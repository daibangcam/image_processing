#define _CRT_SECURE_NO_DEPRECATE
#include "stdio.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
// gọi biến chứa bộ nhận dạng và bộ nhớ cho dữ liệu nhận dạng
CvHaarClassifierCascade* cascade;
CvMemStorage* storage;
// khai báo hàm con nhận diện khuôn mặt
void detectFaces(IplImage *img);
// chương trình chính
void main()
{
	// gọi biến chứa video/webcam và biến chứa frame ảnh
	CvCapture *capture;
	IplImage *frame;
	// đọc video
	capture = cvCaptureFromFile("1.mp4");
	// mở webcam
	//capture = cvCaptureFromCAM(0);
	// khai báo bộ nhận dạng haarcascade
	char *filename = "haarcascade_frontalface_alt2.xml";
	cascade = (CvHaarClassifierCascade*)cvLoad(filename, 0, 0, 0);
	// khởi tạo bộ nhớ cho bộ nhận dạng
	storage = cvCreateMemStorage(0);
	// đọc video/chạy webcam xử lý
	while (1)
	{
		// đọc từng frame hình từ camera
		do
		{
			frame = cvQueryFrame(capture);
		} 
		while (!frame);	
		//// đọc từng frame hình video
		//frame = cvQueryFrame(capture);
		if (!frame) break;
		// gọi hàm nhận diện khuôn mặt
		detectFaces(frame);
		// show kết quả
		cvShowImage("Video", frame);
		// nhấn ESC thì thoát chương trình
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
}
void detectFaces(IplImage *img)
{	
	// gọi biến faces chứa các khuôn mặt nhận diện được
	CvSeq* faces = cvHaarDetectObjects(img, cascade, storage, 1.1, 3, 0, cvSize(40, 40));
	// gọi biến đếm i để chạy trong vòng lặp
	int i;
	for (i = 0; i < (faces ? faces->total : 0); i++)
	{
		// gọi biến r chứa thông tin các khuôn mặt tìm được 
		// r là hình chữ nhật bao quanh khuôn mặt
		CvRect* r = (CvRect*)cvGetSeqElem(faces, i);		
		// làm mờ khuôn mặt nhận diện được
		cvSetImageROI(img, cvRect(r->x, r->y, r->width, r->height));
		cvShowImage("crop", img);
		for (int i = 0; i < 20; i++)
		{
			cvSmooth(img, img, CV_BLUR, 5, 5);
		}		
		cvResetImageROI(img);
		// vẽ hình vuông bao quanh khuôn mặt		
		cvRectangle(img, cvPoint(r->x, r->y), cvPoint(r->x + r->width, r->y + r->height), CV_RGB(255, 0, 0), 5, 8, 0);
		// vẽ hình tròn bao quanh khuôn mặt
		CvPoint center;
		center.x = r->x + r->width / 2;
		center.y = r->y + r->height / 2;
		int radius = r->height *0.7;
		cvCircle(img, center, radius, CV_RGB(0, 255, 0), 5, 8, 0);
	}
}