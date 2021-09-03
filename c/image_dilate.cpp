#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");	
	// convert to gray
	IplImage * img_gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage * img_dilate = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, img_gray, CV_RGB2GRAY);
	cvErode(img_gray, img_dilate, 0, 1);
	// show original image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// show dilation image
	cvNamedWindow("Dilation Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Dilation Image", img_dilate);
	// wait for a pressed key
	cvWaitKey(0);
	// close window
	cvDestroyAllWindows();
}