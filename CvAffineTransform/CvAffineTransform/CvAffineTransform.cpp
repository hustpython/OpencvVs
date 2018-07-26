// CvAffineTransform.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CvPoint2D32f srcTri[3], dstTri[3];
	CvMat *warp_mat = cvCreateMat(2, 3, CV_32FC1);
	CvMat *rot_mat = cvCreateMat(2, 3, CV_32FC1);
	IplImage *src = cvLoadImage("bird.png", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("原图", CV_WINDOW_AUTOSIZE);
	cvShowImage("原图", src);
	IplImage *dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
	dst = cvCloneImage(src);
	dst->origin = src->origin;
	cvZero(dst);
	srcTri[0].x = 0;
	srcTri[0].y = 0;
	srcTri[1].x = src->width - 1;
	srcTri[1].y = 0;
	srcTri[2].x = 0;
	srcTri[2].y = src->height - 1;

	dstTri[0].x = src->width*0.0;
	dstTri[0].y = src->height*0.33;
	dstTri[1].x = src->width*0.85;
	dstTri[1].y = src->height*0.25;
	dstTri[2].x = src->width*0.15;
	dstTri[2].y = src->height*0.7;

	cvGetAffineTransform(srcTri, dstTri, warp_mat);
	//调用函数cvWarpAffine（）
	cvWarpAffine(src, dst, warp_mat);
	cvNamedWindow("仿射图1", CV_WINDOW_AUTOSIZE);
	cvShowImage("仿射图1", dst);

	cvCopy(dst, src);
	//用另外一种方法得到变换矩阵，并进行仿射变换
	CvPoint2D32f center = cvPoint2D32f(src->height / 2, src->width / 2);
	double angle = -50.0;
	double scale = -0.6;
	cv2DRotationMatrix(center, angle, scale, rot_mat);

	cvWarpAffine(src, dst, rot_mat);


	cvNamedWindow("仿射图2", CV_WINDOW_AUTOSIZE);
	cvShowImage("仿射图2", dst);

	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("原图");
	cvDestroyWindow("仿射图1");
	cvDestroyWindow("仿射图2");
	cvReleaseMat(&rot_mat);
	cvReleaseMat(&warp_mat);
	return 0;
}

