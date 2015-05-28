#include <pcl/io/pcd_io.h>
#include <pcl/keypoints/iss_3d.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/filters/filter.h>

// This function by Tommaso Cavallari and Federico Tombari, taken from the tutorial
// http://pointclouds.org/documentation/tutorials/correspondence_grouping.php
double computeCloudResolution(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& cloud)
{
    double resolution = 0.0;
    int numberOfPoints = 0;
    int nres;
    std::vector<int> indices(2);
    std::vector<float> squaredDistances(2);
    pcl::search::KdTree<pcl::PointXYZ> tree;
    tree.setInputCloud(cloud);

    for (size_t i = 0; i < cloud->size(); ++i)
    {
        if (! pcl_isfinite((*cloud)[i].x))
            continue;

        // Considering the second neighbor since the first is the point itself.
        nres = tree.nearestKSearch(i, 2, indices, squaredDistances);
        if (nres == 2)
        {
            resolution += sqrt(squaredDistances[1]);
            ++numberOfPoints;
        }
    }
    if (numberOfPoints != 0)
        resolution /= numberOfPoints;

    return resolution;
}



pcl::PointCloud<pcl::PointXYZ>::Ptr KeyPointsCalc(pcl::PointCloud<pcl::PointXYZ>::Ptr nuvola)
{
    // Objects for storing the point cloud and the keypoints.
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints(new pcl::PointCloud<pcl::PointXYZ>);

    cloud = nuvola;


    // ISS keypoint detector object.
    pcl::ISSKeypoint3D<pcl::PointXYZ, pcl::PointXYZ> detector;
    detector.setInputCloud(cloud);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
    detector.setSearchMethod(kdtree);
    double resolution = computeCloudResolution(cloud);
    // Set the radius of the spherical neighborhood used to compute the scatter matrix.
    detector.setSalientRadius(6 * resolution);
    // Set the radius for the application of the non maxima supression algorithm.
    detector.setNonMaxRadius(4 * resolution);
    // Set the minimum number of neighbors that has to be found while applying the non maxima suppression algorithm.
    detector.setMinNeighbors(5);
    // Set the upper bound on the ratio between the second and the first eigenvalue.
    detector.setThreshold21(0.975);
    // Set the upper bound on the ratio between the third and the second eigenvalue.
    detector.setThreshold32(0.975);
    // Set the number of prpcessing threads to use. 0 sets it to automatic.
    detector.setNumberOfThreads(4);

    detector.compute(*keypoints);

    return keypoints;
}



pcl::PointCloud<pcl::FPFHSignature33>::Ptr featureFPFHScalc(pcl::PointCloud<pcl::PointXYZ>::Ptr nuvola)
{
    // Object for storing the point cloud.
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    // Object for storing the normals.
    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    // Object for storing the FPFH descriptors for each point.
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr descriptors(new pcl::PointCloud<pcl::FPFHSignature33>());

    cloud = nuvola;

    // Note: you would usually perform downsampling now. It has been omitted here
    // for simplicity, but be aware that computation can take a long time.              <== fuck the sistem!!!

    // Estimate the normals.
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
    normalEstimation.setInputCloud(cloud);
    normalEstimation.setRadiusSearch(0.02);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr kdtree(new pcl::search::KdTree<pcl::PointXYZ>);
    normalEstimation.setSearchMethod(kdtree);
    normalEstimation.compute(*normals);

    // FPFH estimation object.
    pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
    fpfh.setInputCloud(cloud);
    fpfh.setInputNormals(normals);
    fpfh.setSearchMethod(kdtree);
    // Search radius, to look for neighbors. Note: the value given here has to be
    // larger than the radius used to estimate the normals.
    fpfh.setRadiusSearch(0.03);

    fpfh.compute(*descriptors);

    return descriptors;
}

pcl::CorrespondencesPtr match(pcl::PointCloud<pcl::FPFHSignature33>::Ptr scene, pcl::PointCloud<pcl::FPFHSignature33>::Ptr model)
{
    // Object for storing the SHOT descriptors for the scene.
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr sceneDescriptors(new pcl::PointCloud<pcl::FPFHSignature33>());
    // Object for storing the SHOT descriptors for the model.
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr modelDescriptors(new pcl::PointCloud<pcl::FPFHSignature33>());

    sceneDescriptors = scene;
    modelDescriptors = model;

    // A kd-tree object that uses the FLANN library for fast search of nearest neighbors.
    pcl::KdTreeFLANN<pcl::FPFHSignature33> matching;
    matching.setInputCloud(modelDescriptors);
    // A Correspondence object stores the indices of the query and the match,
    // and the distance/weight.
    pcl::CorrespondencesPtr correspondences(new pcl::Correspondences());

    // Check every descriptor computed for the scene.
    for (size_t i = 0; i < sceneDescriptors->size(); ++i)
    {
        std::vector<int> neighbors(1);
        std::vector<float> squaredDistances(1);
        // Ignore NaNs.
//        if (pcl_isfinite(sceneDescriptors->at(i).descriptor[0]))
//        {
            // Find the nearest neighbor (in descriptor space)...
            int neighborCount = matching.nearestKSearch(sceneDescriptors->at(i), 1, neighbors, squaredDistances);
            // ...and add a new correspondence if the distance is less than a threshold
            // (SHOT distances are between 0 and 1, other descriptors use different metrics).
            if (neighborCount == 1 && squaredDistances[0] < 0.9f)  //0.25f
            {
                pcl::Correspondence correspondence(neighbors[0], static_cast<int>(i), squaredDistances[0]);
                correspondences->push_back(correspondence);
            }
//        }
    }
    std::cout << "Found " << correspondences->size() << " correspondences." << std::endl;

    return correspondences;
}




int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudData(new pcl::PointCloud<pcl::PointXYZ>);  //database
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudQuery(new pcl::PointCloud<pcl::PointXYZ>);  //query

    pcl::PointCloud<pcl::PointXYZ>::Ptr kp(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr kp2(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::FPFHSignature33>::Ptr feature(new pcl::PointCloud<pcl::FPFHSignature33>);
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr feature2(new pcl::PointCloud<pcl::FPFHSignature33>);

    pcl::CorrespondencesPtr corrispondences(new pcl::Correspondences());


    std::cout << "fin qui ok 1" <<std::endl;

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("dritta.pcd", *cloudData) != 0)
        {
            return -1;
        }
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("000_00_cloud.pcd", *cloudQuery) != 0)
        {
            return -1;
        }
    std::vector<int> mapping;
    pcl::removeNaNFromPointCloud(*cloudQuery, *cloudQuery, mapping);

    std::cout << "nuvole caricate" << std::endl;

    kp = KeyPointsCalc(cloudData);
    std::cout << "keypoint trovati: " << kp->size() <<std::endl;
    feature = featureFPFHScalc(kp);
    std::cout << "feature calcolate: " << feature->size() <<std::endl;

    kp2 = KeyPointsCalc(cloudQuery);
    std::cout << "keypoint2 trovati: " << kp2->size() <<std::endl;
    feature2 = featureFPFHScalc(kp2);
    std::cout << "feature calcolate: " << feature2->size() <<std::endl;

    corrispondences = match(feature, feature2);

}






































