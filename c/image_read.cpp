#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	// show image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	// close window
	cvDestroyWindow("Image");
}