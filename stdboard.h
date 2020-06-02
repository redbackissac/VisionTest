#pragma once
#ifndef	STDBOARD_H
#define STDBOARD_H
#include <algorithm>
#include "singlebattery.h"
using namespace cv;
using namespace std;

class StdBoard : public ImgAlgorithm
{
public:
	void get_stdPoint();
private:
	//struct m_struct_roi
	//{
	//	struct struct_roi father_roi;//父结构体
	//	vector<Point2d> VecSubPixelEdgePoint;//标准板边缘点坐标
	//};
	Mat Img_stdboard;
};




#endif