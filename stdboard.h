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
	//	struct struct_roi father_roi;//���ṹ��
	//	vector<Point2d> VecSubPixelEdgePoint;//��׼���Ե������
	//};
	Mat Img_stdboard;
};




#endif