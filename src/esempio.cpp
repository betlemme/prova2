#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

main()
{
    //commentocommentocommento

    // holds images and labels
    vector<Mat> images;
    vector<int> labels;


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

    cout << "elementi: " << images.size() <<endl;
    namedWindow("originale111");
    imshow("originale111", images[3]);
    waitKey(0);

    Ptr<FaceRecognizer> model =  createEigenFaceRecognizer();
    model->train(images, labels);

    Mat img1 = imread("000_02_image.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat img2 = imread("017_08_image.png", CV_LOAD_IMAGE_GRAYSCALE);

    int predicted_label = -1;
    double predicted_confidence = 0.0;
    // And get a prediction from the cv::FaceRecognizer:
    model->predict(img1, predicted_label, predicted_confidence);

    int predicted_label2 = -1;
    double predicted_confidence2 = 0.0;
    model->predict(img2, predicted_label2, predicted_confidence2);

    cout << "fig1-predicted label: " << predicted_label <<" confidence: " << predicted_confidence <<endl;
    cout << "fig2-predicted label: " << predicted_label2 <<" confidence: " << predicted_confidence2 <<endl;



    return 0;
}
