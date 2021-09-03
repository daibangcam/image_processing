#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	CvCapture* clip = cvCaptureFromFile("1.avi");
	IplImage* img;
	while (1)
	{
		img = cvQueryFrame(clip);
		cvShowImage("video", img);
		if (!img) break;
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
}