// OpenCvTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\highgui\highgui.hpp>
int _tmain(int argc, _TCHAR* argv[])
{
	IplImage *img = cvLoadImage("1.jpg");
	cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example1", img);
	cvWaitKey(0);
	// 内存释放功能  
	cvReleaseImage(&img);
	// 关闭窗口  
	cvDestroyWindow("Example1");
	return 0;
}

