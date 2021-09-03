#include"opencv/cv.h"
#include"opencv/highgui.h"
void main()
{
	// load video
	CvCapture* video = cvCaptureFromFile("1.mp4");
	// gọi biến ảnh dùng để chứa từng frame (khung hình) video
	IplImage* frame;
	while (1)
	{
		// đọc frame video (từ frame 1 đến frame cuối cùng)
		frame = cvQueryFrame(video);
		// hết video --> ko còn frame --> thoát chương trình
		if (!frame) break;
		// show video
		cvShowImage("Original Video", frame);
		// crop video
		cvSetImageROI(frame, cvRect(100, 50, 300, 200));
		cvShowImage("Crop Video", frame);
		// chỉnh tốc độ video
		// 30fps = 30 frame / 1 second --> 1 frame 1/30s = 33ms
		char c = cvWaitKey(33);
		// nhấn ESC thì video ngừng, thoát chương trình
		if (c == 27) break;
	}
	// giải phóng bộ nhớ và thoát chương trình
	cvReleaseCapture(&video);
	cvDestroyAllWindows();
}