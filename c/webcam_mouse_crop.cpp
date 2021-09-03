#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
IplImage* frame, *img1, *frame1;
CvPoint point;
int drag = 0;
int chay = 0;
CvCapture *capture = 0;
int key = 0;
CvRect rect;
void mouseHandler(int event, int x, int y, int flags, void* param)
{
	/* user press left button */
	if (event == CV_EVENT_LBUTTONDOWN && !drag)
	{
		point = cvPoint(x, y);// tra ve toa da x , y vua nhan xuong
		drag = 1;
	}
	/* user drag the mouse */
	if (event == CV_EVENT_MOUSEMOVE && drag)
	{
		img1 = cvCloneImage(frame); /* Creates a copy of IPL image (widthStep may differ) */
		cvRectangle(img1, point, cvPoint(x, y), CV_RGB(255, 0, 0), 1, 8, 0);// CV_RGB( 0, 255, 0) : tao vien mau do khi ta doi chuot
		cvShowImage("root", img1);
	}
	/* user release left button */
	if (event == CV_EVENT_LBUTTONUP && drag)
	{
		rect = cvRect(point.x, point.y, x - point.x, y - point.y);// cvRect :Offset (usually the top-left corner) and size of a rectangle.
		cvSetImageROI(frame1, rect);
		cvShowImage("result", frame1);
		drag = 0;
		chay = 1;
	}
	/* user click right button: reset all */
	if (event == CV_EVENT_RBUTTONUP)
	{
		drag = 0;
	}
}
int main(int argc, char *argv[])
{
	//capture = cvCreateFileCapture("D:\Tinh yeu online.mp4");   
	capture = cvCaptureFromCAM(0);
	if (!capture) {
		printf("Cannot open initialize webcam!\n");
		exit(0);
	}
	/* create a window for the video */
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("root", CV_WINDOW_AUTOSIZE);
	while (key != 'q')
	{
		frame = cvQueryFrame(capture);
		frame1 = cvCreateImage(cvSize(frame->width, frame->height), frame->depth, 1);
		cvCvtColor(frame, frame1, CV_RGB2GRAY);
		cvShowImage("root", frame);
		if (rect.width>0)  
		{
			cvSetImageROI(frame1, rect);
		}
		cvSetMouseCallback("root", mouseHandler, NULL);// NULL tuc la chi co vung ROI duoc xu li
		key = cvWaitKey(33); // khi doc video nen chon la 33 de co frame/s thich hop nhat
		if ((char)key == 'r')
		{
			rect = cvRect(0, 0, 0, 0);
			cvResetImageROI(frame1);
			cvDestroyWindow("result");
			cvReleaseImage(&frame1);
			chay = 0;
		}
		if (chay == 1)
		{
			cvShowImage("result", frame1);
		}
	}
	cvDestroyWindow("result");
	cvReleaseImage(&img1);
	cvDestroyWindow("root");
	cvReleaseImage(&frame1);
	return 0;
}