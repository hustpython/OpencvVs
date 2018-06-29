// ChangeContrastAndBrightness.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	double alpha;
	int beta;
	Mat image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat new_image = Mat::zeros(image.size(), image.type());
	cout << "Basic Linear Transforms" << endl;
	cout << "-----------------------" << endl;
	cout << "*Enter the alpha value [1.0 - 3.0]:";
	cin >> alpha;
	cout << "*Enter the beta value [0 - 100]";
	cin >> beta;
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);
	imshow("Original Image", image);
	imshow("New Image",new_image);
	waitKey(0);
	return 0;
}

