// 4.17.1.cpp : 定义控制台应用程序的入口点。
//

#include"stdafx.h"  
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat o = imread("D:\\2.png", 1);
	std::vector<Mat>SrcMatpart(o.channels());
	split(o, SrcMatpart);
	Mat th;
	threshold(SrcMatpart[0], th, 140, 255, THRESH_BINARY_INV);
	vector<vector<Point>> contours;
	findContours(th, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
	//imshow("exe1", th);
	//waitKey(0);
	//return;
	cout << "num" << contours.size() << endl;
	for (auto i : contours)
	{
		//cout << i.size() << endl;
		RotatedRect rbox = minAreaRect(i);
		Point2f vtx[4];
		rbox.points(vtx);
		auto m = contourArea(i);
		if (m > 800 && m < 6400)
		{
			auto len = boundingRect(i);
			auto hvw = (double)len.width / (double)len.height;
			if (hvw>0.9&& hvw<1.1)
			{
				cout << hvw << endl;
				//if (len.width - len.height<10 && len.width - len.height > -10)
				{
					for (int i = 0; i < 4; ++i)
					{
						line(o, vtx[i], vtx[i < 3 ? i + 1 : 0], Scalar(0, 0, 255));
					}
				}
				//cout << m << endl;
			}
		}
	}



	imshow("out2", o);
	waitKey(0);
	return(0);
