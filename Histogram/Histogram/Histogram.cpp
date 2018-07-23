// Histogram.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#define HDIM 256
#define SRC 0
#define DST 1
int main(int argc, char** argv)
{
	
	IplImage *src = 0, *dst = 0;
	src = cvLoadImage("test3.jpg", 3);
	int n[] = { HDIM, HDIM, HDIM };
	int r[256] = { 0 }, g[256] = { 0 }, b[256] = { 0 };

	//if (argc != 2 || (src = cvLoadImage(argv[1], 3)) == NULL)    return -1;

	cvNamedWindow("source", 1);
	cvNamedWindow("result", 1);

	int width = src->width;
	int height = src->height;
	int sum = width * height;       //图像中的像素点综合
	int i, j;

	//分别统计直方图的RGB分布
	for (i = 0; i<height; i++)
	for (j = 0; j<width; j++)
	{
		b[((uchar*)(src->imageData + i*src->width))[j*src->nChannels + 0]]++;
		g[((uchar*)(src->imageData + i*src->width))[j*src->nChannels + 1]]++;
		r[((uchar*)(src->imageData + i*src->width))[j*src->nChannels + 2]]++;
		//printf("source_b=%i\n", b[((uchar*)(src->imageData + i*src->width))[j*src->nChannels + 0]]);
	}
	////构建直方图的累计分布方程，用于对直方图进行均衡化

	double val[3] = { 0 };
	for (i = 0; i<HDIM; i++)
	{
		val[0] += b[i];
		val[1] += g[i];
		val[2] += r[i];
		b[i] = val[0] * 255 / sum;
		g[i] = val[1] * 255 / sum;
		r[i] = val[2] * 255 / sum;
		//int resb = int(b[i]);
		//printf("b=%i\n", resb);
	}
	r;
	// b = {0, 1, 3, 6, 12, 19, 30, 38, 45, 52, 56, 62, 66, 71, 76, 80, 83, 86, 89, 91, 93, 95, 96, ...,255}
	// g = {0, 1, 3, 6, 12, 19, 30, 38, 45, 52, 56, 62, 66, 71, 76, 80, 83, 86, 89, 91, 93, 95, 97, ...,255}
	// r = {0, 1, 3, 6, 12, 19, 30, 39, 45, 52, 56, 62, 66, 71, 76, 80, 83, 86, 89, 91, 93, 95, 97, ...,255}
	dst = cvCreateImage(cvSize(width, height), 8, 3);
	//归一化直方图
	for (i = 0; i<height; i++)
	for (j = 0; j<width; j++)
	{
		((uchar*)(dst->imageData + i*dst->widthStep))[j*dst->nChannels + 0] = b[((uchar*)(src->imageData + i*src->widthStep))[j*src->nChannels + 0]];
		((uchar*)(dst->imageData + i*dst->widthStep))[j*dst->nChannels + 1] = g[((uchar*)(src->imageData + i*src->widthStep))[j*src->nChannels + 1]];
		((uchar*)(dst->imageData + i*dst->widthStep))[j*dst->nChannels + 2] = r[((uchar*)(src->imageData + i*src->widthStep))[j*src->nChannels + 2]];
	}
	cvShowImage("source", src);
	cvShowImage("result", dst);
	cvSaveImage("out.jpg", dst);
	cvWaitKey(0);

	cvDestroyWindow("source");
	cvDestroyWindow("result");
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	system("pause");
	return 0;
}

