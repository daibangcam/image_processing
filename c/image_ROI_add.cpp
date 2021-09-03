#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	// show image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// add blue ROI
	int x = 190;
	int y = 50;
	int width = 230;
	int height = 250;
	int add = 100;
	cvSetImageROI(img, cvRect(x, y, width, height));
	cvAddS(img, cvScalar(add), img);
	cvResetImageROI(img);
	cvShowImage("Add blue ROI Image", img);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	// close window
	cvDestroyAllWindows();
}