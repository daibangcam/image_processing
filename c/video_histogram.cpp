#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
int main()
{
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* src = NULL;
	IplImage* hist = NULL;
	while (1)
	{
		src = cvQueryFrame(capture);
		if (!src) break;
		char c = cvWaitKey(33);
		if (c == 27) break;
		IplImage* r_hist = cvCreateImage(cvGetSize(src), 8, 1);
		IplImage* g_hist = cvCreateImage(cvGetSize(src), 8, 1);
		IplImage* b_hist = cvCreateImage(cvGetSize(src), 8, 1);
		hist = cvCreateImage(cvGetSize(src), 8, 3);
		//Tach thanh 3 ma tran mau r g b
		cvSplit(src, r_hist, g_hist, b_hist, NULL); 
		// can bang Histogram cho r_color
		cvEqualizeHist(r_hist, r_hist); 
		// can bang Histogram cho g_color
		cvEqualizeHist(g_hist, g_hist); 
		// can bang Histogram cho b_color
		cvEqualizeHist(b_hist, b_hist); 
		//Ghep 3 ma tran mau lai thanh anh
		cvMerge(r_hist, g_hist, b_hist, NULL, hist); 
		cvShowImage("Webcam", src);
		cvShowImage("Histogram", hist);
	}
	cvReleaseImage(&src);
	cvReleaseImage(&hist);
	cvDestroyAllWindows;
	return 0;
}