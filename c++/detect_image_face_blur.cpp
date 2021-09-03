#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
using namespace std;
using namespace cv;
int main()
{
	// initial setup
	Mat roi;
	int MAX_KERNEL_LENGTH = 10;
	// load image
	Mat src = imread("3.png");
	imshow("Original", src);
	// load clssifier
	CascadeClassifier c;
	c.load("haarcascade_frontalface_alt2.xml");
	// detect faces
	vector<Rect> faces;
	c.detectMultiScale(src, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(1, 30));
	// blur faces	
	for (vector<Rect>::const_iterator r = faces.begin(); r < faces.end(); r++)
	{
		// init parameters
		int x = r->x, y = r->y, width = r->width, height = r->height;
		// make ROI
		Rect roi_rect(x, y, width, height);
		roi = src(roi_rect);
		// blur ROI
		for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
		{
			GaussianBlur(roi, roi, Size(i, i), 0, 0);
		}
	}
	// show result
	imshow("Face Detection", src);
	cvWaitKey(0);
	destroyAllWindows;
	return 0;
}