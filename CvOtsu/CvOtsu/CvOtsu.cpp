// CvOtsu.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int Otsu(IplImage *src);
int _tmain(int argc, _TCHAR* argv[])
{
	IplImage *src = cvLoadImage("house.jpeg", -1);
	IplImage *img = cvLoadImage("house.jpeg",0);
	IplImage *dst = cvCreateImage(cvGetSize(img), 8, 1);
	int threshold = Otsu(img);
	cvThreshold(img, dst, threshold, 255, CV_THRESH_BINARY);
	cvNamedWindow("dst", 1);
	cvShowImage("dst", dst);
	cvNamedWindow("img", 1);
	cvShowImage("img", img);
	cvNamedWindow("src", 1);
	cvShowImage("src", src);
	cvWaitKey(-1);
	cvReleaseImage(&img);
	cvReleaseImage(&dst);
	cvDestroyWindow("img");
	cvDestroyWindow("dst");
	cvDestroyWindow("src");
	
	return 0;
}

int Otsu(IplImage* src)
{
	int height = src->height;
	int width = src->width;
	long size = height * width;
	//histogram 
	//ͨ���ۼƷֲ���������ֱ��ͼ
	float histogram[256] = { 0 };
	for (int m = 0; m < height; m++)
	{
		//pָ���m���׵�ַ
		unsigned char* p = (unsigned char*)src->imageData + src->widthStep * m;
		for (int n = 0; n < width; n++)
		{
			//�����ƶ�m�еĵ�ַ,������Ԫ��ֵ����Ӧ��histogram�ĸ�������
			//*p++;ȡpֵ����*p = 10;��histogram[10] += 1;Ȼ��ָ��������
			//����һ����ַ
			histogram[int(*p++)]++;
		}
	}

	int threshold;
	long sum0 = 0, sum1 = 0; //�洢ǰ���ĻҶ��ܺͺͱ����Ҷ��ܺ�  
	long cnt0 = 0, cnt1 = 0; //ǰ�����ܸ����ͱ������ܸ���  
	double w0 = 0, w1 = 0; //ǰ���ͱ�����ռ����ͼ��ı���  
	double u0 = 0, u1 = 0;  //ǰ���ͱ�����ƽ���Ҷ�  
	double variance = 0; //�����䷽��  
	int i, j;
	double u = 0;
	double maxVariance = 0;
	for (i = 1; i < 256; i++) //һ�α���ÿ������  
	{
		sum0 = 0;
		sum1 = 0;
		cnt0 = 0;
		cnt1 = 0;
		w0 = 0;
		w1 = 0;
		for (j = 0; j < i; j++)
		{
			cnt0 += histogram[j];
			sum0 += j * histogram[j];
		}

		u0 = (double)sum0 / cnt0;
		w0 = (double)cnt0 / size;

		for (j = i; j <= 255; j++)
		{
			cnt1 += histogram[j];
			sum1 += j * histogram[j];
		}

		u1 = (double)sum1 / cnt1;
		w1 = 1 - w0; // (double)cnt1 / size;  

		u = u0 * w0 + u1 * w1; //ͼ���ƽ���Ҷ�  
		printf("u = %f\n", u);
		//variance =  w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);  
		variance = w0 * w1 *  (u0 - u1) * (u0 - u1);
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = i;
		}
	}

	printf("threshold = %d,maxVariance=%f\n", threshold, maxVariance);
	return threshold;
}

