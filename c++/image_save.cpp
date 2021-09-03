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
	// save image
	imwrite("2.jpg", img);
	// wait for a pressed key
	cvWaitKey(0);
}