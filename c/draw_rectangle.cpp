#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// create white image
	IplImage* img = cvCreateImage(cvSize(640, 480), 8, 3);
	cvSet(img, cvScalar(255, 255, 255));
	cvShowImage("Image", img);
	// draw rectangle
	cvRectangle(img, cvPoint(200, 200), cvPoint(600, 400), cvScalar(0, 0, 255), 10);
	cvShowImage("Draw Image", img);
	// wait for key pressed
	cvvWaitKey(0);
}