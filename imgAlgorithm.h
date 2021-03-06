#pragma once
#ifndef	IMGALGORITHM_H
#define IMGALGORITHM_H
#include <opencv2\opencv.hpp>
#include <iostream>
#include <QImage>
#include<limits.h>
#include "zernikeMask.h"

using namespace cv;
using namespace std;


enum Line_Type//边缘的类型
{
	VERTICAL,	//竖直
	HORIZONTAL, //水平
};

struct ObjectOfMission//任务对象
{
	Vec4i roipars;//
	Mat roi;//对象区域
	Line_Type type;//对象直线的类型
	vector<Point2d> VecEdgePoint;//计算出的实际边缘点与标准板的差值
	Vec3f line_stds;//拟合出标准形式直线的参数
	vector<Point2d> standard;//用作比对的标准板的位置
	vector<vector<double> > Ks;//标定后获取的标定值
};

enum TypeOfMission //任务类型
{
	NONE,//无任务
	STRAIGHTNESS,//	直线度
	PERPENDICULARITY,//垂直度
	PARALLELISM,//平行度
	DISTANCE//距离
};

struct Mission  //任务
{
	TypeOfMission type;//任务类型
	vector<int> vec_object;//任务对象标号向量
	double result = 0;//计算结果
	void clear()//清空任务
	{
		type = NONE;
		vec_object.clear();
	}
};



typedef vector<Vec4i> VecRoiParas;//roi区域的参数(x,y,width,height)


struct struct_roi
{
	int ID;//roi的id
	Vec4i roipar; //roi参数(x,y,width,height)
	Mat roi;            //roi区域图像
	Line_Type linetype; //roi中边缘类型(水平/竖直)
	Vec3f stdline;      //标准直线参数(a,b,c)
	vector<Point2d> VecSubPixelEdgePoint;//标准板边缘点坐标
};

class ImgAlgorithm
{
public:
	Mat srcImg;//用于处理的源图像
	
	vector<struct_roi> vec_strrois;//roi结构体向量
	VecRoiParas vec_roipars;//roi参数向量
	vector<Mat> vec_rois;//roi向量
	vector<Vec3f> vec_stdLines;//标准电池的直线参数(a,b,c)
	vector<Line_Type> vec_linetype;//边缘类型向量(竖直/水平)
public:
	void test();//用于测试
	
	void openImg(Mat &srcImg);//打开待处理图像
	void createROI(const Mat srcImg, vector<Mat> &vec_rois);//根据子线程中接收的参数向量创建roi区域	
	void createROI(const Mat srcImg, vector<struct_roi> &vec_strrois);//重载，用于测量过程中创建roi
	void getIGrad(const Mat input, Mat& output, Mat &element);//改进形态学梯度边缘提取
	void getRoughEdge_All(const Mat input, vector<Point2i>& vecEdgePoint);//获取所有的粗边缘点坐标
	void getRoughEdge_Normal(const Mat Input, Mat &Output, vector<Rect> &vecEdgeOutline);//获取正交粗边缘轮廓
	void getNeiborROI(const Line_Type type, const vector<Point2i> EdgePoint, const Mat matIn, Mat& matNeibor, Point2d &point, int nbsize = 7);//获取以粗边缘为中心的邻域作为roi
	void getNeiborOfPoints(const vector<Point2i> EdgePoint, const Mat matIn, vector<Mat> &matNeibor, int nbsize = 7);//获得单个点的n*n邻域
	void getSubPixEdge(const Mat InputNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize = N, int ZerBgrL = 120, int ZerBgrH = 255);//获取亚像素边缘
	void changeLine2std(const Vec4f InputLine, Vec3f &OutputLine);//将拟合的直线转换为ax + by + c = 0的标准形式
};


#endif 