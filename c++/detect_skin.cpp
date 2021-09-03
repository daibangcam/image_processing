#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	Mat frame;
	VideoCapture cap;
	//cap.open(0);
	cap.open("1.mp4");
	// create a window called "HSV trackbar"
	namedWindow("HSV trackbar",CV_WINDOW_FREERATIO);
	int iLowH = 0;
	int iHighH = 20;
	int iLowS = 10;
	int iHighS = 200;
	int iLowV = 120;
	int iHighV = 255;
	//Create trackbars in "HSV trackbar" window
	cvCreateTrackbar("Low H", "HSV trackbar", &iLowH, 255);
	cvCreateTrackbar("High H", "HSV trackbar", &iHighH, 255);
	cvCreateTrackbar("Low S", "HSV trackbar", &iLowS, 255);
	cvCreateTrackbar("High S", "HSV trackbar", &iHighS, 255);
	cvCreateTrackbar("Low V", "HSV trackbar", &iLowV, 255);
	cvCreateTrackbar("High V", "HSV trackbar", &iHighV, 255);
	//
	Mat frame_hsv;
	Mat frame_threshold;
	//
	while (1)
	{
		cap.read(frame);
		if (frame.empty()) break;
		imshow("Live", frame);
		cvtColor(frame, frame_hsv, CV_BGR2HSV);
		inRange(frame_hsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), frame_threshold);
		imshow("Humanskin", frame_threshold);
		char c = waitKey(33);
		if (c == 27) break;
	}
	destroyAllWindows;
}