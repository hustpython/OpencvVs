// OpenCvTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2\highgui\highgui.hpp>
int _tmain(int argc, _TCHAR* argv[])
{
	IplImage *img = cvLoadImage("1.jpg");
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", img);
	cvWaitKey(0);
	// �ڴ��ͷŹ���  
	cvReleaseImage(&img);
	// �رմ���  
	cvDestroyWindow("Example1");
	return 0;
}

