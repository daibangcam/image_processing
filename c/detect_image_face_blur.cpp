#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
	IplImage* src = cvLoadImage("3.png");
	cvShowImage("Original", src);
	CascadeClassifier c;
	c.load("haarcascade_frontalface_alt2.xml");
	vector<Rect> faces;
	c.detectMultiScale(src, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(1, 30));
	for (vector<Rect>::const_iterator r = faces.begin(); r < faces.end(); r++)
	{
		cvSetImageROI(src, cvRect(r->x, r->y, r->width, r->height));
		for (int i = 1; i < 10; i++)
		{
			cvSmooth(src, src, CV_BLUR, 5, 3);
		}
		cvResetImageROI(src);
	}
	cvShowImage("Face Detection", src);
	cvWaitKey(0);
	return 0;
}