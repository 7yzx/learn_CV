#include "base_image.h"
#include "ch2_transform.h"
#include "pch.h"
#include "ORB.h"

int main()
{
	string img_path = "E:\\ALL_CODE\\My_study\\learn_CV\\DIP\\images\\lena.png";
	//img_read_test();
	//chang_gray(img_path);
	//Fast_detect(img_path, 40);

	string img_path1 = "E:\\ALL_CODE\\My_study\\learn_CV\\DIP\\images\\1.png";
	string img_path2 = "E:\\ALL_CODE\\My_study\\learn_CV\\DIP\\images\\2.png";
	ORB_detect(img_path1, img_path2);

	return 0;
}