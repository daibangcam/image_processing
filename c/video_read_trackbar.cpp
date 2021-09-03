#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

int g_slider_position = 0;
CvCapture* g_capture = NULL;
void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}
int main(int argc, char** argv) 
{
	cvNamedWindow("Video", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture("1.mp4");
	int frames = (int)cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT);
	if (frames != 0)
	{
		cvCreateTrackbar("Position", "Video", &g_slider_position, frames, onTrackbarSlide);
		//g_slider_position =cvGetTrackbarPos("Position", "Video");
	}
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(g_capture);
		if (!frame) break;
		cvShowImage("Video", frame);
		cvSetTrackbarPos("Position", "Video", g_slider_position);
		g_slider_position++;
		char c = cvWaitKey(1);
		if (c == 27) break;
	}
}