#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// create image
	IplImage* img_test = cvCreateImage(cvSize(320, 240), 8, 3);
	cvSet(img_test, cvScalar(0, 255, 0));
	cvShowImage("Create Solid Image", img_test);
	// set black image
	cvZero(img_test);
	cvShowImage("Black Image", img_test);	
	// wait for key pressed
	cvvWaitKey(0);
}