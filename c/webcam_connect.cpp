#include <opencv/cv.h>
#include <opencv/highgui.h>
void main()
{
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* src;
	while (1)
	{
		src = cvQueryFrame(capture);
		if (!src) break;
		char c = cvWaitKey(33);
		if (c == 27) break;
		cvShowImage("Webcam", src);
	}
	cvReleaseImage(&src);
	cvDestroyWindow("Webcam");
}