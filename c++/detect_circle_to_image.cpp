#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

void main()
{
	// load ảnh
	Mat src = imread("7.png");
	// Tao image moi co cung kich thuoc voi image goc
	Mat dst_new = cvCreateMat(src.rows, src.cols, CV_8UC3);
	for (int i = 0; i < dst_new.cols * 3; i++)
	{
		for (int j = 0; j < dst_new.rows; j++)
		{
			dst_new.at<uchar>(Point(i, j)) = 255;
		}
			
	}		
	// copy ảnh src sang dst
	Mat dst = src.clone();
	// chuyển ảnh xám
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	// chuyển ảnh bw
	Mat bw;
	// lọc canny để làm nổi các cạnh
	Canny(gray, bw, 0, 50, 5);
	// gọi biến chứa đường bao
	vector<vector<Point> > contours;
	// tìm các đường bao có trong hình
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	vector<Point> approx;
	// chạy vòng lặp từ đường bao đầu tiên đến đường bao cuối cùng tìm được
	for (int i = 0; i < contours.size(); i++)
	{
		// xác định các tham số hình học của đường bao
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
		// nếu đường bao có nhiều hơn 6 cạnh --> hình tròn
		if (approx.size() > 6)
		{
			//
			double area = contourArea(contours[i]);
			Rect r = boundingRect(contours[i]);
			int radius = r.width / 2;
			Point center = Point(r.x + radius, r.y + radius);
			if (abs(1 - ((double)r.width / r.height)) <= 0.2 &&
				abs(1 - (area / (CV_PI * pow(radius, 2)))) <= 0.2)
			{
				circle(dst, center, radius, Scalar(255, 255, 255), 5);
			}
			//
			Point loc_text = Point(r.x + radius*0.4, r.y + radius*0.6);
			putText(dst, "Circle", loc_text, CV_FONT_NORMAL, 0.8, CV_RGB(255, 255, 255), 1);
			//
			ostringstream ostr;
			ostr << area;
			Point loc_area = Point(r.x + radius*0.4, r.y + radius*1.2);
			putText(dst, ostr.str(), loc_area, CV_FONT_NORMAL, 0.8, CV_RGB(255, 255, 255), 1);
			//
			Rect roi_circle = Rect(center.x - radius, center.y - radius, radius*2.1, radius*2.1);
			Mat roi_img = src(roi_circle);
			roi_img.copyTo(dst_new(roi_circle));
			imshow("Circle Image", dst_new);
		}
	}
	imshow("Image", src);
	imshow("Detect Circle", dst);
	waitKey(0);
	cvDestroyAllWindows();
}