// MatScanning.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
using namespace cv;
Mat &ScanImageAndReduceIterator(Mat &I, const uchar * const table)
{
	CV_Assert(I.depth() != sizeof(uchar));
	const int chanels = I.channels();
	switch (chanels)
	{
	case 1:
	{
			  MatIterator_<uchar>it, end;
			  for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			  {
				  *it = table[*it];
			  }
			  break;
	}
	case 3:
	{
			  MatIterator_<Vec3b>it, end;
			  for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
			  {
				  (*it)[0] = table[(*it)[0]];
				  (*it)[1] = table[(*it)[1]];
				  (*it)[2] = table[(*it)[2]];
			  }
	}
	}
	return I;
}

int _tmain(int argc, _TCHAR* argv[])
{
	uchar table[256];
	int divideWidth = 10;
	for (int i = 0; i < 256; ++i)
	{
		table[i] = (uchar)(divideWidth*(i / divideWidth));
	}
	//Mat lookUpTable(1, 256, CV_8U);
	Mat I = imread("1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat II = I.clone();
	Mat J = ScanImageAndReduceIterator(II, table);
	//LUT(I, lookUpTable, J);
	Mat kern = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	Mat K;
	filter2D(I, K, I.depth(), kern);
	imshow("example1", I);
	//imshow("example2",J);
	imshow("example2", K);

	cvWaitKey(0);
	cvDestroyWindow("example1");
	cvDestroyWindow("example2");

	return 0;
}

