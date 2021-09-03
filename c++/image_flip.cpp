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
	// flip image
	Mat img_flip_h, img_flip_v, img_flip_hv;
	flip(img, img_flip_h, 0);
	imshow("Flip horizontal Image", img_flip_h);
	flip(img, img_flip_v, 1);
	imshow("Flip vertical Image", img_flip_v);
	flip(img, img_flip_hv, -1);
	imshow("Flip horizontal vertical Image", img_flip_hv);
	// wait for a pressed key
	cvWaitKey(0);
}