#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include <sstream>
#include <string>
IplImage* GetThresholdedImage(IplImage* imgHSV)
{
	/*
	Color Filter
	*/
	IplImage* imgThresh = cvCreateImage(cvGetSize(imgHSV), IPL_DEPTH_8U, 1);
	cvInRangeS(imgHSV, cvScalar(0, 230, 110), cvScalar(10, 256, 256), imgThresh);
	return imgThresh;
}
int main()
{
	/*
	First Step: Color Filter
	Second Step: Extract triangles using Contours
	*/
	IplImage * src = cvLoadImage("5.png");
	IplImage * imgresult = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
	cvCopy(src, imgresult);
	//Load image 
	//== init font 
	CvFont font;
	cvInitFont(&font, CV_FONT_ITALIC, 0.4, 0.2);
	IplImage* imgHSV = cvCreateImage(cvGetSize(imgresult), IPL_DEPTH_8U, 3);
	std::ostringstream ostr;
	std::string str;
	const char  *text;
	//create HSV image for Color Filter
	IplImage* imgR = cvCreateImage(cvGetSize(imgresult), IPL_DEPTH_8U, 1);
	IplImage* imgG = cvCreateImage(cvGetSize(imgresult), IPL_DEPTH_8U, 1);
	IplImage* imgB = cvCreateImage(cvGetSize(imgresult), IPL_DEPTH_8U, 1);
	//imgR, imgG and imgB are used for extract color features from original image
	//== Start of Color Filter 
	cvCvtColor(imgresult, imgHSV, CV_BGR2HSV);
	IplImage* imgThresh = GetThresholdedImage(imgHSV);
	cvSplit(imgresult, imgR, imgG, imgB, NULL);
	cvMul(imgThresh, imgR, imgR);
	cvMul(imgThresh, imgG, imgG);
	cvMul(imgThresh, imgB, imgB);
	cvMerge(imgR, imgG, imgB, NULL, imgresult);
	//==End of Color Filter
	//== Start of finding contours
	IplImage* mask = cvCreateImage(cvGetSize(imgresult), IPL_DEPTH_8U, 1);
	cvZero(mask);
	CvSeq* contours;
	CvSeq* result;
	CvMemStorage *storage = cvCreateMemStorage(0);
	cvFindContours(imgThresh, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	while (contours)
	{
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
		if (result->total == 3)
		{
			CvRect rect = cvBoundingRect(contours, 0);
			cvSetImageROI(mask, rect);
			cvSet(mask, cvScalar(1));
			cvResetImageROI(mask);
		}
		contours = contours->h_next;
	}
	cvMul(mask, imgR, imgR);
	cvMul(mask, imgG, imgG);
	cvMul(mask, imgB, imgB);
	cvMerge(imgR, imgG, imgB, NULL, imgresult);
	//== End of finding contours
	//== Calculate area and perimeter of triangles
	cvFindContours(imgThresh, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	while (contours)
	{
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
		if (result->total == 3)
		{
			CvRect rect = cvBoundingRect(contours, 0);
			double area = fabs(cvContourArea(contours, CV_WHOLE_SEQ));
			ostr << area;
			str = "Area: " + ostr.str();
			text = str.c_str();
			ostr.str("");
			cvPutText(imgresult, text, cvPoint(rect.x, rect.y + rect.height + 5), &font, CV_RGB(255, 0, 0));
			double perimeter = cvArcLength(contours);
			ostr << perimeter;
			str = "Perimeter: " + ostr.str();
			text = str.c_str();
			ostr.str("");
			cvPutText(imgresult, text, cvPoint(rect.x, rect.y + rect.height + 15), &font, CV_RGB(255, 0, 0));
		}
		contours = contours->h_next;
	}
	//== Display
	cvSaveImage("result.png", imgresult);
	cvNamedWindow("Image Input");
	cvNamedWindow("Image Output");
	cvShowImage("Image Input", src);
	cvShowImage("Image Output", imgresult);
	cvWaitKey();
	cvDestroyAllWindows();
	return 0;
}