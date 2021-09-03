#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/// Global variables
char* source_window = "Source image";
char* warp_window = "Warp";
char* per_window = "Perspective";
char* rotate_window = "Rotate";
char* warp_rotate_window = "Warp + Rotate";
/** @function main */
int main(int argc, char** argv)
{
	Point2f srcTri[3];
	Point2f dstTri[3];
	Point2f srcPer[4];
	Point2f dstPer[4];
	Mat rot_mat(2, 3, CV_32FC1);
	Mat warp_rot_mat(2, 3, CV_32FC1);
	Mat warp_mat(2, 3, CV_32FC1);
	Mat per_mat(3, 3, CV_32FC1);
	Mat src, warp_dst, warp_rotate_dst, rotate_dst, per_dst;
	/// Load the image
	src = imread("1.jpg", 1);
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);
	dstTri[0] = Point2f(src.cols*0.0, src.rows*0.33);
	dstTri[1] = Point2f(src.cols*0.85, src.rows*0.25);
	dstTri[2] = Point2f(src.cols*0.15, src.rows*0.7);
	srcPer[0] = Point2f(0, 0);
	srcPer[1] = Point2f(src.cols - 1, 0);
	srcPer[2] = Point2f(0, src.rows - 1);
	srcPer[3] = Point2f(src.cols - 1, src.rows - 1);
	dstPer[0] = Point2f(src.cols*0.05, src.rows*0.33);
	dstPer[1] = Point2f(src.cols*0.9, src.rows*0.25);
	dstPer[2] = Point2f(src.cols*0.2, src.rows*0.7);
	dstPer[3] = Point2f(src.cols*0.8, src.rows*0.9);
	/// Get the Affine & Perspective Transform
	warp_mat = getAffineTransform(srcTri, dstTri);
	per_mat = getPerspectiveTransform(srcPer, dstPer);
	/// Apply the Affine Transform just found to the src image
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
	warpPerspective(src, per_dst, per_mat, per_dst.size());
	/** Rotating the image after Warp */
	/// Compute a rotation matrix with respect to the center of the image
	Point center_warp = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	Point center = Point(src.cols / 2, src.rows / 2);
	double angle = -50.0;
	double scale = 0.8;
	/// Get the rotation matrix with the specifications above
	rot_mat = getRotationMatrix2D(center, angle, scale);
	warp_rot_mat = getRotationMatrix2D(center_warp, angle, scale);
	/// Rotate
	warpAffine(src, rotate_dst, rot_mat, warp_dst.size());
	warpAffine(warp_dst, warp_rotate_dst, warp_rot_mat, warp_dst.size());
	/// Show what you got
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);
	namedWindow(warp_window, CV_WINDOW_AUTOSIZE);
	imshow(warp_window, warp_dst);
	namedWindow(per_window, CV_WINDOW_AUTOSIZE);
	imshow(per_window, per_dst);
	namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);
	imshow(rotate_window, rotate_dst);
	namedWindow(warp_rotate_window, CV_WINDOW_AUTOSIZE);
	imshow(warp_rotate_window, warp_rotate_dst);
	/// Wait until user exits the program
	waitKey(0);
	return 0;
}