// CvMorph.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace cv;
void getmorphmat();
void showimage();
enum MORPH_METHOD
{
	enum_RECT,enum_CROSS,enum_ELLIPSE
};
int _tmain(int argc, _TCHAR* argv[])
{
	//getmorphmat();
	showimage();
	return 0;
}

void getmorphmat()
{
	Mat elementRect, elementCross, elementEllipse;
	elementRect = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	elementCross = getStructuringElement(MORPH_CROSS, Size(3, 3), Point(-1, -1));
	elementEllipse = getStructuringElement(MORPH_ELLIPSE, Size(3, 5), Point(-1, -1));

	std::cout << "3*3矩形核：" << std::endl << elementRect << std::endl;
	std::cout << "3*3十字叉形核：" << std::endl << elementCross << std::endl;
	std::cout << "3*3椭圆形核：" << std::endl << elementEllipse << std::endl;
	system("pause");
}

void showimage()
{
	Mat image, element, imageGray, imageDilate, imageErode, imageBorder;
	image = imread("map.jpg", 1);
	resize(image, image, Size(300, 300));
	cvtColor(image, imageGray, CV_RGB2GRAY);
	enum MORPH_METHOD mymorph = enum_ELLIPSE;
	switch (mymorph)
	{
	case 0:
	{
	    Mat element = getStructuringElement(0, Size(3, 3), Point(-1, -1));
		break; 
	}
	case 1:
	{
		Mat element = getStructuringElement(1, Size(3, 3), Point(-1, -1));
		break; 
	}
	case 2:
	{
		Mat element = getStructuringElement(2, Size(3, 3), Point(-1, -1));
		break;
	}

	}
	dilate(imageGray, imageDilate, element, Point(-1, -1));
	erode(imageGray, imageErode, element, Point(-1, -1));
	imageBorder = imageDilate - imageErode;
	imshow("Source image", image);
	imshow("Dilate image", imageDilate);
	imshow("Erode image", imageErode);
	imshow("Border image", imageBorder);
	waitKey();
}