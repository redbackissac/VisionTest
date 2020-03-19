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
	void getK();//获取标定值
	double REALSIZE = 5.5;//标定板每一小格的实际尺寸
private:
	int realSize;//标定板上小格格的实际间隔
	Mat calImg;//标定板图像
	void getSmallEdgePoint(const Mat Input, Mat &Output, vector<Rect> &num_location);//获取小段的粗边缘轮廓
	void getStdPixel(const Mat Input,Vec3i &Sequence);//计算粗边缘轮廓分类标准标准
	int Classify(const Rect num_location, const Vec3i Sequence);//判断粗边缘轮廓属于边缘的哪一类
	void resetROI(Mat &Input, vector<Rect> num_location, const Vec3i Sequence);//校准ROI，去除两端无法计算标定值的部分
	void changeLine2std(const Vec4f InputLine,Vec3f &OutputLine);//将拟合的直线转换为ax + by + c = 0的标准形式
	double calDist(const Vec3f Line_1, const Vec2d EndPoint_1, const Vec3f Line_2, const Vec2d EndPoint_2);//计算两条直线距离
};


#endif // !BATTERYTEMPLATE
