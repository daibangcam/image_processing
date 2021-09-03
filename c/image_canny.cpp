#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	cvShowImage("RGB Image", img);
	// convert rgb to gray
	IplImage* img_gray = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, img_gray, CV_BGR2GRAY);
	cvShowImage("Gray Image", img_gray);
	// canny
	int lowThresh = 10;
	int highThresh = 50;
	int aperture = 3;
	IplImage* img_canny = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCanny(img_gray, img_canny, lowThresh, highThresh, aperture);
	cvShowImage("Canny", img_canny);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	// close window
	cvDestroyAllWindows();
}