#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	cvShowImage("RGB Image", img);
	// pyrdown image
	assert(img->width % 2 == 0 && img->height % 2 == 0);
	IplImage* img_pyrdown = cvCreateImage(cvSize(img->width / 2, img->height / 2), img->depth, img->nChannels);
	cvPyrDown(img, img_pyrdown, IPL_GAUSSIAN_5x5);
	cvShowImage("Pyrdown Image", img_pyrdown);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	// close window
	cvDestroyAllWindows();
}