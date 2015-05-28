/**
Resgistrazione delle facce estratte per avere un'immagine completa in 3D


**/

#include <pcl/io/pcd_io.h> 		    // for reading the point cloud
#include <pcl/visualization/pcl_visualizer.h>		// for PCL visualizer
#include <pcl/visualization/point_picking_event.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>	
#include <pcl/filters/voxel_grid.h>
#include <iostream>
#include <boost/thread/thread.hpp>
#include <pcl/common/common_headers.h> 
#include <pcl/console/parse.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/registration/icp.h>

typedef pcl::PointXYZRGBA PointT;



int main (int argc, char** argv)
{
	pcl::PointCloud<PointT>::Ptr cloud0_orig (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud1_orig (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud2_orig (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud3_orig (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud4_orig (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr output (new pcl::PointCloud<PointT>);

	pcl::PointCloud<PointT>::Ptr cloud0 (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud1 (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud2 (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud3 (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud4 (new pcl::PointCloud<PointT>);

	pcl::PointCloud<PointT>::Ptr cloudTarget (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr primaRegistrazione_source (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr primaRegistrazione_target (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr primaRegistrazione_output (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr secondaRegistrazione_source (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr secondaRegistrazione_target (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr secondaRegistrazione_output (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr terzaRegistrazione_source (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr terzaRegistrazione_target (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr terzaRegistrazione_output (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr quartaRegistrazione_source (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr quartaRegistrazione_target (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr quartaRegistrazione_output (new pcl::PointCloud<PointT>);

	//read the 1st point cloud------------------------------------------------------
	if (pcl::io::loadPCDFile<PointT> ("G:/3D/RGBD_Face_dataset_training/002/Soggetto_000/000Clean/face000_00Clean.pcd", *cloud0_orig) == -1) //* load the file
			{
				PCL_ERROR ("Couldn't read the pcd file \n");
				return (-1);
			}
	std::cerr << "PointCloud0 before filtering: " << cloud0_orig->width * cloud0_orig->height 
              << " data points (" << pcl::getFieldsList (*cloud0_orig) << ").\n";

    // Create the filtering object
    pcl::VoxelGrid<PointT> sor0;
    sor0.setInputCloud (cloud0_orig);
    sor0.setLeafSize (0.002f, 0.002f, 0.002f);
    sor0.filter (*cloud0);

    std::cerr << "PointCloud0 after filtering: " << cloud0->width * cloud0->height 
              << " data points (" << pcl::getFieldsList (*cloud0) << ").\n\n";

 
	//read the 2nd point cloud------------------------------------------------------
	if (pcl::io::loadPCDFile<PointT> ("G:/3D/RGBD_Face_dataset_training/002/Soggetto_000/000Clean/face000_01Clean.pcd", *cloud1_orig) == -1) //* load the file
			{	PCL_ERROR ("Couldn't read the pcd file \n");
				return (-1);	}

	std::cerr << "PointCloud1 before filtering: " << cloud1_orig->width * cloud1_orig->height 
              << " data points (" << pcl::getFieldsList (*cloud1_orig) << ").\n";

	// Create the filtering object
    pcl::VoxelGrid<PointT> sor1;
    sor1.setInputCloud (cloud1_orig);
    sor1.setLeafSize (0.002f, 0.002f, 0.002f);
    sor1.filter (*cloud1);

    std::cerr << "PointCloud1 after filtering: " << cloud1->width * cloud1->height 
              << " data points (" << pcl::getFieldsList (*cloud1) << ").\n\n";


	// read the 3rd point cloud------------------------------------------------------
	if (pcl::io::loadPCDFile<PointT> ("G:/3D/RGBD_Face_dataset_training/002/Soggetto_000/000Clean/face000_02Clean.pcd", *cloud2_orig) == -1) //* load the file
			{	PCL_ERROR ("Couldn't read the pcd file \n");
				return (-1);	}

	std::cerr << "PointCloud2 before filtering: " << cloud2_orig->width * cloud2_orig->height 
              << " data points (" << pcl::getFieldsList (*cloud2_orig) << ").\n";

	// Create the filtering object
    pcl::VoxelGrid<PointT> sor2;
    sor2.setInputCloud (cloud2_orig);
    sor2.setLeafSize (0.002f, 0.002f, 0.002f);
    sor2.filter (*cloud2);

    std::cerr << "PointCloud2 after filtering: " << cloud2->width * cloud2->height 
              << " data points (" << pcl::getFieldsList (*cloud2) << ").\n\n";


	// read the 4th point cloud------------------------------------------------------
	if (pcl::io::loadPCDFile<PointT> ("G:/3D/RGBD_Face_dataset_training/002/Soggetto_000/000Clean/face000_03Clean.pcd", *cloud3_orig) == -1) //* load the file
			{	PCL_ERROR ("Couldn't read the pcd file \n");
				return (-1);	}

		std::cerr << "PointCloud3 before filtering: " << cloud3_orig->width * cloud3_orig->height 
              << " data points (" << pcl::getFieldsList (*cloud3_orig) << ").\n";

    // Create the filtering object
    pcl::VoxelGrid<PointT> sor3;
    sor3.setInputCloud (cloud3_orig);
    sor3.setLeafSize (0.002f, 0.002f, 0.002f);
    sor3.filter (*cloud3);

    std::cerr << "PointCloud3 after filtering: " << cloud3->width * cloud3->height 
              << " data points (" << pcl::getFieldsList (*cloud3) << ").\n\n";

	
	// read the 5th point cloud------------------------------------------------------
	if (pcl::io::loadPCDFile<PointT> ("G:/3D/RGBD_Face_dataset_training/002/Soggetto_000/000Clean/face000_04Clean.pcd", *cloud4_orig) == -1) //* load the file
			{	PCL_ERROR ("Couldn't read the pcd file \n");
				return (-1);	}

	std::cerr << "PointCloud4 before filtering: " << cloud4_orig->width * cloud4_orig->height 
              << " data points (" << pcl::getFieldsList (*cloud4_orig) << ").\n";

    // Create the filtering object
    pcl::VoxelGrid<PointT> sor4;
    sor4.setInputCloud (cloud4_orig);
    sor4.setLeafSize (0.002f, 0.002f, 0.002f);
    sor4.filter (*cloud4);

    std::cerr << "PointCloud4 after filtering: " << cloud4->width * cloud4->height 
              << " data points (" << pcl::getFieldsList (*cloud4) << ").\n\n";

	
	//remove NAN points from the cloud0
    std::vector<int> indices0;
    pcl::removeNaNFromPointCloud(*cloud0,*cloud0, indices0);
    //remove NAN points from the cloud1
    std::vector<int> indices1;
    pcl::removeNaNFromPointCloud(*cloud1,*cloud1, indices1);
	//remove NAN points from the cloud2
    std::vector<int> indices2;
    pcl::removeNaNFromPointCloud(*cloud2,*cloud2, indices2);
    //remove NAN points from the cloud3
    std::vector<int> indices3;
    pcl::removeNaNFromPointCloud(*cloud3,*cloud3, indices3);
    //remove NAN points from the cloud4
    std::vector<int> indices4;
    pcl::removeNaNFromPointCloud(*cloud4,*cloud4, indices4);

	////////////////////////////// STANDARD NAME ///////////////////////////////////
	
	*cloudTarget=*cloud3;
	
	*primaRegistrazione_source=*cloud0;
	*primaRegistrazione_target=*cloud3;
	//*primaRegistrazione_output=* ;

	
	*secondaRegistrazione_source=*cloud1;
	*secondaRegistrazione_target=*cloud3;
	//*secondaRegistrazione_output=*cloud20;
	
	*terzaRegistrazione_source=*cloud2;
	*terzaRegistrazione_target=*cloud3;
	//*terzaRegistrazione_output=*cloud30;
	
	*quartaRegistrazione_source=*cloud4;
	*quartaRegistrazione_target=*cloud3;
	//*quartaRegistrazione_output=*cloud40;
	
	
	//////////////////////////////////////////////////////////////////////////////
	//source: 1 target: 0
    // ICP object.
    pcl::IterativeClosestPoint<PointT, PointT> registration0;
    registration0.setInputCloud(primaRegistrazione_source);
    registration0.setInputTarget(primaRegistrazione_target);

    //distanza sopra cui non considero allineamenti
    registration0.setMaxCorrespondenceDistance (0.2);
    // Set the maximum number of iterations (criterion 1)
    registration0.setMaximumIterations (500);
    // Set the transformation epsilon (criterion 2)
    registration0.setTransformationEpsilon (1e-10);
    // Set the euclidean distance difference epsilon (criterion 3)
    registration0.setEuclideanFitnessEpsilon (0.00000000001);

    registration0.align(*primaRegistrazione_output);
	//Eigen::Matrix4f Ti = Eigen::Matrix4f::Identity (), targetToSource;

    if (registration0.hasConverged())
    {
        std::cout << "ICP converged." << std::endl
                  << "The score is " << registration0.getFitnessScore() << std::endl;
        std::cout << "Transformation matrix:" << std::endl;
		std::cout << registration0.getFinalTransformation() << std::endl;
    }
    else std::cout << "ICP did not converge." << std::endl;

	std::stringstream ss0;
    ss0 << "G:/3D/RGBD_Face_dataset_training/003/s0-t3.pcd";
    pcl::io::savePCDFile (ss0.str(), *primaRegistrazione_output, true);
	
	
	//////////////////////////////////////////////////////////////////////////////
	//source: 2 target: 0
    // ICP object.
    pcl::IterativeClosestPoint<PointT, PointT> registration1;
    registration1.setInputCloud(secondaRegistrazione_source);
    registration1.setInputTarget(secondaRegistrazione_target);

    //distanza sopra cui non considero allineamenti
    registration1.setMaxCorrespondenceDistance (0.25);
    // Set the maximum number of iterations (criterion 1)
    registration1.setMaximumIterations (500);
    // Set the transformation epsilon (criterion 2)
    registration1.setTransformationEpsilon (1e-10);
    // Set the euclidean distance difference epsilon (criterion 3)
    registration1.setEuclideanFitnessEpsilon (0.0000000001);

    registration1.align(*secondaRegistrazione_output);

    if (registration1.hasConverged())
    {
        std::cout << "ICP converged." << std::endl
                  << "The score is " << registration1.getFitnessScore() << std::endl;
        std::cout << "Transformation matrix:" << std::endl;
        std::cout << registration1.getFinalTransformation() << std::endl;
    }
    else std::cout << "ICP did not converge." << std::endl;

	std::stringstream ss1;
    ss1 << "G:/3D/RGBD_Face_dataset_training/003/s1-t3.pcd";
    pcl::io::savePCDFile (ss1.str(), *secondaRegistrazione_output, true);

	//////////////////////////////////////////////////////////////////////////////
	
	//source: 3 target: 0
    // ICP object.
    pcl::IterativeClosestPoint<PointT, PointT> registration2;
    registration2.setInputCloud(terzaRegistrazione_source);
    registration2.setInputTarget(terzaRegistrazione_target);

    //distanza sopra cui non considero allineamenti
    registration2.setMaxCorrespondenceDistance (0.25);
    // Set the maximum number of iterations (criterion 1)
    registration2.setMaximumIterations (500);
    // Set the transformation epsilon (criterion 2)
    registration2.setTransformationEpsilon (1e-10);
    // Set the euclidean distance difference epsilon (criterion 3)
    registration2.setEuclideanFitnessEpsilon (0.0000000001);

    registration2.align(*terzaRegistrazione_output);

    if (registration2.hasConverged())
    {
        std::cout << "ICP converged." << std::endl
                  << "The score is " << registration2.getFitnessScore() << std::endl;
        std::cout << "Transformation matrix:" << std::endl;
        std::cout << registration2.getFinalTransformation() << std::endl;
    }
    else std::cout << "ICP did not converge." << std::endl;
	
	std::stringstream ss2;
    ss2 << "G:/3D/RGBD_Face_dataset_training/003/s2-t3.pcd";
    pcl::io::savePCDFile (ss1.str(), *terzaRegistrazione_output, true);
	
	//////////////////////////////////////////////////////////////////////////////
	
	//source: 4 target: 3
    // ICP object.
    pcl::IterativeClosestPoint<PointT, PointT> registration3;
    registration3.setInputCloud(quartaRegistrazione_source);
    registration3.setInputTarget(quartaRegistrazione_target);

    //distanza sopra cui non considero allineamenti
    registration3.setMaxCorrespondenceDistance (0.25);
    // Set the maximum number of iterations (criterion 1)
    registration3.setMaximumIterations (500);
    // Set the transformation epsilon (criterion 2)
    registration3.setTransformationEpsilon (1e-10);
    // Set the euclidean distance difference epsilon (criterion 3)
    registration3.setEuclideanFitnessEpsilon (0.0000000001);

    registration3.align(*quartaRegistrazione_output);

    if (registration3.hasConverged())
    {
        std::cout << "ICP converged." << std::endl
                  << "The score is " << registration3.getFitnessScore() << std::endl;
        std::cout << "Transformation matrix:" << std::endl;
        std::cout << registration3.getFinalTransformation() << std::endl;
    }
    else std::cout << "ICP did not converge." << std::endl;
	
	

	// Visualization:
	// vanno visualizzati il risultato e il target
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    viewer.setBackgroundColor (0, 0, 0);
    viewer.addCoordinateSystem (0.01);
    viewer.initCameraParameters ();
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb4(cloudTarget);
    viewer.addPointCloud<PointT> (cloudTarget, rgb4, "cloud0");
	viewer.spin ();
    pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb0(primaRegistrazione_output);
	viewer.addPointCloud<PointT> (primaRegistrazione_output, rgb0, "cloud1");
	viewer.spin ();
    pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb1(secondaRegistrazione_output);
    viewer.addPointCloud<PointT> (secondaRegistrazione_output, rgb1, "cloud2");
    viewer.spin ();
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb2(terzaRegistrazione_output);
	viewer.addPointCloud<PointT> (terzaRegistrazione_output, rgb2, "cloud3");
    viewer.spin ();
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb3(quartaRegistrazione_output);
	viewer.addPointCloud<PointT> (quartaRegistrazione_output, rgb3, "cloud4");
	std::cout << "Fine visualizzazione" << std::endl;
    viewer.spin ();

	
	*output+=*cloudTarget;
	*output+=*primaRegistrazione_output;
	*output+=*secondaRegistrazione_output;
	*output+=*terzaRegistrazione_output;
	*output+=*quartaRegistrazione_output;
	

	std::stringstream ss;
    ss << "G:/3D/RGBD_Face_dataset_training/003/000_registrazione_completa";
    pcl::io::savePCDFile (ss.str(), *output, true);

    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;

    return (0);
}