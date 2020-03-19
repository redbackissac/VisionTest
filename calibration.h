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
	double REALSIZE = 5.5;//�궨��ÿһС���ʵ�ʳߴ�
private:
	int realSize;//�궨����С����ʵ�ʼ��
	Mat calImg;//�궨��ͼ��
	void getSmallEdgePoint(const Mat Input, Mat &Output, vector<Rect> &num_location);//��ȡС�εĴֱ�Ե����
	void getStdPixel(const Mat Input,Vec3i &Sequence);//����ֱ�Ե���������׼��׼
	int Classify(const Rect num_location, const Vec3i Sequence);//�жϴֱ�Ե�������ڱ�Ե����һ��
	void resetROI(Mat &Input, vector<Rect> num_location, const Vec3i Sequence);//У׼ROI��ȥ�������޷�����궨ֵ�Ĳ���
	void changeLine2std(const Vec4f InputLine,Vec3f &OutputLine);//����ϵ�ֱ��ת��Ϊax + by + c = 0�ı�׼��ʽ
	double calDist(const Vec3f Line_1, const Vec2d EndPoint_1, const Vec3f Line_2, const Vec2d EndPoint_2);//��������ֱ�߾���
};


#endif // !BATTERYTEMPLATE
