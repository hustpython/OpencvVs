// Pixe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat m(400, 400, CV_8UC3, Scalar(0,0,255));
	for (int col = 0; col < 400; col++)
	{
		for (int row = 195; row < 205; row++)
		{
			cout << (int)(*(m.data + m.step[0]*row + m.step[1]*col))<<" ==> ";
			*(m.data + m.step[0] * row + m.step[1] * col) = 255;
			cout << (int)(*(m.data + m.step[0] * row + m.step[1] * col)) << endl;
		}		
	}
	imshow("canvas", m);
	//cout << "m = " << endl << " " << m << endl << endl;
	cvWaitKey();
	return 0;
}

