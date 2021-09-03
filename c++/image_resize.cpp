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
	// resize image 100% width, height --> fx = 100% = 1, fy = 50% = 0.5
	Mat img_resize_1;
	resize(img, img_resize_1, Size(), 0.5, 0.5, INTER_NEAREST);
	imshow("Resize Image 1", img_resize_1);
	// resize image  -> fixed size: width = 300, height = 100
	Mat img_resize_2;
	resize(img, img_resize_2, Size(300, 100), 0, 0, INTER_NEAREST);
	imshow("Resize Image 2", img_resize_2);
	// wait for a pressed key
	cvWaitKey(0);
}