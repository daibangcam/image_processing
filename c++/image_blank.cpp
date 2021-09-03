#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

int main()
{
	Mat src = imread("1.jpg");
	imshow("s", src);
	/* ROI by creating mask for the parallelogram */
	Mat dst = cvCreateMat(src.rows, src.cols, CV_8UC1);
	// Create black image with the same size as the original
	for (int i = 0; i<dst.cols; i++)
		for (int j = 0; j<dst.rows; j++)
			dst.at<uchar>(Point(i, j)) = 255;

	imshow("a", dst);
	waitKey(0);
	return 0; // yea, c++, no cleanup nessecary!
}