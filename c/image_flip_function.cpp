#include "opencv/cv.h"
#include "opencv/highgui.h"
void flip(IplImage* src, IplImage* des, int mode);
void main()
{
	// load image
	IplImage* img = cvLoadImage("1.jpg");
	// show image
	cvNamedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
	cvShowImage("RGB Image", img);
	// flip image vertically
	IplImage* img_flip_v = cvCreateImage(cvGetSize(img), 8, 3);
	flip(img, img_flip_v, 1);
	cvShowImage("Flip Image Vertically", img_flip_v);
	// flip image horizontally
	IplImage* img_flip_h = cvCreateImage(cvGetSize(img), 8, 3);
	flip(img, img_flip_h, 0);
	cvShowImage("Flip Image Horizontally", img_flip_h);
	// flip image both horizontally & vertically
	IplImage* img_flip_hv = cvCreateImage(cvGetSize(img), 8, 3);
	flip(img, img_flip_hv, -1);
	cvShowImage("Flip Image Horizontally & Vertically", img_flip_hv);
	// wait for a pressed key
	cvWaitKey(0);
	// release memory
	cvReleaseImage(&img);
	cvReleaseImage(&img_flip_v);
	cvReleaseImage(&img_flip_h);
	cvReleaseImage(&img_flip_hv);
	// close window
	cvDestroyAllWindows();
}
void flip(IplImage* src, IplImage* des, int mode)
{
	int height = src->height;
	int width = src->width;
	int channels = src->nChannels;
	int step = src->widthStep / sizeof(uchar);
	if (mode == 0)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < channels; k++)
				{
					des->imageData[i*step + j*channels + k] = src->imageData[(height - i - 1)*step + j*channels + k];
				}
			}
		}
	}
	else if (mode > 0)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < channels; k++)
				{
					des->imageData[i*step + j*channels + k] = src->imageData[i*step + (width - j - 1)*channels + k];
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int k = 0; k < channels; k++)
				{
					des->imageData[i*step + j*channels + k] = src->imageData[(height - i - 1)*step + (width - j - 1)*channels + k];
				}
			}
		}
	}
}