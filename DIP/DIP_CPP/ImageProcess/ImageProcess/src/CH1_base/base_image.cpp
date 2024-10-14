#include "pch.h"
#include "base_image.h"


int img_read_test()
{
	string imgs_dir = "E:\\ALL_CODE\\My_study\\learn_CV\\DIP\\images";
	string img_path = "E:\\ALL_CODE\\My_study\\learn_CV\\DIP\\images\\lena.png";

	Mat img = imread(img_path, IMREAD_COLOR);

	if (img.empty())
	{
		cout << " no img,recheck the path" << endl;
		return -1;
	}

	imshow("Display window", img);

	int k = waitKey();

	if (k == 's')
	{
		string save_path = imgs_dir + "\\save.png";

		imwrite(save_path, img);

		cout << "save img to" << save_path << endl;
		return 0;
	}

	if (k == 'q')
	{
		return -1;
	}


}

//int Mouse_show(string path)
//{
//
//
//}