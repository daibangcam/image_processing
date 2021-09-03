#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	// show image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// resize image
	IplImage* img_resize = cvCreateImage(cvSize(img->width / 2, img->height / 2), 8, 3);
	cvResize(img, img_resize, 1);
	cvShowImage("Resize Image", img_resize);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	cvReleaseImage(&img_resize);
	// close window
	cvDestroyAllWindows();
}