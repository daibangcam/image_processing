#include "highgui.h"
#include "cv.h"


void my_mouse_callback(
	int event, int x, int y, int flags, void* param
	);
CvRect box;
bool drawing_box = false;
// A litte subroutine to draw a box onto một image
//
void draw_box(IplImage* img, CvRect rect)
{
	cvRectangle(img,								//ve hinh chu nhat
		cvPoint(box.x, box.y),
		cvPoint(box.x + box.width, box.y + box.height),
		cvScalar(0xff, 0x00, 0x00) /* blue*/
		);
}

int main()
{
	box = cvRect(-1, -1, 0, 0);		//tao box hinh chu nhat
	IplImage* image = cvCreateImage(
		cvSize(500, 500), //tao image 3 channel 8 bit 
		IPL_DEPTH_8U,
		3
		);
	cvZero(image);
	IplImage* temp = cvCloneImage(image);
	cvNamedWindow("Box Example");
	// Here is the crucial moment that ta thực sự install
	// callback. Lưu ý rằng ta set the value ‘param’ to
	// be the image ta are working with sao cho callback
	// sẽ have the image to edit.
	//
	cvSetMouseCallback(
		"Box Example",
		my_mouse_callback,
		(void*)image
		);
	// The main program loop. Here ta copy the working image
	// to the ‘temp’ image, và if the user is drawing, then
	// put the currently contemplated box onto that temp image.
	// display the temp image, và wait 15ms for a keystroke,
	// then repeat…
	//

	while (1)
	{
		cvCopyImage(image, temp);
		if (drawing_box) draw_box(temp, box);
		cvShowImage("Box Example", temp);
		if (cvWaitKey(15) == 27)
			break;
	}
	// Be tidy
	//
	cvReleaseImage(&image);
	cvReleaseImage(&temp);
	cvDestroyWindow("Box Example");
}

void my_mouse_callback(int event, int x, int y, int flags, void* param)
{
	IplImage* image = (IplImage*)param;
	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
	{
		if (drawing_box)
		{
			box.width = x - box.x;
			box.height = y - box.y;
		}
	}
	break;
	case CV_EVENT_LBUTTONDOWN:
	{
		drawing_box = true;
		box = cvRect(x, y, 0, 0);
	}
	break;
	case CV_EVENT_LBUTTONUP:
	{
		drawing_box = false;
		if (box.width<0)
		{
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height<0)
		{
			box.y += box.height;
			box.height *= -1;
		}
		draw_box(image, box);
	}
	break;

	}
}