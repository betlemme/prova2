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
Rect detectRect(Mat source);

