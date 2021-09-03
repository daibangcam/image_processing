#include "cv.h"
#include "stdio.h"
#include "cxcore.h"
#include "highgui.h"
#include <iostream>
#include <opencv2/opencv.hpp>
CvHaarClassifierCascade *cascade;
CvMemStorage *storage;
void detectFaces(IplImage *img);
using namespace std;
using namespace cv;
int main()
{
	// load image
	IplImage* src = cvLoadImage("3.png");
	cvShowImage("Original", src);
	// init classifier
	char *filename = "haarcascade_frontalface_alt2.xml";
	// load the classifier
	cascade = (CvHaarClassifierCascade*)cvLoad(filename, 0, 0, 0);
	// setup memory buffer; needed by thappears e face detector
	storage = cvCreateMemStorage(0);
	// detect faces
	detectFaces(src);
	cvShowImage("Face Detection", src);
	cvWaitKey(0);
	destroyAllWindows;
	return 0;
}
void detectFaces(IplImage *img)
{
	int i;
	/* detect faces */
	CvSeq *faces = cvHaarDetectObjects(img, cascade, storage, 1.1, 3, 0 /*CV_HAAR_DO_CANNY_PRUNNING*/, cvSize(40, 40));
	/* for each face found, draw a red box */
	for (i = 0; i < (faces ? faces->total : 0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
		cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(255, 0, 0), 1, 8, 0);
	}
}