// MaskOperation.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;
void Sharpen(const Mat& myImage, Mat& Result);
int _tmain(int argc, _TCHAR* argv[])
{
	Mat M = imread("fruits.jpg", CV_LOAD_IMAGE_COLOR);
	Mat R ,K;
	imshow("Original Image",M);
	double t = (double)getTickCount();
	//使用手写的mask operation 进行锐化操作
	Sharpen(M, R);
	t = ((double)getTickCount() - t) / getTickCount();
	cout << "Hand written function times passed seconds:" << t << endl;
	imshow("Sharpen Image", R);
	cvWaitKey(0);
	//调用内部的滤波函数进行锐化
	Mat kern = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	t = (double)getTickCount();
	filter2D(M, K, M.depth(), kern);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Built-in filter2D time passed seconds:" << t << endl;
	imshow("Filter2D Image", K);
	cvWaitKey(0);
	cvDestroyAllWindows();
	return 0;
}
void Sharpen(const Mat& myImage, Mat& Result)
{
	CV_Assert(myImage.depth() == CV_8U);
	Result.create(myImage.size(), myImage.type());
	const int nChannels = myImage.channels();

	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const uchar *previous = myImage.ptr<uchar>(j - 1);
		const uchar *current = myImage.ptr<uchar>(j);
		const uchar *next = myImage.ptr<uchar>(j + 1);
		uchar *output = Result.ptr<uchar>(j);

		for (int i = nChannels; i < nChannels*(myImage.cols - 1); ++i)
		{
			*output++ = saturate_cast<uchar>(5 * current[i] - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);

		}
	}
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
}
