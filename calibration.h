#pragma once
#ifndef	CALIBRATION_H
#define CALIBRATION_H

#include "singlebattery.h"
using namespace cv;
using namespace std;

class Calibration : public SingleBattery
{
public:
	void getK();//获取标定值
private:
	Mat calImg;//标定板图像
	void getSmallEdgePoint(Mat &Input, Mat Output, vector<Point2i> EdgePoint);//获取小段的边缘点

};


#endif // !BATTERYTEMPLATE
