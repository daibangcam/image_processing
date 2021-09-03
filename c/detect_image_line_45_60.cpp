#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

int main()
{
	double a[209] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564,
		0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0,
		0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0,
		0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0,
		0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0,
		0, 0, 0, 0, 0.02564, 0.02564, 0.02564, 0, 0, 0, 0,
		0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0,
		0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0,
		0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0,
		0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0,
		0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	double b[209] = { 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0.02564, 0.02564, 0.02564, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0.02564, 0.02564
	};
	double c[25] = { 0.2, 0, 0, 0, 0,
		0, 0.2, 0, 0, 0,
		0, 0, 0.2, 0, 0,
		0, 0, 0, 0.2, 0,
		0, 0, 0, 0, 0.2
	};
	double d[25] = { 0, 0, 0, 0, 0.2,
		0, 0, 0, 0.2, 0,
		0, 0, 0.2, 0, 0,
		0, 0.2, 0, 0, 0,
		0.2, 0, 0, 0, 0
	};
	CvMat kernel1 = cvMat(19, 11, CV_64FC1, a); // Goc 60
	CvMat kernel2 = cvMat(19, 11, CV_64FC1, b); // Goc -60
	CvMat kernel3 = cvMat(5, 5, CV_64FC1, c); // Goc -45
	CvMat kernel4 = cvMat(5, 5, CV_64FC1, d); // Goc 45
	IplImage* img = cvLoadImage("4.png");
	IplImage* gray = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* out1 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* out2 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* out3 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* out4 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* result = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, gray, CV_RGB2GRAY); // chuyen doi anh mau sang anh xam
	cvNot(gray, gray); // convert graysacle
	cvFilter2D(gray, out1, &kernel1, cvPoint(-1, -1));
	cvFilter2D(gray, out2, &kernel2, cvPoint(-1, -1));
	cvFilter2D(gray, out3, &kernel3, cvPoint(-1, -1));
	cvFilter2D(gray, out4, &kernel4, cvPoint(-1, -1));
	cvThreshold(out1, out1, 140, 255, CV_THRESH_BINARY);
	cvThreshold(out2, out2, 140, 255, CV_THRESH_BINARY);
	cvThreshold(out3, out3, 200, 255, CV_THRESH_BINARY);
	cvThreshold(out4, out4, 200, 255, CV_THRESH_BINARY);
	cvAdd(out1, out2, result);
	cvAdd(out4, result, result);
	cvAdd(out3, result, result);
	cvNot(result, result);
	cvNamedWindow("anhgoc", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Result", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Goc 60", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Goc -60", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Goc -45", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Goc 45", CV_WINDOW_AUTOSIZE);
	cvShowImage("anhgoc", img);
	cvShowImage("Goc 60", out1);
	cvShowImage("Goc -60", out2);
	cvShowImage("Goc -45", out3);
	cvShowImage("Goc 45", out4);
	cvShowImage("Result", result);
	cvWaitKey();
	cvReleaseImage(&img);
	cvReleaseImage(&out1);
	cvReleaseImage(&out2);
	cvReleaseImage(&out3);
	cvReleaseImage(&out4);
	cvDestroyAllWindows;
	return 0;
}