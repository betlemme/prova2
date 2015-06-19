#include "detection.h"
/*
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

Mat detect(Mat source);
Mat detectSimple(Mat source);
Mat ellipseMask(Mat face);

*/

#include <cstdlib>
#include<stdio.h>

/*
 * Crea e salva nella rispettiva cartella le facce estrapolate dal dataset di training
 *
 *
 *
 * */




int main(int argc, char ** argv)
{
    int j = atoi(argv[1]);      //deve essere di 3 cifre: 010, 000,...
    const char * array[13];

/*
    string pathBeginning("../../../face3d/RGBD_Face_dataset_training/");
    string persona = argv[1]; //010, ...
    string pathMiddle("_0");
    string pathMiddle2("_");
    string posa;                //00, 01, 02, ... 11, 12;
    string pathLast("_image.png");


    stringstream sspath;

    for (int i = 0; i < 13; i++)
    {
        if (i <10)
        {
            sspath << pathBeginning << persona << pathMiddle << i << pathLast;
        }
        else
        {
            sspath << pathBeginning << persona << pathMiddle2 << i << pathLast;
        }

            const string str = sspath.str();
            const char* cstr = str.c_str();

            array[i] = cstr;


    }

    for (int i=0; i<13; i++)
    {
        cout << array[i] << endl;
    }


    cout << "ho caricato l'array" << endl;
*/


    if(j==26)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/026_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/026_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/026_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/026_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/026_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/026_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/026_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/026_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/026_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/026_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/026_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/026_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/026_12_image.png";
    }

    if(j==25)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/025_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/025_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/025_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/025_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/025_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/025_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/025_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/025_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/025_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/025_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/025_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/025_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/025_12_image.png";
    }

    if(j==24)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/024_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/024_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/024_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/024_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/024_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/024_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/024_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/024_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/024_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/024_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/024_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/024_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/024_12_image.png";
    }

    if(j==23)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/023_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/023_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/023_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/023_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/023_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/023_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/023_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/023_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/023_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/023_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/023_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/023_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/023_12_image.png";
    }

    if(j==22)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/022_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/022_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/022_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/022_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/022_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/022_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/022_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/022_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/022_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/022_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/022_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/022_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/022_12_image.png";
    }

    if(j==21)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/021_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/021_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/021_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/021_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/021_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/021_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/021_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/021_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/021_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/021_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/021_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/021_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/021_12_image.png";
    }

    if(j==20)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/020_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/020_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/020_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/020_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/020_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/020_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/020_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/020_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/020_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/020_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/020_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/020_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/020_12_image.png";
    }

    if(j==19)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/019_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/019_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/019_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/019_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/019_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/019_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/019_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/019_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/019_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/019_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/019_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/019_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/019_12_image.png";
    }

    if(j==18)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/018_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/018_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/018_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/018_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/018_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/018_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/018_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/018_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/018_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/018_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/018_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/018_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/018_12_image.png";
    }

    if(j==17)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/017_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/017_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/017_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/017_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/017_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/017_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/017_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/017_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/017_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/017_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/017_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/017_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/017_12_image.png";
    }

    if(j==16)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/016_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/016_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/016_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/016_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/016_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/016_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/016_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/016_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/016_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/016_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/016_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/016_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/016_12_image.png";
    }

    if(j==15)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/015_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/015_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/015_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/015_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/015_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/015_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/015_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/015_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/015_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/015_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/015_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/015_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/015_12_image.png";
    }

    if(j==14)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/014_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/014_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/014_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/014_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/014_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/014_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/014_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/014_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/014_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/014_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/014_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/014_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/014_12_image.png";
    }

    if(j==13)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/013_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/013_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/013_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/013_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/013_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/013_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/013_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/013_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/013_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/013_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/013_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/013_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/013_12_image.png";
    }

    if(j==12)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/012_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/012_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/012_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/012_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/012_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/012_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/012_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/012_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/012_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/012_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/012_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/012_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/012_12_image.png";
    }

    if(j==11)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/011_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/011_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/011_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/011_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/011_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/011_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/011_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/011_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/011_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/011_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/011_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/011_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/011_12_image.png";
    }

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


    if(j==8)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/008_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/008_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/008_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/008_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/008_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/008_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/008_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/008_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/008_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/008_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/008_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/008_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/008_12_image.png";

    }

    if(j==7)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/007_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/007_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/007_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/007_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/007_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/007_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/007_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/007_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/007_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/007_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/007_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/007_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/007_12_image.png";

    }

    if(j==6)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/006_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/006_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/006_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/006_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/006_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/006_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/006_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/006_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/006_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/006_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/006_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/006_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/006_12_image.png";

    }

    if(j==5)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/005_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/005_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/005_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/005_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/005_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/005_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/005_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/005_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/005_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/005_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/005_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/005_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/005_12_image.png";

    }

    if(j==4)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/004_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/004_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/004_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/004_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/004_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/004_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/004_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/004_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/004_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/004_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/004_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/004_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/004_12_image.png";

    }

    if(j==3)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/003_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/003_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/003_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/003_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/003_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/003_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/003_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/003_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/003_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/003_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/003_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/003_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/003_12_image.png";

    }

    if(j==2)
    {

        array[0] = "../../../face3d/RGBD_Face_dataset_training/002_00_image.png";
        array[1] = "../../../face3d/RGBD_Face_dataset_training/002_01_image.png";
        array[2] = "../../../face3d/RGBD_Face_dataset_training/002_02_image.png";
        array[3] = "../../../face3d/RGBD_Face_dataset_training/002_03_image.png";
        array[4] = "../../../face3d/RGBD_Face_dataset_training/002_04_image.png";
        array[5] = "../../../face3d/RGBD_Face_dataset_training/002_05_image.png";
        array[6] = "../../../face3d/RGBD_Face_dataset_training/002_06_image.png";
        array[7] = "../../../face3d/RGBD_Face_dataset_training/002_07_image.png";
        array[8] = "../../../face3d/RGBD_Face_dataset_training/002_08_image.png";
        array[9] = "../../../face3d/RGBD_Face_dataset_training/002_09_image.png";
        array[10] = "../../../face3d/RGBD_Face_dataset_training/002_10_image.png";
        array[11] = "../../../face3d/RGBD_Face_dataset_training/002_11_image.png";
        array[12] = "../../../face3d/RGBD_Face_dataset_training/002_12_image.png";

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

            if(j==0) ss << "../../../face3d/face_00_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==1) ss << "../../../face3d/face_01_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==2) ss << "../../../face3d/face_02_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==3) ss << "../../../face3d/face_03_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==4) ss << "../../../face3d/face_04_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==5) ss << "../../../face3d/face_05_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==6) ss << "../../../face3d/face_06_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==7) ss << "../../../face3d/face_07_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==8) ss << "../../../face3d/face_08_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==9) ss << "../../../face3d/face_09_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==10) ss << "../../../face3d/face_10_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==11) ss << "../../../face3d/face_11_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==12) ss << "../../../face3d/face_12_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==13) ss << "../../../face3d/face_13_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==14) ss << "../../../face3d/face_14_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==15) ss << "../../../face3d/face_15_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==16) ss << "../../../face3d/face_16_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==17) ss << "../../../face3d/face_17_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==18) ss << "../../../face3d/face_18_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==19) ss << "../../../face3d/face_19_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==20) ss << "../../../face3d/face_20_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==21) ss << "../../../face3d/face_21_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==22) ss << "../../../face3d/face_22_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==23) ss << "../../../face3d/face_23_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==24) ss << "../../../face3d/face_24_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==25) ss << "../../../face3d/face_25_trained3/"<< "facciaProva" << i << ".jpg";
            if(j==26) ss << "../../../face3d/face_26_trained3/"<< "facciaProva" << i << ".jpg";


            //ss << "../../../face3d/face_" << persona << "_trained3/" << "facciaProva" << i << ".jpg";



            const string str = ss.str();
            const char* cstr = str.c_str();

            imwrite( cstr, out );


        }


    return 0;
}
