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
	Mat src = imread("2.png");
	if (src.empty())
		return -1;
	// Convert to grayscale
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	// Use Canny instead of threshold to catch squares with gradient shading
	Mat bw;
	Canny(gray, bw, 0, 50, 5);
	// Find contours
	vector<vector<Point> > contours;
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	// The array for storing the approximation curve
	vector<Point> approx;
	// We'll put the labels in this destination image
	Mat dst = cvCreateMat(src.rows, src.cols, CV_8UC3);
	for (int i = 0; i<dst.cols * 3; i++)
		for (int j = 0; j<dst.rows; j++)
			dst.at<uchar>(Point(i, j)) = 255;
	// loop
	for (int i = 0; i < contours.size(); i++)
	{
		// Approximate contour with accuracy proportional
		// to the contour perimeter
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		// Skip small or non-convex objects 
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
		// Circle
		if (approx.size() > 6)
		{
			double area = contourArea(contours[i]);
			Rect r = boundingRect(contours[i]);
			int radius = r.width / 2;

			if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&
				abs(1 - (area / (CV_PI * pow(radius, 2)))) <= 0.2)
			{
				Rect roi = Rect(r.x, r.y, r.width, r.height);
				Mat roi_img = src(roi);
				roi_img.copyTo(dst(roi));
			}
		}
	}
	imshow("Image", src);
	imshow("Circles Image", dst);
	/////////////////////////////////////////////////////////////
	// Close
	waitKey(0);
	return 0; // yea, c++, no cleanup nessecary!
}