/*
 *
 *
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
#include <pcl/io/pcd_io.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>

#include <string>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "detection.h"

using namespace cv;
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pcl::PointCloud<pcl::PointXYZRGB>::Ptr findFace3D(char* pathImg, char* pathCloud )
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr extract(new pcl::PointCloud<pcl::PointXYZRGB>);  //nuvola da restituire

    Mat img = imread(pathImg, CV_LOAD_IMAGE_GRAYSCALE);
    /*
    imshow("img", img);
    waitKey(0);
    */

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile(pathCloud, *cloud2); //"../dataset/people/2.pcd"        //#2 è source
    //non farlo! deorganizza la nuvola rendendola inutile
    //remove NAN points from the cloud2
    //std::vector<int> indices2;
    //pcl::removeNaNFromPointCloud(*cloud2,*cloud2, indices2);

    /*
    // Visualization:
    pcl::visualization::PCLVisualizer viewer2("PCL Viewer");
    viewer2.setBackgroundColor (0, 0, 0);
    viewer2.addCoordinateSystem (0.01);
    viewer2.initCameraParameters ();

    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud2);
    viewer2.addPointCloud<pcl::PointXYZRGB> (cloud2, rgb2, "cloud2");
    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;

    viewer2.spin ();
    */



    //cout << "caricamrento OK!" << img.size() << cloud2->width <<"x" << cloud2->height << endl;    debug

    ///////////////////////////////////////////////////////////////////////////////////////////

    Rect out = detectRect(img);

    //cout << out.x << " " << out.y << " " << out.width << " " << out.height << endl;   debug

    // face projection to 3D
    //Extract the face dimension from the scene
    int x,y,height,width;
    x=out.x;
    y=out.y;
    height=out.height;
    width=out.width;

    //provo a ridimensionare il rect, per tenere solo la faccia:
    height = height*0.8;
    width = width*0.8;
    x = ( x + (width*0.2)/2 );
    y = ( y + (height*0.2)/2 );

    //normalize with the pcd dimension (960x540)
    x=x/2;
    y=y/2;
    height=height/2;
    width=width/2;

    // 3D face extraction from the information of the 2D image
    for( int v=0; v<540; v++)
        {
                for ( int u = 0; u<960; u++)
                {
                    if((u >= x) && (u < x + width) && (v >= y) && (v < y + width))
                    {
                        if (cloud2->at(u,v).z < 2 ) //prendo solo punti entro un raggio di 2m
                            extract->push_back(cloud2->at(u,v));
                    }
                }
        }


    //cout << "estrazione OK!"  << extract->width <<"x" << extract->height << endl; debug

/*
    // Visualization:
    pcl::visualization::PCLVisualizer viewer3("PCL Viewer");
    viewer3.setBackgroundColor (0, 0, 0);
    viewer3.addCoordinateSystem (0.01);
    viewer3.initCameraParameters ();

    pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(extract);
    viewer3.addPointCloud<pcl::PointXYZRGB> (extract, rgb, "extract");
    // Loop for visualization (so that the visualizers are continuously updated):
    std::cout << "Visualization... "<< std::endl;

    viewer3.spin ();
*/

    //pcl::io::savePCDFile ("extract1.pcd", *extract);  debug

    return extract;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > findFaceFromDataset(int dataset)
{
    vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > vectorFace; //da restituire alla fine

    String path = "/media/enrico/U/face3d/RGBD_Face_dataset_testing/Test1/";
    String formatCloud = "cloud.pcd";
    String formatImg = "image.png";
    int NUMBER_OF_SUBJECT = 19;

    String imgPath;
    String cloudPath;
    String number;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr extract(new pcl::PointCloud<pcl::PointXYZRGB>);
    for ( int i = 0; i < NUMBER_OF_SUBJECT; i++)
    {
        if (i == 0) number = "000_";
        if (i == 1) number = "001_";
        if (i == 2) number = "002_";
        if (i == 3) number = "003_";
        if (i == 4) number = "004_";
        if (i == 5) number = "005_";
        if (i == 6) number = "006_";
        if (i == 7) number = "007_";
        if (i == 8) number = "008_";
        if (i == 9) number = "009_";
        if (i == 10) number = "010_";
        if (i == 11) number = "011_";
        if (i == 12) number = "012_";
        if (i == 13) number = "013_";
        if (i == 14) number = "014_";
        if (i == 15) number = "015_";
        if (i == 16) number = "016_";
        if (i == 17) number = "017_";
        if (i == 18) number = "018_";

        imgPath = path + number + "07_" + formatImg;
        char *pathImg = &imgPath[0u];   //converto da string a char*
        cloudPath = path + number + "07_" + formatCloud;
        char *pathCloud = &cloudPath[0u];   //converto da string a char*

        //cout << "image: "<< imgPath << endl;
        //cout << "cloud: "<< cloudPath << endl;

        extract = findFace3D(pathImg, pathCloud);
        vectorFace.push_back(extract);

    }

    return vectorFace;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > loadSubject()
{
    vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > vectorSubject; //da restituire alla fine

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tmpSubject0(new pcl::PointCloud<pcl::PointXYZRGB>);
    //soggetto 000:
    pcl::io::loadPCDFile("000_registrazione_completa_cleaned.pcd", *tmpSubject0);
    vectorSubject.push_back(tmpSubject0);
    //soggetto 001:
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tmpSubject1(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile("Soggetto_001_voxel_clean85.pcd", *tmpSubject1);
    vectorSubject.push_back(tmpSubject1);
    //soggetto 009:
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tmpSubject9(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile("Soggetto_009_clean85.pcd", *tmpSubject9);
    vectorSubject.push_back(tmpSubject9);
    //soggetto 010:
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tmpSubject10(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile("Soggetto_010_clean85.pcd", *tmpSubject10);
    vectorSubject.push_back(tmpSubject10);

    return vectorSubject;
}

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
/*
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
*/
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
/*
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

    distance = registration.getFitnessScore();
    return distance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//implementato nel main (DEPRECATO)
vector<int> getSubject(vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > soggetti, vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > facceTest)
{
    cout << "inizio getSubject..." << endl;
    double SOGLIA = 0.00001; // 10^-5
    vector<int> array;
    for (int j = 0; j < facceTest.size(); j++)
    {
        double min = 2000;
        for (int i = 0; i < soggetti.size(); i++)
        {
            double distanzaTmp = getRegistrationDistance(facceTest[j], soggetti[i]);
            if ( distanzaTmp < min )
            {
                min = distanzaTmp;
                cout << "prima di array[j]..." << endl;
                array[j] = i;
                cout << "dopo di array[j]..." << endl;
                if (min > SOGLIA) array[j] = -1;
                cout << "test " << j << ": " << "sogg. " << array[j] << " DIST. = " << min <<endl;
            }
        }
    }

    return array;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
main (int argc, char** argv)
{
/*
    if (argc < 3)
    {
        cout << "usare ./3dfaceDetect <cloud.pcd> <img.jpg>" << endl;
        return -1;
    }

    char * arg1 = argv[1];  //percorso nuvola
    char * arg2 = argv[2];  //percorso img

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZRGB>);

    cloud2 = findFace3D(arg2, arg1);
    pcl::io::savePCDFile ("extractTest.pcd", *cloud2);  //debug
*/

    vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > vectorFace = findFaceFromDataset(1);
    cout << "DATASET: vector size: " << vectorFace.size() << endl;

    vector< pcl::PointCloud<pcl::PointXYZRGB>::Ptr > vectorSubject = loadSubject();
    cout << "SuBJECT: vector size: " << vectorSubject.size() << endl;

    //double distanza = getRegistrationDistance(vectorFace[18], vectorSubject[3]);
    //cout << "distanza: " << distanza << endl;

    //getSubject(vectorSubject, vectorFace);

    cout << "inizio getSubject..." << endl;
    double SOGLIA = 0.00001; // 10^-5
    //vector<int> array;
    int array[vectorFace.size()];
    for (int j = 0; j < vectorFace.size(); j++)
    {
        cout << "TEST " << j << ": " << endl;
        double min = 2000;
        for (int i = 0; i < vectorSubject.size(); i++)
        {
            double distanzaTmp = getRegistrationDistance(vectorFace[j], vectorSubject[i]);
            cout << " distanza sogg. " << i << ": " << distanzaTmp << endl;
            if ( distanzaTmp < min )
            {
                min = distanzaTmp;
                array[j] = i;
                if (min > SOGLIA) array[j] = -1;
                //cout << "test " << j << ": " << "sogg. " << array[j] << " DIST. = " << min <<endl;
            }
        }
    }


/*
    cout << "inizio gioco:" << endl;

    double distanzaTmp;
    distanzaTmp = getRegistrationDistance(vectorFace[0], vectorSubject[0]);
    cout << distanzaTmp << endl;
    distanzaTmp = getRegistrationDistance(vectorFace[0], vectorSubject[1]);
    cout << distanzaTmp << endl;
    distanzaTmp = getRegistrationDistance(vectorFace[0], vectorSubject[2]);
    cout << distanzaTmp << endl;
    distanzaTmp = getRegistrationDistance(vectorFace[0], vectorSubject[3]);
    cout << distanzaTmp << endl;
*/

    return (0);
}
