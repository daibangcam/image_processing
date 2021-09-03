#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("image.png");
	imshow("Image", src);
	// Tao image moi co cung kich thuoc voi image goc
	Mat dst = cvCreateMat(src.rows,src.cols, CV_8UC3);
	for (int i = 0; i<dst.cols*3; i++)
	for (int j = 0; j<dst.rows; j++)
	dst.at<uchar>(Point(i, j)) = 255;
	//Nhan dang hinh tron dung thuat toan Hough
	Mat gray, circle_only;
	circle_only = Mat::zeros(src.rows, src.cols, CV_8UC3);
	cvtColor(src, gray, CV_BGR2GRAY);
	//Giam nhieu de tranh nhan sai anh
	GaussianBlur(gray, gray, Size(9, 9), 2, 2);
	vector<Vec3f> circles;
	//Dung thuat toan Hough
	HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 30, 100, 50, 0, 0);
	//Ve hinh tron ra image moi
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		Rect roi = Rect(center.x-radius, center.y-radius, radius*2.1, radius*2.1);
		Mat roi_img = src(roi);
		roi_img.copyTo(dst(roi));
		imshow("Circle Image", dst);
	}	
	/////////////////////////////////////////////////////////////
	// Close
	waitKey(0);
	return 0; // yea, c++, no cleanup nessecary!
}