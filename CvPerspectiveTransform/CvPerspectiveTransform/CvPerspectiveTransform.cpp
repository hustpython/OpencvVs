// CvPerspectiveTransform.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	//数组声明
	CvPoint2D32f srcTri[4], dstTri[4];
	//创建数组指针
	CvMat *warp_mat = cvCreateMat(3, 3, CV_32FC1);
	IplImage *src, *dst;
	//载入和显示图像
	src = cvLoadImage("bird.png", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", src);

	dst = cvCloneImage(src);
	dst->origin = src->origin;
	cvZero(dst);
	//构造变换矩阵
	srcTri[0].x = 0;
	srcTri[0].y = 0;
	srcTri[1].x = src->width - 1;
	srcTri[1].y = 0;
	srcTri[2].x = 0;
	srcTri[2].y = src->height - 1;
	srcTri[3].x = src->width - 1;
	srcTri[3].y = src->height - 1;

	dstTri[0].x = src->width*0.05;
	dstTri[0].y = src->height*0.33;
	dstTri[1].x = src->width*0.9;
	dstTri[1].y = src->height*0.25;
	dstTri[2].x = src->width*0.2;
	dstTri[2].y = src->height*0.7;
	dstTri[3].x = src->width*0.8;
	dstTri[3].y = src->height*0.9;
	//计算透视映射矩阵
	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
	//调用函数cvWarpPerspective（）
	cvWarpPerspective(src, dst, warp_mat);
	//显示透视变换后的图像
	cvNamedWindow("透视变换", CV_WINDOW_AUTOSIZE);
	cvShowImage("透视变换", dst);
	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("原图");
	cvDestroyWindow("透视变换");
	cvReleaseMat(&warp_mat);

	return 0;

}
