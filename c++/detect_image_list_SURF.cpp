#include <stdio.h>
#include <iostream>
#include <string.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#define sources  "C:/Users/Administrator/Desktop/Project/TGMT/Visual Studio/Sources/"

using namespace cv;
using namespace std;
void readme();

/** @function main */
int main(int argc, char** argv)
{	
	int loop = 1;
	/*
	string path[10] = { sources"01.jpg", sources"02.jpg", sources"03.jpg", sources"04.jpg", 
						sources"05.jpg", sources"06.jpg", sources"07.jpg"};
	string path_new[10] = { sources"match_01.jpg", sources"match_02.jpg", sources"match_03.jpg", sources"match_04.jpg",
						  sources"match_05.jpg", sources"match_06.jpg", sources"match_07.jpg" };
	*/
	///*
	string path[10] = { "img/1.jpg", "img/2.jpg", "img/3.jpg", "img/4.jpg", "img/5.jpg",
		"img/6.jpg", "img/7.jpg", "img/8.jpg", "img/9.jpg", "img/10.jpg" };
	
	string path_new[10] = { "imgnew/1.jpg", "imgnew/2.jpg", "imgnew/3.jpg", "imgnew/4.jpg", "imgnew/5.jpg",
		"imgnew/6.jpg", "imgnew/7.jpg", "imgnew/8.jpg", "imgnew/9.jpg", "imgnew/10.jpg" };
	//*/
	for (loop = 1; loop <= 10; loop++)
	{
		Mat img_object = imread(sources"08.jpg", CV_LOAD_IMAGE_COLOR);
		Mat img_scene = imread(path[loop - 1], CV_LOAD_IMAGE_COLOR);

		if (!img_object.data || !img_scene.data)
		{
			std::cout << " --(!) Error reading images " << std::endl; return -1;
		}

		//-- Step 1: Detect the keypoints using SURF Detector
		int minHessian = 350;

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

		//printf("-- Max dist : %f \n", max_dist);
		//printf("-- Min dist : %f \n", min_dist);

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
		line(img_matches, scene_corners[0] + Point2f(img_object.cols, 0), scene_corners[1] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
		line(img_matches, scene_corners[1] + Point2f(img_object.cols, 0), scene_corners[2] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
		line(img_matches, scene_corners[2] + Point2f(img_object.cols, 0), scene_corners[3] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);
		line(img_matches, scene_corners[3] + Point2f(img_object.cols, 0), scene_corners[0] + Point2f(img_object.cols, 0), Scalar(0, 255, 0), 4);

		CvMoments area;
		printf("-- Area %d: %f \n", loop, area = moments(scene_corners, 1));

		if (area.m00 > 500)	// Accept match image
		{
			//-- Show detected matches
			imshow(path[loop - 1], img_matches);

			// Copy img and write down new
			//imwrite(path_new[loop - 1], img_scene);
		}
	}
	cvWaitKey();
	destroyAllWindows;
	return 0;
}

/** @function readme */
void readme()
{
	std::cout << " Usage: ./SURF_descriptor <img1> <img2>" << std::endl;
}