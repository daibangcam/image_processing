#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("7.png");
	imshow("Image", src);
	Mat HSV;
	Mat threshold;
	cvtColor(src, HSV, CV_BGR2HSV);
	imshow("HSV", HSV);
	inRange(HSV, Scalar(106, 60, 90), Scalar(124, 255, 255), threshold);
	imshow("Threshold", threshold);
	/////////////////////////////////////////////////////////////
	// Close
	waitKey(0);
	return 0; // yea, c++, no cleanup nessecary!
}