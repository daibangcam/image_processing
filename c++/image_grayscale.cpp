#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void main()
{
	// load image 
	Mat img = imread("1.jpg");
	imshow("RGB Image", img);
	// convert rgb to gray
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	imshow("Gray Image", img_gray);
	// wait for a pressed key
	cvWaitKey(0);
}