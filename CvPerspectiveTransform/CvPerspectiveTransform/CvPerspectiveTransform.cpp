// CvPerspectiveTransform.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include<iostream>
#include<opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

int main()
{
	//��������
	CvPoint2D32f srcTri[4], dstTri[4];
	//��������ָ��
	CvMat *warp_mat = cvCreateMat(3, 3, CV_32FC1);
	IplImage *src, *dst;
	//�������ʾͼ��
	src = cvLoadImage("bird.png", CV_LOAD_IMAGE_UNCHANGED);
	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", src);

	dst = cvCloneImage(src);
	dst->origin = src->origin;
	cvZero(dst);
	//����任����
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
	//����͸��ӳ�����
	cvGetPerspectiveTransform(srcTri, dstTri, warp_mat);
	//���ú���cvWarpPerspective����
	cvWarpPerspective(src, dst, warp_mat);
	//��ʾ͸�ӱ任���ͼ��
	cvNamedWindow("͸�ӱ任", CV_WINDOW_AUTOSIZE);
	cvShowImage("͸�ӱ任", dst);
	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvDestroyWindow("ԭͼ");
	cvDestroyWindow("͸�ӱ任");
	cvReleaseMat(&warp_mat);

	return 0;

}
