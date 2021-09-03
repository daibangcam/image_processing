#include"opencv/cv.h"
#include"opencv/highgui.h"
void main()
{
	// load video
	CvCapture* video = cvCaptureFromFile("1.mp4");
	// gọi biến ảnh dùng để chứa từng frame (khung hình) video
	IplImage* frame;
	double fps = cvGetCaptureProperty(video, CV_CAP_PROP_FPS);
	CvSize size_1 = cvSize(854, 480);
	CvSize size_2 = cvSize((int)cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_WIDTH) / 2, (int)cvGetCaptureProperty(video, CV_CAP_PROP_FRAME_HEIGHT) / 2);
	// tạo bộ ghi video
	CvVideoWriter* writer_1 = cvCreateVideoWriter("output1.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, size_1, 0);
	//
	frame = cvQueryFrame(video);
	CvVideoWriter* writer_2 = cvCreateVideoWriter("output2.avi", CV_FOURCC('P', 'I', 'M', '1'), fps, size_2, 1);
	// để đọc liên tiếp các frame video
	while (1)
	{
		// đọc frame video (từ frame 1 đến frame cuối cùng)
		frame = cvQueryFrame(video);
		// hết video --> ko còn frame --> thoát chương trình
		if (!frame) break;
		// show video
		cvShowImage("Original Video", frame);
		// chuyển qua video xám
		IplImage* frame_gray = cvCreateImage(cvGetSize(frame), 8, 1);
		cvCvtColor(frame, frame_gray, CV_BGR2GRAY);
		cvShowImage("Gray Video", frame_gray);
		// resize video
		IplImage* frame_resize = cvCreateImage(cvSize(frame->width / 2, frame->height / 2), 8, 3);
		cvResize(frame, frame_resize);
		cvShowImage("Resolution Video", frame_resize);	
		// save frame 
		cvWriteFrame(writer_1, frame_gray);
		cvWriteFrame(writer_2, frame_resize);
		// chỉnh tốc độ video
		// 30fps = 30 frame / 1 second --> 1 frame 1/30s = 33ms
		char c = cvWaitKey(33);
		// nhấn ESC thì video ngừng, thoát chương trình
		if (c == 27) break;
	}
	// giải phóng bộ nhớ và thoát chương trình
	cvReleaseCapture(&video);
	cvReleaseVideoWriter(&writer_1);
	cvReleaseVideoWriter(&writer_2);
	cvDestroyAllWindows();
}