/**
Pulizia di immagine da 3Dpixel

PCL.exe nome_input nome_output

nome_input: pcd facciale di ingresso (pcd di training)
nome_output: pcd di output contenente la faccia estratta

modificare red,green e blue per cambiare le soglie di eliminazione.
(red_min è stato inserito per poter individuare falsi positivi
che appartengono alla faccia e che senza questo controllo verrebbero
eliminati quando invece dovrebbero rimanere per contribuire
all'informazione facciale, vedi ad esempio i punti di riflesso
della luce dove il colore è quasi bianco)

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


#define red 85
#define green 85
#define blue 85

#define red_min 165

typedef pcl::PointXYZRGBA PointT;

int main (int argc, char** argv)
{
	// Variables declaration:
	pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
	pcl::PointCloud<PointT>::Ptr cloud_ok (new pcl::PointCloud<PointT>);

	//%%%%%%%%%%%%%%%%%%%%%%%%%%%% CODICE PER INPUT DA COMANDO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
			// Check user input
			if (argc < 2)
			{
			  PCL_ERROR ("Syntax is: %s <source.pcd> <destination.pcd>", argv[0]);
			  return (-1);
			}
			PCL_INFO ("Loading...\n");

			pcl::io::loadPCDFile (argv[1], *cloud);

	for(int i=0; i<cloud->width; i++)
	{	
		
	  // se il colore del 3Dpixel è fuori dal colore della faccia
	  if ( (cloud->at(i).r > red) && (cloud->at(i).g > green) && (cloud->at(i).b > blue) )
	  {
		  // non inserire il pixel nella nuova pcd
		  
		  if ( cloud->at(i).r > red_min ) // considerà però i punti in cui la luce ha reso bianca l'immagine
		  {
				// e aggiungili alla nuova pcd considerata buona
				cloud_ok->push_back(cloud->at(i));
		  }
	  }
	  else // se il colore invece è coerente con la faccia
	  {   // aggiungi il pixel ad una nuova pcd considerata buona
		  cloud_ok->push_back(cloud->at(i));
	  }
	}

	// salvataggio nuova pointcloud
    pcl::io::savePCDFile (argv[2], *cloud_ok, true);

	return(0);

}