#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	// show image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// convert rgb to gray
	IplImage* img_gray = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, img_gray, CV_BGR2GRAY);
	cvShowImage("Gray Image", img_gray);
	// convert gray to bw
	IplImage* img_bw = cvCreateImage(cvGetSize(img), 8, 1);
	cvThreshold(img_gray, img_bw, 80, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	cvShowImage("BW Image", img_bw);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	cvReleaseImage(&img_gray);
	cvReleaseImage(&img_bw);
	// close window
	cvDestroyAllWindows();
}