#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat img = imread("1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	if (img.empty())
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
		system("pause");
		return -1;
	}
	imshow("Image", img);
	//wait infinite time for a keypress
	waitKey(0);			
	//destroy all window
	destroyAllWindows();
	return 0;
}