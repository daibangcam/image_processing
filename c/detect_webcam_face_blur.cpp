#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;
using namespace cv;

CvHaarClassifierCascade *cascade;
CvMemStorage *storage;

int key;

void detectFaces(IplImage *img);
int main(int argc, char** argv)
{
	CvCapture *capture;
	IplImage *frame;
	char *filename = "haarcascade_frontalface_alt2.xml";
	// load the classifier
	cascade = (CvHaarClassifierCascade*)cvLoad(filename, 0, 0, 0);
	// setup memory buffer; needed by thappears e face detector
	storage = cvCreateMemStorage(0);
	// initialize camera
	capture = cvCaptureFromCAM(0);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
	// always check camera
	assert(cascade && storage && capture);
	// init video writer
	CvVideoWriter* writer = cvCreateVideoWriter("wc_detect_face.avi",
		CV_FOURCC('M', 'J', 'P', 'G'),
		10, cvSize(320, 240));
	// create a window
	cvNamedWindow("Webcam_detect_blur_faces", 1);
	while (key != 27)
	{
		// get a frame
		frame = cvQueryFrame(capture);
		// always check
		if (!frame) break;
		// detect faces and display video
		detectFaces(frame);
		// write video
		cvWriteFrame(writer, frame);
		// quit if user press ESC
		key = cvWaitKey(5);
	}
	/* free memory */
	cvReleaseCapture(&capture);
	cvDestroyWindow("video");
	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseMemStorage(&storage);
	return 0;
}
void detectFaces(IplImage *img)
{
	int i;
	/* detect faces */
	CvSeq *faces = cvHaarDetectObjects(img,
		cascade,
		storage,
		1.1,
		3,
		0 /*CV_HAAR_DO_CANNY_PRUNNING*/,
		cvSize(40, 40));
	/* for each face found, draw a red box */
	for (i = 0; i < (faces ? faces->total : 0); i++)
	{
		CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
		/* cvRectangle(img,
		cvPoint(r->x, r->y),
		cvPoint(r->x + r->width, r->y + r->height),
		CV_RGB(255, 0, 0), 1, 8, 0); */
		cvSetImageROI(img, cvRect(r->x, r->y, r->width, r->height));
		for (int i = 1; i < 20; i++)
		{
			cvSmooth(img, img, CV_BLUR, 5, 3);
		}
		cvResetImageROI(img);
	}
	// display video
	cvShowImage("Webcam_detect_blur_faces", img);
}