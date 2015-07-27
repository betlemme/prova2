/*
 * ex5.cpp
 *
 *  Created on: Gen 15, 2015
 *      Author: E.C.
 *
 * Exercise 5:
 *   Register together at least five out of the six pointclouds provided
 *    in ‘data/nao’ folder of PCL Lab 4.
 *   Keep only the part of the clouds corresponding to the robot.
 *
 */


#include <pcl/ModelCoefficients.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/registration/icp.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>		// for PCL visualizer
#include <pcl/filters/filter.h>


#include <string>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double getRegistrationDistance(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud4)
{
    double distance = 2000;

    //remove NAN points from the cloud2
    std::vector<int> indices2;
    pcl::removeNaNFromPointCloud(*cloud2,*cloud2, indices2);
    //remove NAN points from the cloud4
    std::vector<int> indices4;
    pcl::removeNaNFromPointCloud(*cloud4,*cloud4, indices4);

    // Visualization:
    pcl::visualization::PCLVisualizer viewer2("PCL Viewer");
    viewer2.setBackgroundColor (0, 0, 0);
    viewer2.addCoordinateSystem (0.01);
    viewer2.initCameraParameters ();
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud2);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud2, rgb2, "cloud2");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb4(cloud4);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud4, rgb4, "cloud4");
    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;
    viewer2.spin ();

    //source: 2 target: 4
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr finalCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    // ICP object.
    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> registration;
    registration.setInputSource(cloud2);
    registration.setInputTarget(cloud4);

    //distanza sopra cui non considero allineamenti
    registration.setMaxCorrespondenceDistance (2); //0.25
    // Set the maximum number of iterations (criterion 1)
    registration.setMaximumIterations (200);
    // Set the transformation epsilon (criterion 2)
    registration.setTransformationEpsilon (1e-8);
    // Set the euclidean distance difference epsilon (criterion 3)
    registration.setEuclideanFitnessEpsilon (0.00000001);

    registration.align(*finalCloud);

    if (registration.hasConverged())
    {
        std::cout << "ICP converged." << std::endl
                  << "Distance: " << registration.getFitnessScore() << std::endl;
    }
    else std::cout << "ICP did not converge." << std::endl;

    // Visualization:
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    viewer.setBackgroundColor (0, 0, 0);
    viewer.addCoordinateSystem (0.01);
    viewer.initCameraParameters ();
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb9(finalCloud);
    viewer.addPointCloud<pcl::PointXYZRGB> (finalCloud, rgb9, "cloud1");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb10(cloud4);
    viewer.addPointCloud<pcl::PointXYZRGB> (cloud4, rgb10, "cloud2");
    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;
    viewer.spin ();


    distance = registration.getFitnessScore();
    return distance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
main (int argc, char** argv)
{

    if (argc < 3)
    {
        cout << "usare ./ex5 <input.pcd> <output.pcd>" << endl;
        return -1;
    }

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZRGB>);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud4(new pcl::PointCloud<pcl::PointXYZRGB>);


    pcl::io::loadPCDFile(argv[1], *cloud2); //"../dataset/people/2.pcd"        //#2 è source
    pcl::io::loadPCDFile(argv[2], *cloud4); //"../dataset/people/2.pcd"        //#4 è target


    double distanza = getRegistrationDistance(cloud2, cloud4);

    cout << "distanza: " << distanza << endl;

/*
    //remove NAN points from the cloud2
    std::vector<int> indices2;
    pcl::removeNaNFromPointCloud(*cloud2,*cloud2, indices2);
    //remove NAN points from the cloud4
    std::vector<int> indices4;
    pcl::removeNaNFromPointCloud(*cloud4,*cloud4, indices4);

    // Visualization:
    pcl::visualization::PCLVisualizer viewer2("PCL Viewer");
    viewer2.setBackgroundColor (0, 0, 0);
    viewer2.addCoordinateSystem (0.01);
    viewer2.initCameraParameters ();

    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud2);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud2, rgb2, "cloud2");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb4(cloud4);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud4, rgb4, "cloud4");



    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;

    viewer2.spin ();

    //source: 2 target: 4
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr finalCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    // ICP object.
    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> registration;
    registration.setInputSource(cloud2);
    registration.setInputTarget(cloud4);

    //distanza sopra cui non considero allineamenti
    registration.setMaxCorrespondenceDistance (2); //0.25
    // Set the maximum number of iterations (criterion 1)
    registration.setMaximumIterations (200);
    // Set the transformation epsilon (criterion 2)
    registration.setTransformationEpsilon (1e-8);
    // Set the euclidean distance difference epsilon (criterion 3)
    registration.setEuclideanFitnessEpsilon (0.00000001);

    registration.align(*finalCloud);

    if (registration.hasConverged())
    {
        std::cout << "ICP converged." << std::endl
                  << "The score is " << registration.getFitnessScore() << std::endl;
        std::cout << "Transformation matrix:" << std::endl;
        std::cout << registration.getFinalTransformation() << std::endl;
    }
    else std::cout << "ICP did not converge." << std::endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Visualization:
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    viewer.setBackgroundColor (0, 0, 0);
    viewer.addCoordinateSystem (0.01);
    viewer.initCameraParameters ();
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb9(finalCloud);
    viewer.addPointCloud<pcl::PointXYZRGB> (finalCloud, rgb9, "cloud1");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb10(cloud4);
    viewer.addPointCloud<pcl::PointXYZRGB> (cloud4, rgb10, "cloud2");

    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;

    viewer.spin ();
*/

    return (0);
}
