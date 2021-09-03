#include <highgui.h>
#include <cv.h>
#include <opencv2/opencv.hpp>
void main()
{
	// ma tran cho Average Filter
	double a[9] = { 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111, 0.1111 };
	// ma tran x cho Sobel Filter
	double b[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 }; 
	// ma tran y cho Sobel Filter
	double c[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	// tao ma tran loc 3x3
	CvMat averfil = cvMat(3, 3, CV_64FC1, a);
	CvMat sobel_x = cvMat(3, 3, CV_64FC1, b);
	CvMat sobel_y = cvMat(3, 3, CV_64FC1, c);
	// doc file video
	CvCapture* capture = cvCreateFileCapture("1.mp4");
	IplImage* src = cvQueryFrame(capture);
	IplImage* gray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	IplImage* aver = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	IplImage* sobelx = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	IplImage* sobely = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	IplImage* sobel = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	while (1)
	{
		src = cvQueryFrame(capture);
		if (!src) break;
		// chuyen thanh anh Gray
		cvCvtColor(src, gray, CV_RGB2GRAY);
		// su dung bo loc average
		cvFilter2D(gray, aver, &averfil, cvPoint(-1, -1));
		// su dung bo loc sobel x
		cvFilter2D(gray, sobelx, &sobel_x, cvPoint(-1, -1));
		// su dung bo loc sobel y
		cvFilter2D(gray, sobely, &sobel_y, cvPoint(-1, -1));
		// gop 2 bo loc sobel x & y
		cvMul(sobelx, sobely, sobel, 10);
		// hien thi ket qua
		cvShowImage("Webcam", src);
		cvShowImage("Webcam_Gray", gray);
		cvShowImage("Webcam_Average", aver);
		cvShowImage("Webcam_Sobel", sobel);
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
	cvReleaseImage(&src);
	cvReleaseImage(&gray);
	cvReleaseImage(&aver);
	cvReleaseImage(&sobel);
}