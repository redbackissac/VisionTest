#pragma once
#ifndef	CALIBRATION_H
#define CALIBRATION_H
#include <algorithm>
#include "singlebattery.h"
using namespace cv;
using namespace std;





class Calibration : public SingleBattery
{
public:
	void getK();//��ȡ�궨ֵ
private:
	int realSize;//�궨����С����ʵ�ʼ��
	Mat calImg;//�궨��ͼ��
	void getSmallEdgePoint(const Mat Input, Mat &Output, vector<Rect> &num_location);//��ȡС�εĴֱ�Ե����
	void getStdPixel(const Mat Input,Vec3i &Sequence);//����ֱ�Ե���������׼��׼
	int Classify(const Rect num_location, const Vec3i Sequence);//�жϴֱ�Ե�������ڱ�Ե����һ��
	void resetROI(Mat &Input, vector<Rect> num_location, const Vec3i Sequence);//У׼ROI��ȥ�������޷�����궨ֵ�Ĳ���
};


#endif // !BATTERYTEMPLATE
