// MatLearn.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
using namespace cv;
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	int sz[3] = { 2, 2, 2 };
	//Mat L(3, sz, CV_8UC(1), Scalar::all(0));
	Mat L(2, 2, CV_8UC3, Scalar(0, 0, 255));
	cout << "L=" << " " << " " << L << endl << endl;
	return 0;
}

