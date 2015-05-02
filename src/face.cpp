#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

main()
{

    //carico il descrittore pre il face detector
    char const * faceCascadeFilename = "/home/enrico/opencv-2.4.9/data/lbpcascades/lbpcascade_frontalface.xml";
    CascadeClassifier faceDetector;
    try {
        faceDetector.load(faceCascadeFilename);
    } catch (cv::Exception e) {}
    if ( faceDetector.empty() ) {
        cerr << "ERROR: Couldn't load Face Detector (";
        cerr << faceCascadeFilename << ")!" << endl;
        exit(1);
    }
    cout << "descrittore caricato: " << faceCascadeFilename <<endl;


    //carico l'img in b/n:
    Mat img = imread("000_00_image.png", CV_LOAD_IMAGE_GRAYSCALE);
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", img );
    waitKey(0);
/*
    //ora la scalo per ragioni di prestazioni:                  //sta parte per ora non la implemento
    const int DETECTION_WIDTH = 320;
    // Possibly shrink the image, to run much faster.
    Mat smallImg;
    float scale = img.cols / (float) DETECTION_WIDTH;
    if (img.cols > DETECTION_WIDTH) {
        // Shrink the image while keeping the same aspect ratio.
        int scaledHeight = cvRound(img.rows / scale);
        resize(img, smallImg, Size(DETECTION_WIDTH, scaledHeight));
    }
    else {
        // Access the input directly since it is already small.
        smallImg = img;
    }
    namedWindow( "Display window2", WINDOW_AUTOSIZE );
    imshow( "Display window2", smallImg );
    waitKey(0);
*/
    // faccio equalizeHist per omogeneizzare il contrasto e la luminosità:
    Mat equalizedImg;
    equalizeHist(img, equalizedImg);


    //ora posso usare detectMultiScale() per trovare la faccia nell'immagine:
    int flags = CASCADE_FIND_BIGGEST_OBJECT;    //cerco una sola faccia
    Size minFeatureSize(80, 80);                //size minima in pixel della faccia
    float searchScaleFactor = 1.1f;             //su quante scale cercare (1.1 oppure 1.2)
    int minNeighbors = 4;                       //Reliability vs many faces
    std::vector<Rect> faces;                    //param di uscita, circonda la faccia
    faceDetector.detectMultiScale(equalizedImg, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);


    //namedWindow( "Display window4", WINDOW_AUTOSIZE );
    imshow( "Display window4", equalizedImg(faces[0]) );
    waitKey(0);


    rectangle(equalizedImg,faces[0],Scalar( 0, 55, 255 ), +1, 4 );
    imshow( "Display window5", equalizedImg );
    waitKey(0);
    
    
    //ora ho la regione della faccia. trovo gli occhi
    
    //TO-DO      carico il descrittore pre l'eye detector
    char const * faceCascadeFilename = "/home/enrico/opencv-2.4.9/data/lbpcascades/lbpcascade_frontalface.xml";
    CascadeClassifier faceDetector;
    try {
        faceDetector.load(faceCascadeFilename);
    } catch (cv::Exception e) {}
    if ( faceDetector.empty() ) {
        cerr << "ERROR: Couldn't load Face Detector (";
        cerr << faceCascadeFilename << ")!" << endl;
        exit(1);
    }
    cout << "descrittore caricato: " << faceCascadeFilename <<endl;
    



    return 0;
}
