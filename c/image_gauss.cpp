#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	cvShowImage("RGB Image", img);
	// smooth image
	IplImage* img_smooth = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvSmooth(img, img_smooth, CV_GAUSSIAN, 3, 3);
	cvShowImage("Smooth Image", img_smooth);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	// close window
	cvDestroyAllWindows();
}