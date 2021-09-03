#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void main()
{
	// load ảnh
	Mat src = imread("3.png");
	imshow("Original", src);
	// tạo biến chứa bộ nhận diện khuôn mặt
	CascadeClassifier c;
	// gọi bộ nhận dạng có sẵn haarcascade vào biến c
	c.load("haarcascade_frontalface_alt2.xml");
	// tạo 1 vector chứa các khuôn mặt nhận diện được
	vector<Rect> faces;
	// chạy bộ phân loại để nhận diện khuôn mặt có trong ảnh
	c.detectMultiScale(src, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(1, 30));
	for (vector<Rect>::const_iterator r = faces.begin(); r < faces.end(); r++)
	{
		// gọi biến chứa tâm khuôn mặt
		Point center;
		center.x = r->x + (int)r->width / 2;
		center.y = r->y + (int)r->height / 2;
		circle(src, center, 50, CV_RGB(255, 0, 0), 2, 8, 0);
	}
	// show ảnh kết quả
	imshow("Result", src);
	// chờ nhấn phím bất kì thì thoát
	cvWaitKey(0);
}