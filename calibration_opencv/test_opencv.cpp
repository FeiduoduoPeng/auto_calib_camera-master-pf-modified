#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("lena.jpg");
    //Mat img = Mat::zeros(123,250,CV_8UC3);
    imshow("b", img);
    waitKey(0);
    return 0;
}
