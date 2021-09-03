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

vector<Point> approx;
vector<vector<Point> > contours;

static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void setLabel(Mat& im, const string label, vector<Point>& contour);
void setArea(Mat& im, const string label, vector<Point>& contour);

void find_triangle(Mat& result);
void find_square(Mat& result);
void find_rectangle(Mat& result);
void find_penta(Mat& result);
void find_hexa(Mat& result);
void find_circle(Mat& result);

int main()
{
	// Load image;
	Mat src = imread("5.png");
	// Create image for display
	Mat dst = src.clone();
	// Media Blur
	medianBlur(src, src, 3);
	// Convert input image to HSV
	Mat hsv_image;
	cvtColor(src, hsv_image, cv::COLOR_BGR2HSV);
	// Threshold the HSV image, keep only the red - green - blue pixels
	Mat red_hue_image, blue_hue_image, green_hue_image;
	inRange(hsv_image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), red_hue_image);
	inRange(hsv_image, cv::Scalar(38, 100, 100), cv::Scalar(75, 255, 255), green_hue_image);
	inRange(hsv_image, cv::Scalar(75, 100, 100), cv::Scalar(130, 255, 255), blue_hue_image);
	GaussianBlur(red_hue_image, red_hue_image, cv::Size(9, 9), 2, 2);
	GaussianBlur(green_hue_image, green_hue_image, cv::Size(9, 9), 2, 2);
	GaussianBlur(blue_hue_image, blue_hue_image, cv::Size(9, 9), 2, 2);
	// Find Red Squares
	findContours(red_hue_image.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	find_square(dst);
	// Find Green Rectangles
	findContours(green_hue_image.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	find_rectangle(dst);
	// Find Blue Circles
	findContours(blue_hue_image.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	find_circle(dst);
	// Show result
	imshow("Image", src);
	imshow("Tracked", dst);
	waitKey(0);
	return 0;
}
void setLabel(Mat& im, const string label, vector<Point>& contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.9;
	int thickness = 2.5;
	int baseline = 0;

	Size text = getTextSize(label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + r.width + 10, r.y + r.height / 3);
	rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, label, pt, fontface, scale, CV_RGB(255, 0, 0), thickness, 8);
}
void setArea(Mat& im, const string label, vector<Point>& contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.8;
	int thickness = 2;
	int baseline = 0;
	Size text = getTextSize(label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);
	Point pt1(r.x + r.width + 20, r.y + r.height * 2 / 3);
	rectangle(im, pt1 + Point(0, baseline), pt1 + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, "Area:", pt1, fontface, scale, CV_RGB(150, 0, 255), thickness, 8);
	Point pt2(r.x + r.width + 15, r.y + r.height * 2 / 3 + 30);
	rectangle(im, pt2 + Point(0, baseline), pt2 + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, label, pt2, fontface, scale, CV_RGB(150, 0, 255), thickness, 8);
}

void find_square(Mat& result)
{
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
		if (approx.size() >= 4 && approx.size() <= 6)
		{
			ostringstream ostr;
			int vtc = approx.size();
			std::vector<double> cos;
			for (int j = 2; j < vtc + 1; j++)
				cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));
			std::sort(cos.begin(), cos.end());
			double mincos = cos.front();
			double maxcos = cos.back();
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{
				cv::Rect r = cv::boundingRect(contours[i]);
				double ratio = std::abs(1 - (double)r.width / r.height);
				double area = cv::contourArea(contours[i]);
				ostr << area;
				if (ratio <= 0.02)
				{
					setLabel(result, "SQUARE", contours[i]);
					setArea(result, ostr.str(), contours[i]);
					rectangle(result, r, Scalar(0, 0, 0), 10);
				}
			}
		}
	}
}
void find_rectangle(Mat& result)
{
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
		if (approx.size() >= 4 && approx.size() <= 6)
		{
			ostringstream ostr;
			int vtc = approx.size();
			std::vector<double> cos;
			for (int j = 2; j < vtc + 1; j++)
				cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));
			std::sort(cos.begin(), cos.end());
			double mincos = cos.front();
			double maxcos = cos.back();
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{
				cv::Rect r = cv::boundingRect(contours[i]);
				double ratio = std::abs(1 - (double)r.width / r.height);
				double area = cv::contourArea(contours[i]);
				ostr << area;
				if (ratio > 0.02)
				{
					setLabel(result, "RECTANGLE", contours[i]);
					setArea(result, ostr.str(), contours[i]);
					rectangle(result, r, Scalar(0, 0, 0), 10);
				}
			}
		}
	}
}
void find_circle(Mat& result)
{
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
		if (approx.size() > 6)
		{
			ostringstream ostr;
			double area = cv::contourArea(contours[i]);
			cv::Rect r = cv::boundingRect(contours[i]);
			int radius = r.width / 2;
			Point center = Point(r.x + radius, r.y + radius);
			ostr << area;
			if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
				std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
			{
				setLabel(result, "CIRCLE", contours[i]);
				setArea(result, ostr.str(), contours[i]);
				circle(result, center, radius, Scalar(0, 0, 0), 10);
			}
		}
	}
}

/*
void find_triangle(Mat& result)
{
for (int i = 0; i < contours.size(); i++)
{
approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
continue;
if (approx.size() == 3)
{
setLabel(result, "TRI", contours[i]);
}
}
}
void find_penta(Mat& result)
{
for (int i = 0; i < contours.size(); i++)
{
approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
continue;
if (approx.size() >= 4 && approx.size() <= 6)
{
int vtc = approx.size();
std::vector<double> cos;
for (int j = 2; j < vtc + 1; j++)
cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));
std::sort(cos.begin(), cos.end());
double mincos = cos.front();
double maxcos = cos.back();
if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
setLabel(result, "PENTA", contours[i]);
}
}
}
void find_hexa(Mat& result)
{
for (int i = 0; i < contours.size(); i++)
{
approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
continue;
if (approx.size() >= 4 && approx.size() <= 6)
{
int vtc = approx.size();
std::vector<double> cos;
for (int j = 2; j < vtc + 1; j++)
cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));
std::sort(cos.begin(), cos.end());
double mincos = cos.front();
double maxcos = cos.back();
if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
setLabel(result, "HEXA", contours[i]);
}
}
}
*/