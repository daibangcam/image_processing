#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

void main()
{
	// load ảnh
	Mat src = imread("6.png");
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
				//
				ostringstream ostr;
				ostr << area;
				Point location_area = Point(r.x + radius*0.6, r.y + radius*0.8);
				Point location_text = Point(r.x + radius*0.6, r.y + radius*1.5);
				putText(dst, "Circle", location_text, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 2, 8);
				putText(dst, ostr.str(), location_area, FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 2, 8);
			}
			
		}
	}
	imshow("Image", src);
	//imshow("Gray", gray);
	//imshow("BW", bw);
	imshow("Detect Circle", dst);
	waitKey(0);
	cvDestroyAllWindows();
}