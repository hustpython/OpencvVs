#include "stdafx.h"
#include "iostream"
using namespace std;
#include "opencv2/opencv.hpp"
IplImage *pGrayImage = NULL;
IplImage *pCannyImage = NULL;

const char *pImagePath = "bird.png";
const char *pGrayWindowsTitle = "Ô­Í¼";
const char *pCannyWindowsTitle = "±ßÔµ¼ì²âÍ¼";
const char *pWindowsToolBarTitle = "·§Öµ";
void onCallBack(int pos)
{
	//Canny check
	cvCanny(pGrayImage, pCannyImage, pos, pos * 3, 3);
	cvShowImage(pCannyWindowsTitle, pCannyImage);
}
int main()
{
	//load gray image from srcouce file image
	pGrayImage = cvLoadImage(pImagePath, CV_LOAD_IMAGE_GRAYSCALE);
	cvSmooth(pGrayImage, pGrayImage, CV_BLUR, 5, pGrayImage->nChannels);
	pCannyImage = cvCreateImage(cvGetSize(pGrayImage), IPL_DEPTH_8U, 1);
	//create window
	cvNamedWindow(pGrayWindowsTitle, CV_WINDOW_AUTOSIZE);
	cvNamedWindow(pCannyWindowsTitle, CV_WINDOW_AUTOSIZE);

	//creat slide bar
	int pos = 1;
	cvCreateTrackbar(pWindowsToolBarTitle, pCannyWindowsTitle, &pos, 100, onCallBack);
	onCallBack(0);

	cvShowImage(pGrayWindowsTitle, pGrayImage);
	cvShowImage(pCannyWindowsTitle, pCannyImage);

	cvWaitKey(0);
	cvDestroyWindow(pCannyWindowsTitle);
	cvDestroyWindow(pGrayWindowsTitle);
	cvReleaseImage(&pGrayImage);
	cvReleaseImage(&pCannyImage);
	return 0;
}