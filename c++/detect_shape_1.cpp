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
	if (src.empty())
		return -1;
	// Create image for display
	Mat dst = src.clone();
	// Find Contours
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	Mat bw;
	Canny(gray, bw, 0, 50, 5);
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	// Find Triangles
	find_triangle(dst);
	// Find Squares
	find_square(dst);
	// Find Rectangles
	find_rectangle(dst);
	// Find Pentas
	find_penta(dst);
	// Find Hexas
	find_hexa(dst);
	// Find Circles
	find_circle(dst);
	// Show result
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}
void setLabel(Mat& im, const string label, vector<Point>& contour)
{
	int fontface = FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	Size text = getTextSize(label, fontface, scale, thickness, &baseline);
	Rect r = boundingRect(contour);

	Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

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
void find_square(Mat& result)
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
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{
				// Detect rectangle or square
				cv::Rect r = cv::boundingRect(contours[i]);
				double ratio = std::abs(1 - (double)r.width / r.height);
				if (ratio <= 0.02)
					setLabel(result, "SQU", contours[i]);
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
			int vtc = approx.size();
			std::vector<double> cos;
			for (int j = 2; j < vtc + 1; j++)
				cos.push_back(angle(approx[j%vtc], approx[j - 2], approx[j - 1]));
			std::sort(cos.begin(), cos.end());
			double mincos = cos.front();
			double maxcos = cos.back();
			if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
			{
				// Detect rectangle or square
				cv::Rect r = cv::boundingRect(contours[i]);
				double ratio = std::abs(1 - (double)r.width / r.height);
				if (ratio > 0.02)
					setLabel(result, "RECT", contours[i]);
			}
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
void find_circle(Mat& result)
{
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
		if (approx.size() > 6)
		{
			double area = cv::contourArea(contours[i]);
			cv::Rect r = cv::boundingRect(contours[i]);
			int radius = r.width / 2;
			if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
				std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
				setLabel(result, "CIR", contours[i]);
		}
	}
}