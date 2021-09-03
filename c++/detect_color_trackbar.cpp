#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat img = imread("7.png");
	imshow("Image", img);

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	int iLowH = 0;
	int iHighH = 255;
	int iLowS = 0;
	int iHighS = 255;
	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (1)
	{
		// convert HSV
		Mat img_HSV;
		cvtColor(img, img_HSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
		Mat img_thresholded;
		inRange(img_HSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), img_thresholded); //Threshold the image
		//morphological opening (remove small objects from the foreground)
		erode(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		//morphological closing (fill small holes in the foreground)
		dilate(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(img_thresholded, img_thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		//show the thresholded image
		imshow("Thresholded Image", img_thresholded);
		//show the original image
		imshow("Original", img);
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}		
	}
	return 0;
}