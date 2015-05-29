/**
Estrazione facciale da pcd fornita per il progetto.

PCL.exe nome_input nome_output

nome_input: pcd di ingresso (pcd di training)
nome_output: pcd di output contenente la faccia estratta.

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

typedef pcl::PointXYZRGBA PointT;

struct callbackArgs{
	// structure used to pass arguments to the callback function
	float x,y,z;
};

void pp_callback (const pcl::visualization::PointPickingEvent& event, void* args)
{
	// callback function used to visualize feature histograms
	struct callbackArgs* data = (struct callbackArgs *)args;
    if (event.getPointIndex () == -1)
      return;
    event.getPoint( data->x, data->y, data->z); 
    cout << "Point ("<<data->x<<","<<data->y<<","<<data->z<<") was picked"<<endl; 
}


int main (int argc, char** argv)
{
	// Variables declaration:
	pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud_f (new pcl::PointCloud<PointT>);

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%% CODICE PER INPUT DA COMANDO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			// Check user input
			if (argc < 2)
			{
			  PCL_ERROR ("Syntax is: %s <source.pcd> <destination.pcd>", argv[0]);
			  return (-1);
			}
			PCL_INFO ("Loading...\n");
			pcl::io::loadPCDFile (argv[1], *cloud);
			
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%% CODICE PER INPUT DA FILE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			// Load point cloud from .pcd file:
			/*if (pcl::io::loadPCDFile<PointT> ("G:/3D/RGBD_Face_dataset_training/001/cloud_cluster001_00.pcd", *cloud) == -1) //* load the file
			{
				PCL_ERROR ("Couldn't read the pcd file \n");
				return (-1);
			}
			*/


	std::cout << "Loaded "
			  << cloud->width * cloud->height
			  << " data points from the pcd file. "
			  << std::endl;

    // VISUALIZER
	pcl::visualization::PCLVisualizer viewer("PCL Viewer");
	viewer.setBackgroundColor (0.0, 0.0, 0.5);
	viewer.addCoordinateSystem (0.1);
	viewer.initCameraParameters ();
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb1(cloud);
	viewer.addPointCloud<PointT> (cloud, rgb1, "input_cloud1");

	// Create structure containing the parameters for the callback function
	struct callbackArgs histCallbackArgs;
	 
	// Add point picking callback to viewer (for visualizing feature histograms):
	viewer.registerPointPickingCallback (pp_callback , (void*)&histCallbackArgs);

	// Loop for visualization (so that the visualizers are continuously updated):
	std::cout << "Visualization... "<< std::endl;
	while (!viewer.wasStopped ())
	{
		viewer.spin ();
	}
	
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% TO DELETE THE SPORCIZIA %%%%%%%%%%%%%
			// Remove Nan pointers from the cloud data
			  pcl::PointCloud<PointT>::Ptr cloud_filtered (new pcl::PointCloud<PointT>);
			  std::vector<int> indices;
			  pcl::removeNaNFromPointCloud(*cloud,*cloud_filtered, indices);

			  std::cout << "Nan removed - Reloaded "
						<< cloud_filtered->width * cloud_filtered->height
						<< " data points from the pcd file. "
						<< std::endl;

			  for(int i=0; i<cloud_filtered->width; i++)
			  {
				  int u=cloud_filtered->at(i).z;
				  if (cloud_filtered->at(i).z < 1)
				  {
					  cloud_f->push_back(cloud_filtered->at(i));
				  }
			  }

	std::cout << "Select with the mouse the sphere facial portion to extract."<< std::endl;

	// point selected with mouse
	pcl::PointXYZ pc (histCallbackArgs.x,histCallbackArgs.y,histCallbackArgs.z);

	std::cout<< "\nViewer 2 ucciso, inizio procedura estrazione facciale"<< std::endl;

	// point container of the correct face
	pcl::PointCloud<PointT>::Ptr cloud_ok (new pcl::PointCloud<PointT>);

	// estrapolation face from the total pointcloud
	for(int i=0; i<cloud_f->width; i++)
	{	

	  if ( pow((cloud_f->at(i).x - pc.x),2) + pow((cloud_f->at(i).y - pc.y),2) + pow((cloud_f->at(i).z - pc.z),2) < pow(0.16,2))
	  {
		  cloud_ok->push_back(cloud_f->at(i));
	  }
	}

	std::cout<< "\nFaccia estratta corretamente"<< std::endl;

	// visualization facial extraction
	pcl::visualization::PCLVisualizer viewer3("PCL Viewer2");
	viewer3.setBackgroundColor (0.0, 0.0, 0.5);
	viewer3.addCoordinateSystem (0.1);
	viewer3.initCameraParameters ();
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb3(cloud_ok);
	viewer3.addPointCloud<PointT> (cloud_ok, rgb3, "input_cloud1");

	// Loop for visualization (so that the visualizers are continuously updated):
	std::cout << "Visualization... "<< std::endl;
	while (!viewer3.wasStopped ())
	{
		viewer3.spin ();
	}

	std::cout<< "\nInizio procedura di salvataggio"<< std::endl;

	//%%%%%%%%%%%%%%%%%%%%%% SALVATAGGIO POINTCLOUD DA COMANDO %%%%%%%%%%%%%%%%%%%%%

	//std::stringstream ss;
    //ss << "G:/3D/RGBD_Face_dataset_training/002/extract";
    pcl::io::savePCDFile (argv[2], *cloud_ok, true);


	return 0;
}