#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Histogram Equalize seperately for the left and right sides of the face.
void equalizeLeftAndRightHalves(Mat &faceImg)
{
    // It is common that there is stronger light from one half of the face than the other. In that case,
    // if you simply did histogram equalization on the whole face then it would make one half dark and
    // one half bright. So we will do histogram equalization separately on each face half, so they will
    // both look similar on average. But this would cause a sharp edge in the middle of the face, because
    // the left half and right half would be suddenly different. So we also histogram equalize the whole
    // image, and in the middle part we blend the 3 images together for a smooth brightness transition.
    int w = faceImg.cols;
    int h = faceImg.rows;
    // 1) First, equalize the whole face.
    Mat wholeFace;
    equalizeHist(faceImg, wholeFace);
    // 2) Equalize the left half and the right half of the face separately.
    int midX = w/2;
    Mat leftSide = faceImg(Rect(0,0, midX,h));
    Mat rightSide = faceImg(Rect(midX,0, w-midX,h));
    equalizeHist(leftSide, leftSide);
    equalizeHist(rightSide, rightSide);
    // 3) Combine the left half and right half and whole face together, so that it has a smooth transition.
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            int v;
            if (x < w/4) { // Left 25%: just use the left face.
                v = leftSide.at<uchar>(y,x);
            }
            else if (x < w*2/4) { // Mid-left 25%: blend the left face & whole face.
                int lv = leftSide.at<uchar>(y,x);
                int wv = wholeFace.at<uchar>(y,x);
                // Blend more of the whole face as it moves further right along the face.
                float f = (x - w*1/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * lv + (f) * wv);
            }
            else if (x < w*3/4) { // Mid-right 25%: blend the right face & whole face.
                int rv = rightSide.at<uchar>(y,x-midX);
                int wv = wholeFace.at<uchar>(y,x);
                // Blend more of the right-side face as it moves further right along the face.
                float f = (x - w*2/4) / (float)(w*0.25f);
                v = cvRound((1.0f - f) * wv + (f) * rv);
            }
            else { // Right 25%: just use the right face.
                v = rightSide.at<uchar>(y,x-midX);
            }
            faceImg.at<uchar>(y,x) = v;
        }// end x loop
    }//end y loop
}

Mat normalize(Mat source)
{
    Mat out;
    char const * frontaleLBP = "/home/enrico/opencv-2.4.9/data/lbpcascades/lbpcascade_frontalface.xml";
    char const * frontaleHAAR = "/home/enrico/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_default.xml";
    char const * profilo ="/home/enrico/opencv-2.4.9/data/haarcascades/haarcascade_profileface.xml";

    //carico il descrittore pre il face detector (haar: /home/enrico/opencv-2.4.9/data/haarcascades/haarcascade_frontalface_default.xml)
    char const * faceCascadeFilename = frontaleLBP;
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
    Mat img = source;
    //Mat img = imread("000_00_image.png", CV_LOAD_IMAGE_GRAYSCALE);
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
    float searchScaleFactor = 1.3f;             //su quante scale cercare (1.1 oppure 1.2) piu alto è piu è veloce, ma trova meno facce
    int minNeighbors = 4;                       //Reliability vs many faces
    std::vector<Rect> faces;                    //param di uscita, circonda la faccia
    faceDetector.detectMultiScale(equalizedImg, faces, searchScaleFactor, minNeighbors, flags, minFeatureSize);

    if (faces.size() < 1)
    {
        cout << "nessuna faccia trovata" << endl;

        return out;
    }
    //namedWindow( "Display window4", WINDOW_AUTOSIZE );
    imshow( "Display window4", equalizedImg(faces[0]) );
    waitKey(0);


    rectangle(equalizedImg,faces[0],Scalar( 0, 55, 255 ), +1, 4 );
    imshow( "Display window5", equalizedImg );
    waitKey(0);
    
    
    //ora ho la regione della faccia. trovo gli occhi
    
    //carico il descrittore pre l'eye detector
    char const * eyeCascadeFilename = "/home/enrico/opencv-2.4.9/data/haarcascades/haarcascade_eye.xml";
    CascadeClassifier eyeDetector;
    try {
        eyeDetector.load(eyeCascadeFilename);
    } catch (cv::Exception e) {}
    if ( eyeDetector.empty() ) {
        cerr << "ERROR: Couldn't load eye Detector (";
        cerr << eyeCascadeFilename << ")!" << endl;
        exit(1);
    }
    cout << "descrittore caricato: " << eyeCascadeFilename <<endl;

    //trovo la regione della faccia in cui cercare l'occhio per restringere il campo di ricerca (parametri empirici):
    Mat face = equalizedImg(faces[0]);

    float EYE_SX = 0.16;
    float EYE_SY = 0.26;
    float EYE_SW = 0.30;
    float EYE_SH = 0.28;


    int leftX = cvRound(face.cols * EYE_SX);
    int topY = cvRound(face.rows * EYE_SY);
    int widthX = cvRound(face.cols * EYE_SW);
    int heightY = cvRound(face.rows * EYE_SH);
    int rightX = cvRound(face.cols * (1.0-EYE_SX-EYE_SW));

    Mat topLeftOfFace = face(Rect(leftX, topY, widthX, heightY));
    Mat topRightOfFace = face(Rect(rightX, topY, widthX, heightY));

   //    imshow( "Display window6", topLeftOfFace );
   //    imshow( "Display window6", topRightOfFace );
   //    waitKey(0);

    Rect leftEyeRect, rightEyeRect; //conterranno le regioni degli occhi

    //avvio la ricerca (sinistro):
    int flags2 = CASCADE_FIND_BIGGEST_OBJECT;    //cerco una sola faccia
    Size minFeatureSize2(20, 20);                //size minima in pixel della faccia
    float searchScaleFactor2 = 1.3f;             //su quante scale cercare (1.1 oppure 1.2) piu alto è piu è veloce, ma trova meno facce
    int minNeighbors2 = 4;                       //Reliability vs many faces
    std::vector<Rect> eyesL;                    //param di uscita, circonda l'occhio
    std::vector<Rect> eyesR;                    //param di uscita, circonda l'occhio
    eyeDetector.detectMultiScale(topLeftOfFace, eyesL, searchScaleFactor2, minNeighbors2, flags2, minFeatureSize2);
    eyeDetector.detectMultiScale(topRightOfFace, eyesR, searchScaleFactor2, minNeighbors2, flags2, minFeatureSize2);

    leftEyeRect = eyesL[0];
    rightEyeRect = eyesR[0];

    Point leftEye, rightEye;

    //debug:
    if (eyesL.size() < 1)
    {
        cout << "nessuna occhio L trovata" << endl;

    }

    if (eyesR.size() < 1)
    {
        cout << "nessuna occhio L trovata" << endl;

    }

    if (leftEyeRect.width > 0) //se ho trovato l'occhio
    {
        leftEyeRect.x += leftX; // Adjust the left-eye rectangle because the face border was removed.
        leftEyeRect.y += topY;
        leftEye = Point(leftEyeRect.x + leftEyeRect.width/2, leftEyeRect.y + leftEyeRect.height/2);
    }
    else {
        leftEye = Point(-1, -1); // Return an invalid point
    }

    if (rightEyeRect.width > 0)
    { // Check if the eye was detected.
        rightEyeRect.x += rightX; // Adjust the right-eye rectangle, since it starts on the right side of the image.
        rightEyeRect.y += topY; // Adjust the right-eye rectangle because the face border was removed.
        rightEye = Point(rightEyeRect.x + rightEyeRect.width/2, rightEyeRect.y + rightEyeRect.height/2);
    }
    else {
        rightEye = Point(-1, -1); // Return an invalid point
    }

    circle( face, leftEye, 16.0, Scalar( 0, 0, 255 ), 1, 8 );
    circle( face, rightEye, 16.0, Scalar( 0, 0, 255 ), 1, 8 );
    
    imshow( "Display window5", face );
    //  imshow( "Display window5", equalizedImg );  per mostrare i rettangli nella foto originale

    waitKey(0);

/*
To have better alignment we will use eye detection to align the face so the positions of the two detected
eyes line up perfectly in desired positions. We will do the geometrical transformation using the
warpAffine() function, which is a single operation that will do four things:
-Rotate the face so that the two eyes are horizontal.
-Scale the face so that the distance between the two eyes is always the same.
-Translate the face so that the eyes are always centered horizontally and at a desired height.
-Crop the outer parts of the face, since we want to crop away the image background, hair,
 forehead, ears, and chin.
*/

    // trovo il centro tra i 2 occhi:
    Point2f eyesCenter;
    eyesCenter.x = (leftEye.x + rightEye.x) * 0.5f;
    eyesCenter.y = (leftEye.y + rightEye.y) * 0.5f;

    // ora trovo l'angolo di inclinazione del segmento che ha per estremi gli occhi
    double dy = (rightEye.y - leftEye.y);
    double dx = (rightEye.x - leftEye.x);
    double len = sqrt(dx*dx + dy*dy);
    // Convert Radians to Degrees.
    double angle = atan2(dy, dx) * 180.0/CV_PI;

    // Hand measurements shown that the left eye center should ideally be at roughly (0.19, 0.14) of a scaled face image.
    const double DESIRED_LEFT_EYE_X = 0.16;
    const double DESIRED_LEFT_EYE_Y = 0.14;
    const int desiredFaceWidth = 70; // DESIRED_FACE_WIDTH
    const int desiredFaceHeight = 70;//DESIRED_FACE_HEIGHT
    const double DESIRED_RIGHT_EYE_X = (1.0f - DESIRED_LEFT_EYE_X);
    // Get the amount we need to scale the image to be the desired fixed size we want.
    double desiredLen = (DESIRED_RIGHT_EYE_X - DESIRED_LEFT_EYE_X) * desiredFaceWidth;
    double scale = desiredLen / len;

    // Get the transformation matrix for rotating and scaling the face to the desired angle & size.
   Mat rot_mat = getRotationMatrix2D(eyesCenter, angle, scale);
   // Shift the center of the eyes to be the desired center between the eyes.
   rot_mat.at<double>(0, 2) += desiredFaceWidth * 0.5f - eyesCenter.x;
   rot_mat.at<double>(1, 2) += desiredFaceHeight * DESIRED_LEFT_EYE_Y - eyesCenter.y;

   // Rotate and scale and translate the image to the desired angle & size & position!
   // Note that we use 'w' for the height instead of 'h', because the input face has 1:1 aspect ratio.
   Mat warped = Mat(desiredFaceHeight, desiredFaceWidth, CV_8U, Scalar(128)); // Clear the output image to a default grey.
   warpAffine(img(faces[0]), warped, rot_mat, warped.size());

   equalizeLeftAndRightHalves(warped);

   imshow("warped", warped);
   waitKey(0);

   // Use the "Bilateral Filter" to reduce pixel noise by smoothing the image, but keeping the sharp edges in the face.
   Mat filtered = Mat(warped.size(), CV_8U);
   bilateralFilter(warped, filtered, 0, 20.0, 2.0);

   imshow("filtered", filtered);
   waitKey(0);

   imwrite( "faceFiltered.jpg", filtered );




    return filtered;
}

int main()
{
    Mat img = imread("000_00_image.png", CV_LOAD_IMAGE_GRAYSCALE);
    Mat out = normalize(img);

    cout << "evviva!" <<endl;
    imshow("out", out);
    waitKey(0);
    return 0;
}

