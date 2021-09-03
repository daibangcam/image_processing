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
	// kernel
	double a[25] = { 2, 0, -2, -2, 2, 0, 2, 0, 2, -2, -2, 0, 4, 0, -2, -2, 2, 0, 2, 0, 2, -2, -2, 0, 2 };
	double b[25] = { 2, -2, -2, 0, 2, -2, 2, 0, 2, 0, -2, 0, 4, 0, -2, 0, 2, 0, 2, -2, 2, 0, -2, -2, 2 };
	CvMat kernel1 = cvMat(5, 5, CV_64FC1, a);		//kernel 5x5 
	CvMat kernel2 = cvMat(5, 5, CV_64FC1, b);		//kernel 5x5
	IplImage* out1 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* out2 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* img_kernel = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvFilter2D(img_gray, out1, &kernel1, cvPoint(-1, -1));
	cvFilter2D(img_gray, out2, &kernel2, cvPoint(-1, -1));
	cvShowImage("Kernel 1", out1);
	cvShowImage("Kernel 2", out2);
	cvMul(out1, out2, img_kernel, 10);
	cvShowImage("Kernel Image", img_kernel);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	// close window
	cvDestroyAllWindows();
}