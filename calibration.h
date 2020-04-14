#pragma once
#ifndef	CALIBRATION_H
#define CALIBRATION_H
#include <algorithm>
#include "singlebattery.h"
using namespace cv;
using namespace std;





class Calibration : public ImgAlgorithm
{
public:
	void getK();//��ȡ�궨ֵ
	vector<Vec3f> vec_stdLines;//��׼��ص�ֱ�߲���(a,b,c)
	vector<Line_Type> vec_linetype;//��Ե��������(��ֱ/ˮƽ)
	double REALSIZE = 5.5;//�궨��ÿһС���ʵ�ʳߴ�
private:
	Vec3i Sequence;//�ֱ�Ե���������׼
	int realSize;//�궨����С����ʵ�ʼ��
	Mat calImg;//�궨��ͼ��
	//void getSmallEdgePoint(const Mat Input, Mat &Output, vector<Rect> &num_location);//��ȡС�εĴֱ�Ե����
	Line_Type getClassifyStd(const Mat Input,Vec3i &Sequence);//����ֱ�Ե���������׼��׼
	int Classify(const Rect num_location, const Vec3i Sequence);//�жϴֱ�Ե�������ڱ�Ե����һ��
	void resetROI(Mat &Input, vector<Rect> num_location, const Vec3i Sequence);//У׼ROI��ȥ�������޷�����궨ֵ�Ĳ���

	double calDist(const Vec3f Line_1, const Vec2d EndPoint_1, const Vec3f Line_2, const Vec2d EndPoint_2);//��������ֱ�߾���
	void getStdLinePars(Mat &it_rois, const vector<Rect> vecEdgeOutline, const Line_Type type);
};


#endif // !BATTERYTEMPLATE
