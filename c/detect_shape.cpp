#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
void main()
{
	// load ảnh input
	IplImage* img = cvLoadImage("5.png");
	// show ảnh input
	cvShowImage("Original Image", img); 
	// chuyển sang ảnh xám
	IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1);
	cvCvtColor(img, imgGrayScale, CV_BGR2GRAY);
	// chuyển sang ảnh nhị phân
	cvThreshold(imgGrayScale, imgGrayScale, 128, 255, CV_THRESH_BINARY);
	// gọi biến pointer đến khung bao
	CvSeq* contours;
	// gọi biến chứa kết quả
	CvSeq* result;
	// gọi biến vùng nhớ lưu trữ kết quả
	CvMemStorage *storage = cvCreateMemStorage(0);
	// chọn font chữ để ghi lên ảnh
	CvFont font;
	cvInitFont(&font, CV_FONT_ITALIC, 1, 0.5);
	string str;
	const char *text;
	// tìm các khung bao có trong ảnh
	cvFindContours(imgGrayScale, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
	// khi trong ảnh có khung bao thì xử  lý
	while (contours)
	{
		// lưu chuỗi thông tin của các khung bao vào biến result
		result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);
		// nếu khung bao có 3 đỉnh --> hình tam giác
		if (result->total == 3)
		{
			// xác định từng đỉnh trong 3 đỉnh của khung bao
			CvPoint *pt[3];
			CvRect rect = cvBoundingRect(contours, 0);
			for (int i = 0; i<3; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			// vẽ đường thẳng nối lần lượt 2 đỉnh lại với nhau
			cvLine(img, *pt[0], *pt[1], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(0, 0, 255), 4);
			cvLine(img, *pt[2], *pt[0], cvScalar(0, 0, 255), 4);
			// ghi chú chữ "tam giác" vào hình
			str = "Tam giac";
			text = str.c_str();
			cvPutText(img, text, cvPoint(rect.x + 5, rect.y + rect.height + 30), &font, CV_RGB(255, 0, 0));
		}
		// nếu khung bao có 4 đỉnh --> hình tứ giác
		else if (result->total == 4)
		{
			//  xác định từng đỉnh trong 4 đỉnh của khung bao
			CvPoint *pt[4];
			CvRect rect = cvBoundingRect(contours, 0);
			for (int i = 0; i<4; i++)
			{
				pt[i] = (CvPoint*)cvGetSeqElem(result, i);
			}
			// vẽ đường thẳng nối lần lượt 2 đỉnh lại với nhau
			cvLine(img, *pt[0], *pt[1], cvScalar(255, 0, 0), 4);
			cvLine(img, *pt[1], *pt[2], cvScalar(255, 0, 0), 4);
			cvLine(img, *pt[2], *pt[3], cvScalar(255, 0, 0), 4);
			cvLine(img, *pt[3], *pt[0], cvScalar(255, 0, 0), 4);
			// ghi chú chữ "tứ giác" vào hình
			str = "Tu giac";
			text = str.c_str();
			cvPutText(img, text, cvPoint(rect.x + 5, rect.y + rect.height + 30), &font, CV_RGB(255, 255, 255));
		}
		// chuyển qua khung bao tiếp theo
		contours = contours->h_next;
	}
	// show ảnh đã nhận dạng tam giác, tứ giác
	cvShowImage("Tracked Image", img);
	cvWaitKey(0); //wait for a key press
	//cleaning up
	cvDestroyAllWindows();
}