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
#include <pcl/visualization/pcl_visualizer.h>		// for PCL visualizer

#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>

#include <iostream>

#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>		// for PCL visualizer

#include <pcl/filters/filter.h>

#include <pcl/registration/icp.h>

#include <string>

int
main (int argc, char** argv)
{


    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud6(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud3(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud4(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud5(new pcl::PointCloud<pcl::PointXYZRGB>);

    pcl::io::loadPCDFile("alto.pcd", *cloud6); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("basso.pcd", *cloud3); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("destra.pcd", *cloud5); //"../dataset/people/2.pcd"        //#4 è targhet!!!!!!
    pcl::io::loadPCDFile("dritta.pcd", *cloud4); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("sinistra.pcd", *cloud2); //"../dataset/people/2.pcd"
/*
    pcl::io::loadPCDFile("robot_6.pcd", *cloud6); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("robot_2.pcd", *cloud2); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("robot_3.pcd", *cloud3); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("robot_4.pcd", *cloud4); //"../dataset/people/2.pcd"
    pcl::io::loadPCDFile("robot_5.pcd", *cloud5); //"../dataset/people/2.pcd"

*/

    //remove NAN points from the cloud
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloud6,*cloud6, indices);
    //remove NAN points from the cloud2
    std::vector<int> indices2;
    pcl::removeNaNFromPointCloud(*cloud2,*cloud2, indices2);
    //remove NAN points from the cloud2
    std::vector<int> indices3;
    pcl::removeNaNFromPointCloud(*cloud3,*cloud3, indices3);
    //remove NAN points from the cloud2
    std::vector<int> indices4;
    pcl::removeNaNFromPointCloud(*cloud4,*cloud4, indices4);
    //remove NAN points from the cloud2
    std::vector<int> indices5;
    pcl::removeNaNFromPointCloud(*cloud5,*cloud5, indices5);


    // Visualization:
    pcl::visualization::PCLVisualizer viewer2("PCL Viewer");
    viewer2.setBackgroundColor (0, 0, 0);
    viewer2.addCoordinateSystem (0.01);
    viewer2.initCameraParameters ();
//    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud6);
//    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud6, rgb, "cloud1");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud2);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud2, rgb2, "cloud2");
//    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb3(cloud3);
//    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud3, rgb3, "cloud3");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb4(cloud4);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud4, rgb4, "cloud4");
//    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb5(cloud5);
//    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud5, rgb5, "cloud5");


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
    registration.setMaxCorrespondenceDistance (0.25);
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
/*
    //source: 3 target: 4
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr finalCloud2(new pcl::PointCloud<pcl::PointXYZRGB>);
        // ICP object.
        pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> registration2;
        registration2.setInputSource(cloud3);
        registration2.setInputTarget(cloud4);

        //distanza sopra cui non considero allineamenti
        registration2.setMaxCorrespondenceDistance (1.5);
        // Set the maximum number of iterations (criterion 1)
        registration2.setMaximumIterations (50);
        // Set the transformation epsilon (criterion 2)
        registration2.setTransformationEpsilon (1e-8);
        // Set the euclidean distance difference epsilon (criterion 3)
        registration2.setEuclideanFitnessEpsilon (0.01);

        registration2.align(*finalCloud2);

        if (registration2.hasConverged())
        {
            std::cout << "ICP converged." << std::endl
                      << "The score is " << registration2.getFitnessScore() << std::endl;
            std::cout << "Transformation matrix:" << std::endl;
            std::cout << registration2.getFinalTransformation() << std::endl;
        }
        else std::cout << "ICP did not converge." << std::endl;

        //source: 5 target: 4
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr finalCloud3(new pcl::PointCloud<pcl::PointXYZRGB>);
        // ICP object.
        pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> registration3;
        registration3.setInputSource(cloud5);
        registration3.setInputTarget(cloud4);

        //distanza sopra cui non considero allineamenti
        registration3.setMaxCorrespondenceDistance (1.5);
        // Set the maximum number of iterations (criterion 1)
        registration3.setMaximumIterations (50);
        // Set the transformation epsilon (criterion 2)
        registration3.setTransformationEpsilon (1e-8);
        // Set the euclidean distance difference epsilon (criterion 3)
        registration3.setEuclideanFitnessEpsilon (0.01);

        registration3.align(*finalCloud3);

        if (registration3.hasConverged())
        {
            std::cout << "ICP converged." << std::endl
                      << "The score is " << registration3.getFitnessScore() << std::endl;
            std::cout << "Transformation matrix:" << std::endl;
            std::cout << registration3.getFinalTransformation() << std::endl;
        }
        else std::cout << "ICP did not converge." << std::endl;

        //source: 6 target: 4
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr finalCloud4(new pcl::PointCloud<pcl::PointXYZRGB>);
        // ICP object.
        pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB> registration4;
        registration4.setInputSource(cloud6);
        registration4.setInputTarget(cloud4);

        //distanza sopra cui non considero allineamenti
        registration4.setMaxCorrespondenceDistance (1.5);
        // Set the maximum number of iterations (criterion 1)
        registration4.setMaximumIterations (50);
        // Set the transformation epsilon (criterion 2)
        registration4.setTransformationEpsilon (1e-8);
        // Set the euclidean distance difference epsilon (criterion 3)
        registration4.setEuclideanFitnessEpsilon (0.01);

        registration4.align(*finalCloud4);

        if (registration4.hasConverged())
        {
            std::cout << "ICP converged." << std::endl
                      << "The score is " << registration4.getFitnessScore() << std::endl;
            std::cout << "Transformation matrix:" << std::endl;
            std::cout << registration4.getFinalTransformation() << std::endl;
        }
        else std::cout << "ICP did not converge." << std::endl;
*/
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
/*    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb11(finalCloud2);
    viewer.addPointCloud<pcl::PointXYZRGB> (finalCloud2, rgb11, "cloud3");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb12(finalCloud3);
    viewer.addPointCloud<pcl::PointXYZRGB> (finalCloud3, rgb12, "cloud4");
    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb13(finalCloud4);
    viewer.addPointCloud<pcl::PointXYZRGB> (finalCloud4, rgb13, "cloud5");
*/
    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;

    viewer.spin ();


    return (0);
}
