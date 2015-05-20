/*
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;
*/

#include "face.h"

main()
{
    bool haveContribModule = initModule_contrib();
   if (!haveContribModule) {
   cerr << "ERROR: The 'contrib' module is needed for FaceRecognizer but has not been loaded into OpenCV!" << endl;
   exit(1);
   }
    //commentocommentocommento
    //22 aprile


    // holds images and labels
    vector<Mat> images;
    vector<int> labels;

/*
    images.push_back(imread("../data/000_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(0);
    images.push_back(imread("../data/001_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(1);
    images.push_back(imread("../data/002_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(2);
    images.push_back(imread("../data/003_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(3);
    images.push_back(imread("../data/004_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(4);
    images.push_back(imread("../data/005_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(5);
    images.push_back(imread("../data/006_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(6);
    images.push_back(imread("../data/007_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(7);
    images.push_back(imread("../data/008_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(8);
    images.push_back(imread("../data/009_00_image.png", CV_LOAD_IMAGE_GRAYSCALE)); labels.push_back(9);
*/


    images.push_back(imread("../../../face3d/face_00_trained/facciaProva0.jpg")); labels.push_back((0));
   images.push_back(imread("../../../face3d/face_00_trained/facciaProva1.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva2.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva3.jpg")); labels.push_back((0));
    //  images.push_back(imread("../../../face3d/face_00_trained/facciaProva4.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva5.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva6.jpg")); labels.push_back((0));
    //  images.push_back(imread("../../../face3d/face_00_trained/facciaProva7.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva8.jpg")); labels.push_back((0));
    //  images.push_back(imread("../../../face3d/face_00_trained/facciaProva9.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva10.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva11.jpg")); labels.push_back((0));
    images.push_back(imread("../../../face3d/face_00_trained/facciaProva12.jpg")); labels.push_back((0));



    images.push_back(imread("../../../face3d/face_01_trained/facciaProva0.jpg")); labels.push_back((1));
    //  images.push_back(imread("../../../face3d/face_01_trained/facciaProva1.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva2.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva3.jpg")); labels.push_back((1));
    //  images.push_back(imread("../../../face3d/face_01_trained/facciaProva4.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva5.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva6.jpg")); labels.push_back((1));
    //  images.push_back(imread("../../../face3d/face_01_trained/facciaProva7.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva8.jpg")); labels.push_back((1));
    //  images.push_back(imread("../../../face3d/face_01_trained/facciaProva9.jpg")); labels.push_back((1));
    //  images.push_back(imread("../../../face3d/face_01_trained/facciaProva10.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva11.jpg")); labels.push_back((1));
    images.push_back(imread("../../../face3d/face_01_trained/facciaProva12.jpg")); labels.push_back((1));


    images.push_back(imread("../../../face3d/face_09_trained/facciaProva0.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva1.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva2.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva3.jpg")); labels.push_back((9));
    //  images.push_back(imread("../../../face3d/face_09_trained/facciaProva4.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva5.jpg")); labels.push_back((9));
    //  images.push_back(imread("../../../face3d/face_09_trained/facciaProva6.jpg")); labels.push_back((9));
    //  images.push_back(imread("../../../face3d/face_09_trained/facciaProva7.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva8.jpg")); labels.push_back((9));
    //  images.push_back(imread("../../../face3d/face_09_trained/facciaProva9.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva10.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva11.jpg")); labels.push_back((9));
    images.push_back(imread("../../../face3d/face_09_trained/facciaProva12.jpg")); labels.push_back((9));


    images.push_back(imread("../../../face3d/face_10_trained/facciaProva0.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva1.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva2.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva3.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva4.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva5.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva6.jpg")); labels.push_back((10));
    //  images.push_back(imread("../../../face3d/face_10_trained/facciaProva7.jpg")); labels.push_back((10));
    //  images.push_back(imread("../../../face3d/face_10_trained/facciaProva8.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva9.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva10.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva11.jpg")); labels.push_back((10));
    images.push_back(imread("../../../face3d/face_10_trained/facciaProva12.jpg")); labels.push_back((10));













    cout << "elementi: " << images.size() <<endl;
/*    namedWindow("originale111");
    imshow("originale111", images[3]);
    waitKey(0);
*/

    Ptr<FaceRecognizer> model =  createFisherFaceRecognizer();
    model->train(images, labels);

    cout << "train: ok" <<endl;

    //queste img non vanno bene perchè devono essere della stessa dimensione del training set 70x70
    Mat img1 = imread("../../../face3d/face_01_trained/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img2 = imread("../../../face3d/face_09_trained/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    //Mat img1 = imread("../../../face3d/face_10_trained/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //Mat img2 = imread("../../../face3d/face_10_trained/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);

/*    imshow("aaa", img1);
    waitKey(0);
*/
    int predicted_label = -1;
    double predicted_confidence = 0.0;
    // And get a prediction from the cv::FaceRecognizer:
    model->predict(img1, predicted_label, predicted_confidence);

    cout << "fig1-predicted label: " << predicted_label <<" confidence: " << predicted_confidence <<endl;

    int predicted_label2 = -1;
    double predicted_confidence2 = 0.0;
    model->predict(img2, predicted_label2, predicted_confidence2);

    cout << "fig2-predicted label: " << predicted_label2 <<" confidence: " << predicted_confidence2 <<endl;






    return 0;
}
