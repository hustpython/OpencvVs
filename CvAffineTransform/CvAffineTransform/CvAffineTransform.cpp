// CvAffineTransform.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", src);
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
	//���ú���cvWarpAffine����
	cvWarpAffine(src, dst, warp_mat);
	cvNamedWindow("����ͼ1", CV_WINDOW_AUTOSIZE);
	cvShowImage("����ͼ1", dst);

	cvCopy(dst, src);
	//������һ�ַ����õ��任���󣬲����з���任
	CvPoint2D32f center = cvPoint2D32f(src->height / 2, src->width / 2);
	double angle = -50.0;
	double scale = -0.6;
	cv2DRotationMatrix(center, angle, scale, rot_mat);

	cvWarpAffine(src, dst, rot_mat);


	cvNamedWindow("����ͼ2", CV_WINDOW_AUTOSIZE);
	cvShowImage("����ͼ2", dst);

	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("ԭͼ");
	cvDestroyWindow("����ͼ1");
	cvDestroyWindow("����ͼ2");
	cvReleaseMat(&rot_mat);
	cvReleaseMat(&warp_mat);
	return 0;
}

