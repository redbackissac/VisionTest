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
	void getK();//获取标定值
	vector<Vec3f> vec_stdLines;//标准电池的直线参数(a,b,c)
	vector<Line_Type> vec_linetype;//边缘类型向量(竖直/水平)
	double REALSIZE = 5.5;//标定板每一小格的实际尺寸
private:
	Vec3i Sequence;//粗边缘轮廓分类标准
	int realSize;//标定板上小格格的实际间隔
	Mat calImg;//标定板图像
	//void getSmallEdgePoint(const Mat Input, Mat &Output, vector<Rect> &num_location);//获取小段的粗边缘轮廓
	Line_Type getClassifyStd(const Mat Input,Vec3i &Sequence);//计算粗边缘轮廓分类标准标准
	int Classify(const Rect num_location, const Vec3i Sequence);//判断粗边缘轮廓属于边缘的哪一类
	void resetROI(Mat &Input, vector<Rect> num_location, const Vec3i Sequence);//校准ROI，去除两端无法计算标定值的部分

	double calDist(const Vec3f Line_1, const Vec2d EndPoint_1, const Vec3f Line_2, const Vec2d EndPoint_2);//计算两条直线距离
	void getStdLinePars(Mat &it_rois, const vector<Rect> vecEdgeOutline, const Line_Type type);
};


#endif // !BATTERYTEMPLATE
