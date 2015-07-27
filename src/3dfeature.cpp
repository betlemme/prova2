#include <pcl/io/pcd_io.h>
#include <pcl/keypoints/iss_3d.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/filters/filter.h>
#include <pcl/registration/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/correspondence.h>
#include <pcl/recognition/cg/geometric_consistency.h>

/* Estrae features e fa il match tra 2 nuvole.
 * contiene i metodi:
 *- KeyPointsCalc
 *- featureFPFHScalc
 *- consistency (da problemi)
 *- visualize_corrispondences
 *
 * -main
 *
 *
 *
 *
 *
 * */

int consistency(pcl::PointCloud<pcl::PointXYZ>::Ptr _sceneKeypoints, pcl::PointCloud<pcl::PointXYZ>::Ptr _modelKeypoints, pcl::CorrespondencesPtr _correspondences )
{
    // Objects for storing the keypoints of the scene and the model.
    pcl::PointCloud<pcl::PointXYZ>::Ptr sceneKeypoints(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr modelKeypoints(new pcl::PointCloud<pcl::PointXYZ>);
    // Objects for storing the unclustered and clustered correspondences.
    pcl::CorrespondencesPtr correspondences(new pcl::Correspondences());
    std::vector<pcl::Correspondences> clusteredCorrespondences;
    // Object for storing the transformations (rotation plus translation).
    std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f> > transformations;

    sceneKeypoints = _sceneKeypoints;
    modelKeypoints = _modelKeypoints;
    correspondences = _correspondences;

    // Object for correspondence grouping.
    pcl::GeometricConsistencyGrouping<pcl::PointXYZ, pcl::PointXYZ> grouping;
    grouping.setSceneCloud(sceneKeypoints);
    grouping.setInputCloud(modelKeypoints);
    grouping.setModelSceneCorrespondences(correspondences);
    // Minimum cluster size. Default is 3 (as at least 3 correspondences
    // are needed to compute the 6 DoF pose).
    grouping.setGCThreshold(3);
    // Resolution of the consensus set used to cluster correspondences together,
    // in metric units. Default is 1.0.
    grouping.setGCSize(0.01);

    grouping.recognize(transformations, clusteredCorrespondences);

    std::cout << "Model instances found: " << transformations.size() << std::endl << std::endl;
    for (size_t i = 0; i < transformations.size(); i++)
    {
        std::cout << "Instance " << (i + 1) << ":" << std::endl;
        std::cout << "\tHas " << clusteredCorrespondences[i].size() << " correspondences." << std::endl << std::endl;

        Eigen::Matrix3f rotation = transformations[i].block<3, 3>(0, 0);
        Eigen::Vector3f translation = transformations[i].block<3, 1>(0, 3);
        printf("\t\t    | %6.3f %6.3f %6.3f | \n", rotation(0, 0), rotation(0, 1), rotation(0, 2));
        printf("\t\tR = | %6.3f %6.3f %6.3f | \n", rotation(1, 0), rotation(1, 1), rotation(1, 2));
        printf("\t\t    | %6.3f %6.3f %6.3f | \n", rotation(2, 0), rotation(2, 1), rotation(2, 2));
        std::cout << std::endl;
        printf("\t\tt = < %0.3f, %0.3f, %0.3f >\n", translation(0), translation(1), translation(2));
    }
    return 0;
}




void visualize_correspondences (const pcl::PointCloud<pcl::PointXYZ>::Ptr points1,
                                const pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints1,
                                const pcl::PointCloud<pcl::PointXYZ>::Ptr points2,
                                const pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints2,
                                const std::vector<int> &correspondences,
                                const std::vector<float> &correspondence_scores)
{
  // We want to visualize two clouds side-by-side, so do to this, we'll make copies of the clouds and transform them
  // by shifting one to the left and the other to the right.  Then we'll draw lines between the corresponding points

  // Create some new point clouds to hold our transformed data
  pcl::PointCloud<pcl::PointXYZ>::Ptr points_left (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints_left (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr points_right (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr keypoints_right (new pcl::PointCloud<pcl::PointXYZ>);

  // Shift the first clouds' points to the left
  //const Eigen::Vector3f translate (0.0, 0.0, 0.3);
  const Eigen::Vector3f translate (0.4, 0.0, 0.0);
  const Eigen::Quaternionf no_rotation (0, 0, 0, 0);
  pcl::transformPointCloud (*points1, *points_left, -translate, no_rotation);
  pcl::transformPointCloud (*keypoints1, *keypoints_left, -translate, no_rotation);

  // Shift the second clouds' points to the right
  pcl::transformPointCloud (*points2, *points_right, translate, no_rotation);
  pcl::transformPointCloud (*keypoints2, *keypoints_right, translate, no_rotation);

  // Add the clouds to the vizualizer
  pcl::visualization::PCLVisualizer viz;
  viz.addPointCloud (points_left, "points_left");
  viz.addPointCloud (points_right, "points_right");

  // Compute the median correspondence score
  std::vector<float> temp (correspondence_scores);
  std::sort (temp.begin (), temp.end ());
  float median_score = temp[temp.size ()/2];

  // Draw lines between the best corresponding points
  for (size_t i = 0; i < keypoints_left->size (); ++i)
  {
    if (correspondence_scores[i] > 50)   //if (correspondence_scores[i] > median_score)
    {
      continue; // Don't draw weak correspondences
    }

    // Get the pair of points
    const pcl::PointXYZ & p_left = keypoints_left->points[i];
    const pcl::PointXYZ & p_right = keypoints_right->points[correspondences[i]];

    // Generate a random (bright) color
    double r = (rand() % 100);
    double g = (rand() % 100);
    double b = (rand() % 100);
    double max_channel = std::max (r, std::max (g, b));
    r /= max_channel;
    g /= max_channel;
    b /= max_channel;

    // Generate a unique string for each line
    std::stringstream ss ("line");
    ss << i;

    // Draw the line
    viz.addLine (p_left, p_right, r, g, b, ss.str ());
  }

  // Give control over to the visualizer
  viz.spin ();
}



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

pcl::CorrespondencesPtr match(pcl::PointCloud<pcl::FPFHSignature33>::Ptr scene, pcl::PointCloud<pcl::FPFHSignature33>::Ptr model,std::vector<int> &correspondences_out, std::vector<float> &correspondence_scores_out)
{
    // Resize the output vector (per debug, mi servono i vettori degli accoppiamenti per disegnarli)
    correspondences_out.resize (scene->size ());
    correspondence_scores_out.resize (scene->size ());



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
            if (neighborCount == 1 && squaredDistances[0] < 200.0f)  //0.25f
            {
                pcl::Correspondence correspondence(neighbors[0], static_cast<int>(i), squaredDistances[0]);
                correspondences->push_back(correspondence);

                //correspondences_out[i] = neighbors[0];
                //correspondence_scores_out[i] = squaredDistances[0];

            }
            //debug: aggiungo le corrispondenze in un vetttore di interi, per disegnarle
            std::cout << "squaredDistances " << i << ": " << squaredDistances[0] <<std::endl;

            correspondences_out[i] = neighbors[0];
            correspondence_scores_out[i] = squaredDistances[0];

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

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("000_registrazione_completa_cleaned.pcd", *cloudData) != 0)
        {
            return -1;
        }
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("dritta.pcd", *cloudQuery) != 0)
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

    std::vector<int> correspondences_out;
    std::vector<float> correspondence_scores_out;

    corrispondences = match(feature, feature2, correspondences_out, correspondence_scores_out);
    visualize_correspondences (cloudData, kp, cloudQuery, kp2, correspondences_out, correspondence_scores_out);

    cout << "consistenza..." << endl;
    consistency(kp2, kp, corrispondences);

}
