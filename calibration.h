#pragma once
#ifndef	CALIBRATION_H
#define CALIBRATION_H

#include "singlebattery.h"
using namespace cv;
using namespace std;

class Calibration : public SingleBattery
{
public:
	void getK();//��ȡ�궨ֵ
private:
	Mat calImg;//�궨��ͼ��
	void getSmallEdgePoint(Mat &Input, Mat Output, vector<Point2i> EdgePoint);//��ȡС�εı�Ե��

};


#endif // !BATTERYTEMPLATE
