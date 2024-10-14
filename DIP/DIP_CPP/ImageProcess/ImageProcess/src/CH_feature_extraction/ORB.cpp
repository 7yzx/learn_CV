#include "ORB.h"
#include "pch.h"

int Fast_detect(string img_path, int threshold)
{
	Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
	if (img.empty())
	{
		cout << " no img,recheck the path" << endl;
		return -1;
	}

	cv::Ptr<cv::FastFeatureDetector> fast = cv::FastFeatureDetector::create(threshold, true);

	vector<cv::KeyPoint> keypoints;

	fast->detect(img, keypoints);

	cv::Mat img_keypoints;

	cv::drawKeypoints(img, keypoints, img_keypoints);

	cv::imshow("keypoints", img_keypoints);
	cv::waitKey(0);

	return 0;
}


int ORB_detect(string img_path1, string img_path2)
{
	Mat img1 = imread(img_path1, IMREAD_COLOR);
	Mat img2 = imread(img_path2, IMREAD_COLOR);

	if (img1.empty() || img2.empty())
	{
		cout << " no img,recheck the path" << endl;
		return -1;
	}
	// 1. 定义关键点和描述子
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptors1, descriptors2;
	Ptr<FeatureDetector> ORB_detector = ORB::create();
	Ptr<DescriptorExtractor> ORB_discriptor = ORB::create();
	Ptr<DescriptorMatcher> ORB_matcher = DescriptorMatcher::create("BruteForce-Hamming");

	// 2. 检测ORB角点位置
	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

	ORB_detector->detect(img1, keypoints1);
	ORB_detector->detect(img2, keypoints2);
	// 3. 计算描述子
	ORB_discriptor->compute(img1, keypoints1, descriptors1);
	ORB_discriptor->compute(img2, keypoints2, descriptors2);

	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

	chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

	cout << "extract ORB cost = " << time_used.count() << " seconds. " << endl;

	Mat outimg1;
	drawKeypoints(img1, keypoints1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);


	imshow("ORB features", outimg1);


	vector<DMatch> matches;

	t1 = chrono::steady_clock::now();

	ORB_matcher->match(descriptors1, descriptors2, matches);

	t2 = chrono::steady_clock::now();

	time_used = chrono::duration_cast<chrono::duration<double>>(t2- t1);

	cout<< "match ORB cost = " << time_used.count() << " seconds. " << endl;

	auto min_max = minmax_element(matches.begin(),matches.end(), [](const DMatch &m1, const DMatch &m2) {return m1.distance < m2.distance; });


	double min_dist = min_max.first->distance;
	double max_dist = min_max.second->distance;


	cout << "min dist = " << min_dist << endl;
	cout << "max dist = " << max_dist << endl;

	vector<DMatch> good_matches;

	for (int i = 0; i < descriptors1.rows; i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 30.0))
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_match;
	Mat good_img_match;

	drawMatches(img1, keypoints1, img2, keypoints2, matches, img_match);
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, good_img_match);
	imshow("all matches", img_match);
	imshow("good matches", good_img_match);


	waitKey(0);
	// 
	return 0;
}
