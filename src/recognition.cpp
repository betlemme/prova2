#include "detection.h"

/* Legge il dataset e cerca le facce
 * Stampa i risultati.
 *
 * -train() :creo l'oggetto Facerecognizer già trainato con le facce del set di persone da riconoscere
 * -detectFacesOnTest() : crea il vettore di facce trovate nel set di testing
 * -faccio il predict e ricostruisco la faccia per misurare la similarità con la faccia campione.
 *
 * -purtroppo non riesce a ricostruire bene le facce, mi accontento del parametro della distanza
 *
 */



//restituisco il vettore contenente le facce 70x70(140x140) trovate nel dataset di testing. int dataset = [1 2 3 4]
vector<Mat> detectFacesOnTest(int dataset){
    vector<Mat> setImages;

    if (dataset == 1)
    {
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/000_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/001_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/002_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/003_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/004_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/005_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/006_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/007_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/008_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/009_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/010_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/011_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/012_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/013_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/014_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/015_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/016_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/017_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/018_00_image.png", CV_LOAD_IMAGE_GRAYSCALE));

       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/000_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/001_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/002_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/003_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/004_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/005_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/006_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/007_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/008_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/009_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/010_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/011_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/012_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/013_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/014_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/015_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/016_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/017_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test1/018_07_image.png", CV_LOAD_IMAGE_GRAYSCALE));
    }

    if (dataset == 2)
    {
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/000_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/001_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/002_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/003_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/004_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/005_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/006_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/007_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/008_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/009_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/010_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/011_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/012_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/013_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/014_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/015_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/016_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/017_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test2/018_09_image.png", CV_LOAD_IMAGE_GRAYSCALE));
    }

    if (dataset == 3)
    {
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/000_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/001_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/002_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/003_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/004_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/005_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/006_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/007_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/008_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/009_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/010_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/011_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/012_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/013_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/014_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/015_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/016_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/017_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/018_05_image.png", CV_LOAD_IMAGE_GRAYSCALE));

       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/000_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/001_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/002_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/003_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/004_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/005_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/006_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/007_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/008_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/009_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/010_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/011_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/012_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/013_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/014_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/015_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/016_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/017_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test3/018_06_image.png", CV_LOAD_IMAGE_GRAYSCALE));
    }

    if (dataset == 4)
    {
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/000_01_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/001_02_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/002_03_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/003_04_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/004_01_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/005_02_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/006_03_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/007_04_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/008_01_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/009_02_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/010_03_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/011_04_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/012_01_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/013_02_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/014_03_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/015_04_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/016_01_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/017_02_image.png", CV_LOAD_IMAGE_GRAYSCALE));
       setImages.push_back(imread("../../../face3d/RGBD_Face_dataset_testing/Test4/018_03_image.png", CV_LOAD_IMAGE_GRAYSCALE));
    }

       Mat img;

       for (int i = 0; i < setImages.size(); i++)
       {
           //img = detectSimple(setImages[i]);

           //applico maschera:
           img = ellipseMask(detectSimple(setImages[i]));

           imshow("aaaa", img);
           waitKey(0);
           setImages[i] = img;

       }



    return setImages;
}

//aggiungo una immagine e la sua copia speculare al vettore(con rispettivo label) per il training
void pushPreProcImg(Mat preProcImg, int label, vector<Mat>& images, vector<int>& labels)
{
    Mat mirroredFace;
    flip(preProcImg, mirroredFace, 1);

    images.push_back(preProcImg); labels.push_back(label);
    imshow("aa", preProcImg);
    waitKey(0);

    images.push_back(mirroredFace); labels.push_back(label);
    imshow("aa", mirroredFace);
    waitKey(0);
}

Ptr<FaceRecognizer> train()
{
    // holds images and labels
    vector<Mat> images;
    vector<int> labels;
/*    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 00
    Mat soggetto0;


    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);


    /////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 01

    Mat soggetto1;
    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 09

    Mat soggetto9;

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);



    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 10

    Mat soggetto10;

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 00
    Mat soggetto0;


    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    //soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    //soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    //soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);

    soggetto0 = imread("../../../face3d/face_00_trained2/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto0, 0, images, labels);


   /////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 01

    Mat soggetto1;
    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    //soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    //soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    //soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    //soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto1, 1, images, labels);

    //soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    soggetto1 = imread("../../../face3d/face_01_trained2/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto1, 1, images, labels);

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 09

    Mat soggetto9;

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);



    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    //soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    //soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto9, 9, images, labels);

    //soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    //soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    soggetto9 = imread("../../../face3d/face_09_trained2/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto9, 9, images, labels);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //soggetto 10

    Mat soggetto10;

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva0.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva6.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    //soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva7.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    //pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva8.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva9.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva10.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva11.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);

    soggetto10 = imread("../../../face3d/face_10_trained2/facciaProva12.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    pushPreProcImg(soggetto10, 10, images, labels);



    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

     Ptr<FaceRecognizer> model;

     // Make sure the "contrib" module is dynamically loaded at runtime.
     // Requires OpenCV v2.4.1 or later (from June 2012), otherwise the FaceRecognizer will not compile or run!
     bool haveContribModule = initModule_contrib();
     if (!haveContribModule) {
     cerr << "ERROR: The 'contrib' module is needed for FaceRecognizer but has not been loaded into OpenCV!" << endl;
     exit(1);
     }

     // Use the new FaceRecognizer class in OpenCV's "contrib" module:
     // Requires OpenCV v2.4.1 or later (from June 2012), otherwise the FaceRecognizer will not compile or run!
     model = Algorithm::create<FaceRecognizer>("FaceRecognizer.Eigenfaces");
     if (model.empty()) {
     cerr << "ERROR: The FaceRecognizer algorithm [" << "FaceRecognizer.Eigenfaces" << "] is not available in your version of OpenCV. Please update to OpenCV v2.4.1 or newer." << endl;
     exit(1);
     }

      model->train(images, labels);

      cout << "train OK"  << endl;

      return model;
}

// Generate an approximately reconstructed face by back-projecting the eigenvectors & eigenvalues of the given (preprocessed) face.
Mat reconstructFace(const Ptr<FaceRecognizer> model, const Mat preprocessedFace)
{
    // Get some required data from the FaceRecognizer model.
    Mat eigenvectors = model->get<Mat>("eigenvectors");
    Mat averageFaceRow = model->get<Mat>("mean");
    int faceHeight = preprocessedFace.rows;

    // Project the input image onto the PCA subspace.
    Mat projection = subspaceProject(eigenvectors, averageFaceRow, preprocessedFace.reshape(1,1));
    //printMatInfo(projection, "projection");
    // Generate the reconstructed face back from the PCA subspace.
    Mat reconstructionRow = subspaceReconstruct(eigenvectors, averageFaceRow, projection);
    //printMatInfo(reconstructionRow, "reconstructionRow");
    // Convert the float row matrix to a regular 8-bit image. Note that we
    // shouldn't use "getImageFrom1DFloatMat()" because we don't want to normalize
    // the data since it is already at the perfect scale.
    // Make it a rectangular shaped image instead of a single row.
    Mat reconstructionMat = reconstructionRow.reshape(1, faceHeight);
    // Convert the floating-point pixels to regular 8-bit uchar pixels.
    Mat reconstructedFace = Mat(reconstructionMat.size(), CV_8U);
    reconstructionMat.convertTo(reconstructedFace, CV_8U, 1, 0);
    //printMatInfo(reconstructedFace, "reconstructedFace");
    return reconstructedFace;
}


// Compare two images by getting the L2 error (square-root of sum of squared error) (lo uso per confrontare la faccia ricostruita con quella originale)
double getSimilarity(const Mat A, const Mat B)
{
    if (A.rows > 0 && A.rows == B.rows && A.cols > 0 && A.cols == B.cols) {
        // Calculate the L2 relative error between the 2 images.
        double errorL2 = norm(A, B, CV_L2);
        // Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
        double similarity = errorL2 / (double)(A.rows * A.cols);
        return similarity;
    }
    else {
        //cout << "WARNING: Images have a different size in 'getSimilarity()'." << endl;
        return 100000000.0; // Return a bad value
    }
}

int main()
{

      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      //creo l'oggetto Facerecognizer già trainato con le facce del set di persone da riconoscere:
      Ptr<FaceRecognizer> model = train();

      // da dataset:
      vector<Mat> vec = detectFacesOnTest(1);

      int label[vec.size()] ;
      double confidence[vec.size()];

      for (int i = 0; i < vec.size(); i++)
      {
          model->predict(vec[i], label[i], confidence[i]);

          Mat reconstructedFace = reconstructFace(model,vec[i]);

          imshow("ricostruzione", reconstructedFace);
          waitKey(0);


          // Verify whether the reconstructed face looks like the preprocessed face, otherwise it is probably an unknown person.
          double similarity = getSimilarity(vec[i], reconstructedFace);
          int falso = 0;
          if (similarity > 0.5) {
              falso = -1;
              // Unknown person.
          }


          cout << "persona " << i << ": " << label[i] << "; confidenza: " << confidence[i] << "similarità: " << falso << endl;

      }



    return 1;
}
