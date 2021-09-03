#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "imgproc/imgproc_c.h"
#include "opencv2/objdetect/objdetect.hpp"

#define HAAR_LINK "haarcascade_frontalface_alt_tree.xml"

using namespace std;
using namespace cv;
void readme();

/** Function Headers */
void detectAndDisplay(IplImage* frame, IplImage* frame_org);

/** Global variables */
CvHaarClassifierCascade* face_cascade = 0;
CvMemStorage* pStorageface = 0;

RNG rng(12345);

/**
* @function main
*/

/** @function main */
int main()
{

	Mat img_object = imread("surf_object.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_scene = imread("surf_scene.jpg", CV_LOAD_IMAGE_COLOR);

	Mat img_face_cluster;
	img_scene.copyTo(img_face_cluster);
	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;

	SurfFeatureDetector detector(minHessian);

	std::vector<KeyPoint> keypoints_object, keypoints_scene;

	detector.detect(img_object, keypoints_object);
	detector.detect(img_scene, keypoints_scene);

	//-- Step 2: Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;

	Mat descriptors_object, descriptors_scene;

	extractor.compute(img_object, keypoints_object, descriptors_object);
	extractor.compute(img_scene, keypoints_scene, descriptors_scene);

	//-- Step 3: Matching descriptor vectors using FLANN matcher
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches;
	matcher.match(descriptors_object, descriptors_scene, matches);

	double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints
	for (int i = 0; i < descriptors_object.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}

	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	//-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
	std::vector< DMatch > good_matches;

	for (int i = 0; i < descriptors_object.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_matches;
	drawMatches(img_object, keypoints_object, img_scene, keypoints_scene,
		good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	//-- Localize the object
	std::vector<Point2f> obj;
	std::vector<Point2f> scene;

	for (int i = 0; i < good_matches.size(); i++)
	{
		//-- Get the keypoints from the good matches
		obj.push_back(keypoints_object[good_matches[i].queryIdx].pt);
		scene.push_back(keypoints_scene[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(obj, scene, CV_RANSAC);

	//-- Get the corners from the image_1 ( the object to be "detected" )
	std::vector<Point2f> obj_corners(4);
	obj_corners[0] = cvPoint(0, 0); obj_corners[1] = cvPoint(img_object.cols, 0);
	obj_corners[2] = cvPoint(img_object.cols, img_object.rows); obj_corners[3] = cvPoint(0, img_object.rows);
	std::vector<Point2f> scene_corners(4);

	perspectiveTransform(obj_corners, scene_corners, H);

	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
	Point facemark_org = scene_corners[0] + Point2f(img_object.cols, 0);
	Point facemark_fin = scene_corners[2] + Point2f(img_object.cols, 0);

	rectangle(img_face_cluster, scene_corners[0], scene_corners[2], cvScalar(0, 255, 255));
	rectangle(img_matches,
		scene_corners[0] + Point2f(img_object.cols, 0),
		scene_corners[2] + Point2f(img_object.cols, 0),
		cvScalar(0, 255, 255));

	//-- Show detected matches
	imshow("Good Matches & Object detection", img_matches);
	imshow("Face Matched", img_face_cluster);
	imshow("Object", img_object);

	waitKey(0);
	return 0;
}

void detectAndDisplay(IplImage* frame, IplImage* frame_org)
{

	CvSeq * pFaceRectSeq;               // memory-access interface
	pStorageface = cvCreateMemStorage(0);

	// detect faces in image
	pFaceRectSeq = cvHaarDetectObjects
		(frame, face_cascade, pStorageface,
		1.1,                       // increase search scale by 10% each pass
		3,                         // merge groups of three detections
		CV_HAAR_DO_CANNY_PRUNING,  // skip regions unlikely to contain a face
		cvSize(40, 40));            // smallest size face to detect = 40x40

	const char * DISPLAY_WINDOW = "Haar Window";
	int i;

	// create a window to display detected faces
	cvNamedWindow(DISPLAY_WINDOW, CV_WINDOW_AUTOSIZE);

	// draw a rectangular outline around each detection
	for (i = 0; i<(pFaceRectSeq ? pFaceRectSeq->total : 0); i++)
	{
		CvRect* r = (CvRect*)cvGetSeqElem(pFaceRectSeq, i);
		CvPoint pt1 = { (int)((double)(r->x) * 2), (int)((double)r->y * 2) };
		CvPoint pt2 = { (int)((double)(r->x + r->width) * 2), (int)((double)(r->y + r->height) * 2) };
		cvRectangle(frame_org, pt1, pt2, CV_RGB(255, 255, 255), 2, 4, 0);
	}

	// display face detections
	cvShowImage(DISPLAY_WINDOW, frame_org);
}