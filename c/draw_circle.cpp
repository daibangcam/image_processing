#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// create image
	IplImage* img_test = cvCreateImage(cvSize(640, 480), 8, 3);
	cvSet(img_test, cvScalar(0, 0, 0));
	cvShowImage("Create Image", img_test);
	// draw circle
	cvCircle(img, cvPoint(300, 300), 100, cvScalar(0, 0, 255), 8, 8, 0);
	cvShowImage("Draw Image", img);
	// wait for key pressed
	cvvWaitKey(0);
}