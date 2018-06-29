// LinearBlending.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	double alpha = 0.5;
	double beta;
	double input;
	Mat src1, src2, dst;
	cout << "Simple Linear Blender" << endl;
	cout << "----------------------" << endl;
	cout << "* Enter alpha [0-1]:";
	cin >> input;
	if (input >= 0.0 && input <= 1.0)
	{
		{ alpha = input; }
	}
	src1 = imread("LinuxLogo.jpg");
	src2 = imread("WindowsLogo.jpg");
	if (!src1.data){ printf("Error loading src1\n"); return -1; }
	if (!src1.data){ printf("Error loading src2\n"); return -1; }
	namedWindow("Linear Blend", 1);
	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	imshow("Linear Blend", dst);
	waitKey(0);
	return 0;
}

