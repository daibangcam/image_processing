#include <opencv2/opencv.hpp>
#include "cv.h"
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
	CvCapture* capture = cvCaptureFromCAM(0);
	IplImage* src = NULL;
	IplImage* srcwc = NULL;
	cvNamedWindow("Webcam", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("WebcamHistogram", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Webcam_contrast", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("WebcamSmooth", CV_WINDOW_AUTOSIZE);
	IplImage* frame = cvQueryFrame(capture);
	IplImage* hsv = cvCreateImage(cvGetSize(frame), 8, 3);
	IplImage* smooth = cvCreateImage(cvGetSize(frame), 8, 3);
	IplImage* h_plane = cvCreateImage(cvGetSize(frame), 8, 1);
	//into one of several sup-plied single-channel images
	IplImage* s_plane = cvCreateImage(cvGetSize(frame), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(frame), 8, 1);
	IplImage* planes[] = { h_plane, s_plane };
	IplImage* h_plane_1 = cvCreateImage(cvGetSize(frame), 8, 1);
	IplImage* s_plane_1 = cvCreateImage(cvGetSize(frame), 8, 1);
	IplImage* v_plane_1 = cvCreateImage(cvGetSize(frame), 8, 1);
	// Quantize the hue to 30 levels
	// and the saturation to 32 levels
	int h_bins = 30, s_bins = 32, scale = 10;
	//parameter 1: width and height
	IplImage* hist_img = cvCreateImage(cvSize(h_bins * scale, s_bins * scale), 8, 3);   
	//parameter 2: chiều sâu của pixel theo bit
	//parameter 3: số kênh, các hàm của OpenCV  đều hỗ trợ từ 1-4 kênh.
	cvZero(hist_img);
	while (1)
	{
		src = cvQueryFrame(capture); /* Just a combination of cvGrabFrame and cvRetrieveFrame!!!DO NOT RELEASE or MODIFY the retrieved frame!!!      */
		if (!src) break; // khong thu duoc capture => break.
		srcwc = src;
		cvSmooth(src, smooth, CV_BLUR, 5, 3);/* Smoothes array (removes noise) */ // lam tron mang, loai bo nhieu
		//CV_BLUR : linear convolution with size1xsize2  box kernel (all 1’s) with subsequent scaling by  1/[size1xsize2]
		cvCvtColor(src, hsv, CV_BGR2HSV); // chuyen doi mau
		//The function converts an input image from one color space to another
		cvCvtPixToPlane(hsv, h_plane, s_plane, v_plane, 0);// #define cvCvtPixToPlane cvSplit
		/* cvSplit : Splits ( chia ra, tach ra) a multi-channel array into the set of single-channel arrays or
		extracts particular [color] plane */
		/* Equalize the histogram */
		//cvEqualizeHist(h_plane,h_plane_1);
		/* Equalize the histogram */
		//cvEqualizeHist(s_plane,s_plane_1);
		/* Equalize the histogram */
		cvEqualizeHist(v_plane, v_plane_1); // v la thanh phan cuong do sang cua ma tran anh HSV, do vay ta chi equalize thanh phan nay ma thoi
		cvCvtPlaneToPix(h_plane, s_plane, v_plane_1, 0, hsv);
		cvCvtColor(hsv, hsv, CV_HSV2BGR);
		cvSmooth(hsv, smooth, CV_BLUR, 5, 3);
		CvHistogram* hist;
		{
			int    hist_size[] = { h_bins, s_bins };
			float  h_ranges[] = { 0, 100 };          // day la nguong hue, thay doi theo mong muon
			float  s_ranges[] = { 0, 250 };
			float* ranges[] = { h_ranges, s_ranges };
			hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1); ///* Creates new histogram */ //The function creates a histogram of the specified size and returns a pointer to the created histogram
			//parameter 1: kich thuoc mong muon <=> so phan tu
			//parameter 2: mang chua tri integer ma chieu dai bang voi parm 1
			/*parameter 3: - CV_HIST_ARRAY : su dung cho multidimensional histograms.dense array CvMatND
			- CV_HIST_SPARSE : 	means that histogram data is represented as a multi-dimensional sparse array CvSparseMat */
			//parameter 4: chiều sâu của pixel theo bit
			//parameter 5 số kênh, các hàm của OpenCV  đều hỗ trợ từ 1-4 kênh.
		}
		cvCalcHist(planes, hist, 0, 0); /* Calculates array histogram */
		/*In the case of a multi-channel image (e.g., HSV or RGB) we will have to cvSplit() that image into planes before call-ing cvCalcHist(),
		so this is the reason why we have to use cvSplit() above */
		//parameter 1:  Source arrays. o day da dung cvSplit de tach ra thanh single-demension
		/*parameter 2: hist – Output histogram, which is a dense or sparse dims -dimensional array*/
		//parameter 3: 
		//parameter 4:
		float max_value = 0;
		cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0); ///* Finds indices and values of minimum and maximum histogram bins */
		for (int h = 0; h < h_bins; h++)
		{
			for (int s = 0; s < s_bins; s++)
			{
				float bin_val = cvQueryHistValue_2D(hist, h, s);
				int intensity = cvRound(bin_val * 255 / max_value);
				cvRectangle(hist_img, cvPoint(h*scale, s*scale), cvPoint((h + 1)*scale - 1, (s + 1)*scale - 1), CV_RGB(intensity, intensity, intensity), CV_FILLED);
			}
		}
		//cvFlip(smooth,smooth,0);
		//cvFlip(hsv,hsv,0);
		char c = cvWaitKey(10);
		if (c == 27) break;
		cvShowImage("Webcam", srcwc);
		cvShowImage("WebcamSmooth", smooth);
		cvShowImage("Webcam_contrast", hsv);
		cvShowImage("WebcamHistogram", hist_img);
	}
	cvReleaseCapture(&capture);
	destroyAllWindows;
	return 0;
}