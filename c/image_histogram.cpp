#include "opencv/cv.h"
#include "opencv/highgui.h"
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");			
	// Compute HSV image and separate into colors
	IplImage* back_img = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	IplImage* hsv = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCvtColor(img, hsv, CV_BGR2HSV);
	IplImage* h_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* s_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(img), 8, 1);
	IplImage* planes[] = { h_plane, s_plane };
	cvCvtPixToPlane(hsv, h_plane, s_plane, v_plane, 0);
	// Build and fill the histogram 
	int h_bins = 30, s_bins = 32;
	CvHistogram* hist;
	{
		int hist_size[] = { h_bins, s_bins };
		float h_ranges[] = { 0, 180 };
		float s_ranges[] = { 0, 255 };
		float* ranges[] = { h_ranges, s_ranges };
		hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
	}
	// compute histogram
	cvCalcHist(planes, hist, 0, 0); 
	// normalize it 
	cvNormalizeHist(hist, 20 * 255); 
	// calculate back projection 
	cvCalcBackProject(planes, back_img, hist);
	// normalize it
	cvNormalizeHist(hist, 1.0); 
	// create an image to visualize the histogram 
	int scale = 10;
	IplImage* hist_img = cvCreateImage(cvSize(h_bins * scale, s_bins * scale), 8, 3);
	cvZero(hist_img);
	// populate the visualization 
	float max_value = 0;
	cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);
	for (int h = 0; h < h_bins; h++)
	{
		for (int s = 0; s < s_bins; s++)
		{
			float bin_val = cvQueryHistValue_2D(hist, h, s);
			int intensity = cvRound(bin_val * 255 / max_value);
			cvRectangle(hist_img, cvPoint(h*scale, s*scale),
				cvPoint((h + 1)*scale - 1, (s + 1)*scale - 1),
				CV_RGB(intensity, intensity, intensity),
				CV_FILLED);
		}
	}
	// show original image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// show back projection 
	cvNamedWindow("Back Projection", CV_WINDOW_AUTOSIZE);
	cvShowImage("Back Projection", back_img);
	// show histogram equalized 
	cvNamedWindow("HS Histogram", CV_WINDOW_AUTOSIZE);
	cvShowImage("HS Histogram", hist_img);
	// wait for a pressed key
	cvWaitKey(0);
	// close window
	cvDestroyAllWindows();
}