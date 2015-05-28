#include "detection.h"

#include <cstdlib>




int main(int argc, char ** argv)
{
    int j = atoi(argv[1]);
    const char * array[13];

    if(j==10)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/010_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/010_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/010_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/010_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/010_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/010_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/010_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/010_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/010_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/010_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/010_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/010_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/010_12_image.png";
    }

    if(j==9)
    {
        array[0] = "../../../face3d/RGBD_Face_dataset_training/009_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/009_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/009_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/009_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/009_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/009_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/009_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/009_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/009_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/009_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/009_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/009_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/009_12_image.png";
    }

    if(j==1)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/001_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/001_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/001_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/001_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/001_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/001_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/001_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/001_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/001_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/001_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/001_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/001_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/001_12_image.png";

    }

    if(j==0)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/000_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/000_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/000_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/000_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/000_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/000_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/000_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/000_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/000_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/000_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/000_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/000_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/000_12_image.png";
    }


        Mat img, out;
        for (int i = 0; i < 13; i++)
        {
            cout << array[i] << endl;
            img = imread(array[i], CV_LOAD_IMAGE_GRAYSCALE);
            out = detectSimple(img);


            stringstream ss;
            if(j==0) ss << "../../../face3d/face_00_trained2/"<< "facciaProva" << i << ".jpg";
            if(j==1) ss << "../../../face3d/face_01_trained2/"<< "facciaProva" << i << ".jpg";
            if(j==9) ss << "../../../face3d/face_09_trained2/"<< "facciaProva" << i << ".jpg";
            if(j==10) ss << "../../../face3d/face_10_trained2/"<< "facciaProva" << i << ".jpg";


            const string str = ss.str();
            const char* cstr = str.c_str();

            imwrite( cstr, out );


        }


    return 0;
}
