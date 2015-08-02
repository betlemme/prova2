#define  EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET 

#include <pcl/io/pcd_io.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/features/normal_3d.h>	    // for computing normals
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh.h>
#include <pcl/filters/filter.h>
#include <pcl/registration/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/correspondence.h>
#include <pcl/recognition/cg/geometric_consistency.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/fpfh_omp.h>		// for computing FPFH with multi-core implementation
#include <pcl/visualization/histogram_visualizer.h>	// for histogram visualization
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <stdio.h> 
#include <math.h> 
#include <algorithm>
#include <vector>

/* Estrae features e fa il match tra 2 nuvole.
 * contiene i metodi:
 *
 * */

using namespace cv;
using namespace std;
using namespace pcl;


typedef pcl::PointXYZRGB PointT;
const float soglia=1.25;

const int DEBUG=0;


/**
 *  Metodo di face detection in 2D
 *	Input: Immagine sorgente
 *  Output: rettangolo che circonda la faccia trovata
 *
 */
Rect detect(Mat source)
{
    cv::Mat out;
    cv::Mat img = source;

    char const * frontaleLBP = "C:/MyLibrary/opencv/sources/data/lbpcascades/lbpcascade_frontalface.xml";
    char const * frontaleHAAR = "C:/MyLibrary/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml";
    char const * profilo ="C:/MyLibrary/opencv/sources/data/haarcascades/haarcascade_profileface.xml";

    //carico il descrittore pre il face detector ( 1 -> frontale , 2 -> profilo)
    char const * faceCascadeFilename;

    faceCascadeFilename = frontaleHAAR;
    cv::CascadeClassifier faceDetector;
	
    try {
        faceDetector.load(faceCascadeFilename);
    } catch (cv::Exception e) {}
    if ( faceDetector.empty() ) {
        cerr << "ERROR: Couldn't load Face Detector (";
        cerr << faceCascadeFilename << ")!" << endl;
        exit(1);
    }
    cout << "descrittore caricato: " << faceCascadeFilename <<endl;


    // detectMultiScale() per trovare la faccia nell'immagine:
    int flags = CASCADE_FIND_BIGGEST_OBJECT;    //cerco una sola faccia
    Size minFeatureSize(90, 90);                //size minima in pixel della faccia
    float searchScaleFactor = 1.1f;             //su quante scale cercare (1.1 oppure 1.2) piu alto è piu è veloce, ma trova meno facce
    int minNeighbors = 4;                       //Reliability vs many faces
    std::vector<Rect> faces;                    //param di uscita, circonda la faccia
    faceDetector.detectMultiScale(img, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);


    if (faces.size() < 1) //non ho trovato una faccia frontale. cerco una faccia di profilo:
    {
        cout << "nessuna faccia trovata" << endl;

        // cerco una faccia di profilo
        faceCascadeFilename = profilo;

        try {
            faceDetector.load(faceCascadeFilename);
        } catch (cv::Exception e) {}
        if ( faceDetector.empty() ) {
            cerr << "ERROR: Couldn't load Face Detector (";
            cerr << faceCascadeFilename << ")!" << endl;
            exit(1);
        }

        cout << "descrittore caricato: " << faceCascadeFilename <<endl;

        faceDetector.detectMultiScale(img, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);

        if (faces.size() < 1)
        {
            cout << "nessuna faccia di profilo trovata" << endl;
            return faces[0];
        }
    }

	return faces[0];
}


/**
 *  Metodo per estrarre il rettangolo relativo alla posizione della
 *  faccia nell'immagine 2D
 *
 */
Rect Face2D(Mat img)
{
	// dimensione della PointCloud
	Size size(960,540);

	// ridimensionamento dell'immagine 2D sulle dimensioni della PointCloud
	resize(img,img,size);

	// rettangolo che circonda la faccia riconosciuta in 2D
    Rect out = detect(img);

	return out;
}


/**
 *  Metodo che dato un rettangolo relativo ad una posizione della poincloud
 *  estrae la sola porzione individuata da tale rettangolo
 */
pcl::PointCloud<PointT>::Ptr ExtractFace3D(pcl::PointCloud<PointT>::Ptr nuvola, Rect face)
{
	// Cloud che contiene la faccia estratta dal 2D proiettata nel 3D 
	pcl::PointCloud<PointT>::Ptr extract (new pcl::PointCloud<PointT>);

	// extract the face dimension from the scene
	int x = face.x;
	int y = face.y;
	int height = face.height;
	int width = face.width;	


	// 3D face extraction from the information of the 2D image
	// considero l'immagine 3D come una matrice bidimensionale
	for( int v=0; v<540; v++) 
        { 
                for ( int u = 0; u<960; u++) 
                { 
					if((u >= x) && (u < x + width) && (v >= y) && (v < y + width))
                        extract->push_back(nuvola->at(u,v));
                } 
        } 

	//pcl::visualization::PCLVisualizer ShowCut("PCL Viewer2");
	//ShowCut.setBackgroundColor (0.0, 0.0, 0.5);
	//ShowCut.addCoordinateSystem (1);
	//pcl::visualization::PointCloudColorHandlerCustom<PointT> rgb1(extract,0,0,0);
	//ShowCut.addPointCloud (nuvola, "extractPCLCut");

	// Create structure containing the parameters for the callback function
	//struct callbackArgs histCallbackArgs;
	 
	// Add point picking callback to viewer (for visualizing feature histograms):
	//ShowCut.registerPointPickingCallback (pp_callback , (void*)&histCallbackArgs);

	// Loop for visualization (so that the visualizers are continuously updated):
	//std::cout << "Visualization... "<< std::endl;
	//while (!ShowCut.wasStopped ())
	//{
	//	ShowCut.spin ();
	//}

	return extract;
}


/**	
 *  Metodo per visualizzare i keypoints
 *  Input = immagine jpg e keypoints calcolati
 */
void showKeypoints(Mat imgCut, vector<KeyPoint> keypoints)
{
	//-- Draw keypoints
	Mat img_keypoints_1;

	drawKeypoints( imgCut, keypoints, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1 );

	waitKey(0);
}

/**
 *  Metodo per calcolare i keypoints dall'immagine jpg
 *  Input:	pointCloud relativa alla foto
 *			immagine jpg relativa alla foto
 *			rettangolo relativo alla posizione della faccia nell'immagine
 *
 *  Output:	Kepoints trasposti nel 3D
 */

pcl::PointCloud<PointT>::Ptr KeyPointsCalc(const pcl::PointCloud<PointT>::Ptr cloud, Mat img, Rect face)
{
	// Cloud contenente i keypoints 3D
	pcl::PointCloud<PointT>::Ptr keypoints3D (new pcl::PointCloud<PointT>);

	// vettore contenente i keypoints 2D
	vector<KeyPoint> keypoints;

	if(DEBUG==0)
		vector<KeyPoint> keypointsFace;

	// dimensione utile dell'immagine
	Size size(960,540);

	// ridimensionamento dell'immagine 2D sulle dimensioni della PointCloud
	resize(img,img,size);

	// estrazione faccia da immagine completa
	Mat imgCut = img(face);

	// calcolo keypoints sulla faccia 2D
	cv::SurfFeatureDetector detector(400); // initial setting 400
	detector.detect(img, keypoints);

	vector<KeyPoint>::const_iterator it = keypoints.begin(),
                                     end = keypoints.end();

    for( ; it != end; ++it )
    {

		if((it->pt.x >= face.x) && (it->pt.x < face.x + face.width) && (it->pt.y >= face.y) && (it->pt.y < face.y + face.width))
			{
				keypoints3D->push_back(cloud->at(it->pt.x,it->pt.y));
				//keypointsFace.push_back(it->pt)
			}
	}



	//if(DEBUG==0)
		//showKeypoints(imgCut, keypointsFace);
	
	/*
	//Visualization keypoints
	pcl::visualization::PCLVisualizer ShowKp("PCL Viewer");
	ShowKp.setBackgroundColor (0.0, 0.0, 0.5);
	ShowKp.addCoordinateSystem (0.1);
	pcl::visualization::PointCloudColorHandlerCustom<PointT> rgb1(cloud,0,0,0);
	ShowKp.addPointCloud (cloud, rgb1, "extractPCL");
	
	pcl::visualization::PointCloudColorHandlerCustom<PointT> rgb2(keypoints3D,255,0,0);
	ShowKp.addPointCloud (keypoints3D, rgb2, "keypoints");

	ShowKp.spin();
	*/

	return keypoints3D;
}


pcl::PointCloud<pcl::FPFHSignature33>::Ptr featureFPFHScalc(pcl::PointCloud<PointT>::Ptr keypoints, pcl::PointCloud<PointT>::Ptr cloud)
{
	// Output datasets
	pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhOut (new pcl::PointCloud<pcl::FPFHSignature33> ());

	pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

	pcl::search::KdTree<PointT>::Ptr tree (new pcl::search::KdTree<PointT> ());

	// Remove NaN from the point cloud:
	std::vector<int> indices;
	pcl::PointCloud<PointT>::Ptr cloudDense (new pcl::PointCloud<PointT>);
	pcl::removeNaNFromPointCloud(*cloud, *cloudDense, indices);

//////NORMAL
	// Create the normal estimation class, and pass the input dataset to it
	pcl::NormalEstimationOMP<PointT, pcl::Normal> normalEstimation;
	normalEstimation.setInputCloud (cloudDense);
	normalEstimation.setSearchMethod (tree);
	normalEstimation.setRadiusSearch (0.02);
	std::cout << "Computing normals...please wait...";
	normalEstimation.setNumberOfThreads(2); 	// set number of threads when using OpenMP 
	normalEstimation.compute (*cloud_normals);
	std::cout << "done." << std::endl;


//////FEATURES
	pcl::FPFHEstimationOMP<PointT, pcl::Normal, pcl::FPFHSignature33> fpfh;
	fpfh.setSearchMethod(tree);
	fpfh.setRadiusSearch (0.03);
	fpfh.setSearchSurface (cloudDense);
	fpfh.setInputNormals (cloud_normals);
	fpfh.setInputCloud (keypoints);

	std::cout << "Computing FPFH features...please wait...";
	fpfh.compute (*fpfhOut); // qui muore tutto
	std::cout << "done." << std::endl;


	// Visualize FPFH:
	int normalsVisualizationStep = 100; // to visualize a normal every normalsVisualizationStep
	float normalsScale = 0.02;			// normals dimension

	pcl::visualization::PCLVisualizer viewer("PCL Viewer");
	pcl::visualization::PCLHistogramVisualizer histViewer;
	viewer.setBackgroundColor (0.0, 0.0, 0.5);
	viewer.addCoordinateSystem (0.1);
	viewer.initCameraParameters ();
	pcl::visualization::PointCloudColorHandlerRGBField<PointT> rgb(cloud);
	viewer.addPointCloud<PointT> (cloud, rgb, "input_cloud");
	viewer.addPointCloudNormals<PointT, pcl::Normal>(cloud, cloud_normals, normalsVisualizationStep, normalsScale, "normals");

	pcl::visualization::PointCloudColorHandlerCustom<PointT> rgb2(keypoints,255,0,0);
	viewer.addPointCloud (keypoints, rgb2, "keypoints");

	// Loop for visualization (so that the visualizers are continuously updated):
	std::cout << "Visualization... "<< std::endl;
	while (!viewer.wasStopped ())
	{
		viewer.spin ();
		histViewer.spin();
	}

    return fpfhOut;
}

int main()
{
	///////////////////////////////DEFINIZIONI INIZIALI////////////////////////////////////////////

	// Clouds input 
    pcl::PointCloud<PointT>::Ptr cloudData(new pcl::PointCloud<PointT>);  //database
    pcl::PointCloud<PointT>::Ptr cloudQuery(new pcl::PointCloud<PointT>);  //query

	// Clouds di input senza lo sfondo, con solo la faccia
	pcl::PointCloud<PointT>::Ptr cloudDataExtract(new pcl::PointCloud<PointT>);  //database
    pcl::PointCloud<PointT>::Ptr cloudQueryExtract(new pcl::PointCloud<PointT>);  //query

	// Keypoints
    pcl::PointCloud<PointT>::Ptr kp1(new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr kp2(new pcl::PointCloud<PointT>);

	// Features
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr feature(new pcl::PointCloud<pcl::FPFHSignature33>);
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr feature2(new pcl::PointCloud<pcl::FPFHSignature33>);

	// Clouds filtered 
	pcl::PointCloud<PointT>::Ptr cloud_f(new pcl::PointCloud<PointT>);  
	pcl::PointCloud<PointT>::Ptr cloud_v(new pcl::PointCloud<PointT>); 

	// Correspondences
    pcl::CorrespondencesPtr corrispondences(new pcl::Correspondences());

	// 2D image input
	cv::Mat imgQuery;
	cv::Mat imgData;

	/////////////////////////////// CARICAMENTO NUVOLE E IMMAGINI /////////////////////////////////////////////

	// caricamento clouds 3D
    if (pcl::io::loadPCDFile<PointT>("G:/3D/RGBD_Face_dataset_testing/RGBD_Face_dataset_testing/Test1/002_00_cloud.pcd", *cloudData) != 0) // MENEGATTI
        { return -1; }
    if (pcl::io::loadPCDFile<PointT>("G:/3D/RGBD_Face_dataset_training/RGBD_Face_dataset_training/000_00_cloud.pcd", *cloudQuery) != 0)
		{ return -1; }

	// caricamento immagini 2D
	imgQuery = cv::imread("G:/3D/RGBD_Face_dataset_training/RGBD_Face_dataset_training/000_00_image.png", CV_LOAD_IMAGE_COLOR);
	imgData = cv::imread("G:/3D/RGBD_Face_dataset_testing/RGBD_Face_dataset_testing/Test1/002_00_image.png", CV_LOAD_IMAGE_COLOR);

    std::cout << "nuvole caricate" << std::endl;

	// rettangolo che circonda la faccia dell'immagine 2D
	Rect rectDataFace = Face2D(imgData);
	Rect rectQueryFace = Face2D(imgQuery);

	// estrazione della faccia 3D dalla pointcloud
	cloudDataExtract = ExtractFace3D(cloudData, rectDataFace);
	cloudQueryExtract = ExtractFace3D(cloudQuery, rectQueryFace);

	//pcl::io::savePCDFile("C:/Users/giki/Desktop/test_pcd.pcd", *cloudDataExtract, true);
	/////////////////////////////// CALCOLO KEYPOINTS /////////////////////////////////////////////

	//Keypoints calculation
	kp1 = KeyPointsCalc(cloudData, imgData, rectDataFace);
    std::cout << "keypoint_data trovati: " << kp1->size() <<std::endl;

    kp2 = KeyPointsCalc(cloudQuery, imgQuery, rectQueryFace);
    std::cout << "keypoint_query trovati: " << kp2->size() <<std::endl;


	std::vector<int> mapping;
    pcl::removeNaNFromPointCloud(*kp1, *kp1, mapping);
    pcl::removeNaNFromPointCloud(*kp2, *kp2, mapping);


	/////////////////////////////// CALCOLO FEATURES ///////////////////////////////////////////////

	//Feature calculation
	feature = featureFPFHScalc(kp1, cloudData);
    std::cout << "feature_data calcolate: " << feature->size() <<std::endl;

	//Feature calculation
	feature2 = featureFPFHScalc(kp2, cloudQuery);
    std::cout << "feature_query calcolate: " << feature2->size() <<std::endl;

	/////////////////////////////// CALCOLO CORRISPONDENZE ////////////////////////////////////////

    std::vector<int> correspondences_out;
    std::vector<float> correspondence_scores_out;

    //corrispondences = match(feature, feature2, correspondences_out, correspondence_scores_out);
    //visualize_correspondences (cloudData, kp1, cloudQuery, kp2, correspondences_out, correspondence_scores_out);

    //consistency(kp2, kp1, corrispondences);

}