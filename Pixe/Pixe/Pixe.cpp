// Pixe.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
int _tmain(int argc, _TCHAR* argv[])
{
	Mat m(400, 400, CV_8U, Scalar(0));
	for (int col = 0; col < 400; col++)
	{
		for (int row = 195; row < 205; row++)
		{
			cout << (int)(*(m.data + m.step[0]))
		}
	}
	return 0;
}

