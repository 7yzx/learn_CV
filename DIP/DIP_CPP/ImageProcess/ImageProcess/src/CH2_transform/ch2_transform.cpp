#include "pch.h"
#include "ch2_transform.h"

int chang_gray(string img_path)
{
	Mat img1, img_gray, output_img;
	img1 = imread(img_path);
	if (img1.empty())
	{
		cout << "error " << endl;
		return -1;
	}

	cvtColor(img1,img_gray, COLOR_BGR2GRAY);

	imshow("gray_image", img_gray);

	output_img = img_gray.clone();

	for (int i=0; i < img_gray.rows; i++)
	{
		for (int j=0; j < img_gray.cols; j++)
		{
			output_img.at<uchar>(i, j) = 255 - img_gray.at<uchar>(i, j);
		}
	}
	imshow("output", output_img);

	waitKey(0);

	return 0;

}