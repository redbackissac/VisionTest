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

//struct roi_parameters             //roi区域的参数
//{
//	int16_t x;
//	int16_t y;
//	int16_t width;
//	int16_t height;
//};

struct ObjectOfMission//任务对象
{
	Mat roi;//对象区域
	vector<Point2d> standard;//用作比对的标准板的位置
	vector<vector<double> > Ks;//标定后获取的标定值
};


enum TypeOfMission
{
	NONE,//无任务
	STRAIGHTNESS,//	直线度
	PERPENDICULARITY,//垂直度
	PARALLELISM,//平行度
	DISTANCE//距离
};


struct Mission  //要处理的任务
{
	TypeOfMission type;//任务类型
	vector<int> vec_object;//任务对象标号向量
	void clear()//清空任务
	{
		type = NONE;
		vec_object.clear();
	}
};
typedef vector<Vec4i> VecRoiParas;//roi区域的参数(x,y,width,height)
//typedef QList<roi_parameters*> ROI_pars;//存贮所有ROI区域参数的QList

class ImgAlgorithm
{
public:
	Mat srcImg;//用于处理的源图像
	VecRoiParas vec_roipars;//roi参数向量
	vector<Mat> vec_rois;//roi向量
public:
	//typedef QList<Mat*> ROIS;//存储建立的ROI区域的列表
	//ROIS m_rois;
	void test();//用于测试

	void openImg(Mat &srcImg);//打开待处理图像
	void createROI(const Mat srcImg, vector<Mat> &vec_rois);//根据子线程中接收的参数向量创建roi区域	
	void getIGrad(const Mat input, Mat& output, Mat &element);//改进形态学梯度边缘提取
	void getRoughEdge_All(const Mat input, vector<Point2i>& vecEdgePoint);//获取所有的粗边缘点坐标
	void getRoughEdge_Normal(const Mat Input, Mat &Output, vector<Rect> &vecEdgeOutline);//获取正交粗边缘轮廓
	void getNeiborROI(const vector<Point2i> EdgePoint, const Mat matIn, Mat& matNeibor, int nbsize = 7);//获取以粗边缘为中心的邻域作为roi
	void getNeiborOfPoints(const vector<Point2i> EdgePoint, const Mat matIn, vector<Mat> &matNeibor, int nbsize = 7);//获得单个点的n*n邻域
	void getSubPixEdge(const Mat InputNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize = N, int ZerBgrL = 120, int ZerBgrH = 255);//获取亚像素边缘

	//void MeasureOneBattery();  //处理一块电池
	//
	//Mat ImageAverage(int imgNum);
	//Mat getEdgeVal(Mat srcImg);
	
	//void edge(Mat Input);//用二值化的方法提取边缘
	//void getCovPoint(Mat& matIn, vector<Point2i>& vecEdgePoint, int cannyL, int cannyH, int cannyCore);//canny方法粗定位
	//void resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum);//对邻域进行插值
	//void getNeibor(vector<Point2i>& vecEdgePoint, Mat& matIn, Mat* matNeibor, int nbsize = 7);//获得边缘7*7邻域matNeibor
	//void calEdgedxdy(Mat* matNeibor, int neiborNum, vector<Point2i>& vecDxdy);//获取边缘梯度
	//double calRratio(double absdx, double absdy);
	//void calInterTime(vector<Point2i>& vecDxdy, int neiborNum, vector<Point2i>& vecResizeXY, Point2i VHtime);
	//void calEdgePara(Mat& matSingleResizeNeibor, Point2i resizeXY, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize, int ZerBgrL, int ZerBgrH);
	//void m_calEdgePara(Mat& matSingleResizeNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize = N, int ZerBgrL = 120, int ZerBgrH = 255);
	//void getIGrad(const Mat input, Mat& output, Mat &element);//计算改进形态学梯度算子
	
	//void getNewROI(vector<Point2i>& EdgePoint, Mat& matIn, Mat& matNeibor, int nbsize = 7);//获取以粗边缘为中心的roi
	//void print_px_value(Mat& im);//打印所有像素值,调试用


	


};


#endif 