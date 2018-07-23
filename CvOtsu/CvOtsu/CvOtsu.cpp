// CvOtsu.cpp : 定义控制台应用程序的入口点。
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
	//通过累计分布函数计算直方图
	float histogram[256] = { 0 };
	for (int m = 0; m < height; m++)
	{
		//p指向第m行首地址
		unsigned char* p = (unsigned char*)src->imageData + src->widthStep * m;
		for (int n = 0; n < width; n++)
		{
			//依次移动m行的地址,并将该元素值所对应的histogram的个数增加
			//*p++;取p值，如*p = 10;则histogram[10] += 1;然后指向所在行
			//的下一个地址
			histogram[int(*p++)]++;
		}
	}

	int threshold;
	long sum0 = 0, sum1 = 0; //存储前景的灰度总和和背景灰度总和  
	long cnt0 = 0, cnt1 = 0; //前景的总个数和背景的总个数  
	double w0 = 0, w1 = 0; //前景和背景所占整幅图像的比例  
	double u0 = 0, u1 = 0;  //前景和背景的平均灰度  
	double variance = 0; //最大类间方差  
	int i, j;
	double u = 0;
	double maxVariance = 0;
	for (i = 1; i < 256; i++) //一次遍历每个像素  
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

		u = u0 * w0 + u1 * w1; //图像的平均灰度  
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

