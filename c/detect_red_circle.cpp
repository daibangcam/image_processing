#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <string>
#include <sstream>
using namespace std;
int main()
{
	IplImage *original, *imgHSV, *imgThresh, *cut_image;
	original = cvLoadImage("6.png");
	cvNamedWindow("Original");
	cvShowImage("Original", original);
	imgHSV = cvCreateImage(cvGetSize(original), 8, 3);
	cut_image = cvCloneImage(original);
	cvCvtColor(original, imgHSV, CV_BGR2HSV);
	imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
	cvInRangeS(imgHSV, cvScalar(170, 160, 60), cvScalar(180, 256, 256), imgThresh);
	cvThreshold(imgThresh, imgThresh, 230, 255, CV_THRESH_BINARY);
	CvSeq *contours, *result;
	CvMemStorage *storage;
	storage = cvCreateMemStorage(0);
	cvFindContours(imgThresh, storage, &contours, sizeof(CvContour), CV_RETR_LIST,
		CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	CvFont Font;
	cvInitFont(&Font, CV_FONT_HERSHEY_COMPLEX, 0.5, 0.5, 1, 1, 8);
	string str;
	const char *text;
	while (contours)
	{
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
		if (result->total == 8)
		{
			CvPoint *pt[8];
			CvRect rect = cvBoundingRect(contours, 0);
			for (int i = 0; i < 8; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}/*
			 cvLine(original, *pt[0], *pt[1], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[1], *pt[2], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[2], *pt[3], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[3], *pt[4], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[4], *pt[5], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[5], *pt[6], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[6], *pt[7], cvScalar(0, 0, 255), 4);
			 cvLine(original, *pt[7], *pt[0], cvScalar(0, 0, 255), 4);*/
			str = "Red Circle";
			text = str.c_str();
			cvPutText(original, text, cvPoint(rect.x + 5, rect.y + rect.height + 20), &Font, cvScalar(0, 0, 255));
			cvSetImageROI(cut_image, rect);
		}
		contours = contours->h_next;
	}
	cvNamedWindow("Tracked");
	cvShowImage("Tracked", original);
	cvShowImage("Cut Image", cut_image);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseMemStorage(&storage);
	cvReleaseImage(&original);
	cvReleaseImage(&imgThresh);
	return 0;
}