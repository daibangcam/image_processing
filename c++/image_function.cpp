#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void hufi_bw(Mat& src, Mat& dst, int threshold_value);

void main()
{
	// C++ load image 
	Mat img = imread("1.jpg");
	imshow("RGB Image", img);
	// call function hufi_bw
	Mat img_bw;
	hufi_bw(img, img_bw, 120);
	imshow("BW Image", img_bw);
	// wait for a pressed key
	cvWaitKey(0);
}
void hufi_bw(Mat& src, Mat& dst, int threshold_value)
{
	// C++ convert rgb to gray 
	Mat img_gray;
	cvtColor(src, img_gray, COLOR_BGR2GRAY);
	// C++ convert gray to bw
	threshold(img_gray, dst, threshold_value, 255, THRESH_BINARY);
}