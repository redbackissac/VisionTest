#pragma once
#ifndef	SINGLEBATTERY_H
#define SINGLEBATTERY_H
#include <opencv2\opencv.hpp>
#include <iostream>
#include <QImage>
#include<limits.h>
#include "zernikeMask.h"
#include "imgAlgorithm.h"

using namespace cv;
using namespace std;

struct roi_parameters             //roi区域的参数
{
	int16_t x;  
	int16_t y;
	int16_t width;
	int16_t height;
};
typedef QList<roi_parameters*> ROI_pars;//存贮所有ROI区域参数的QList

//继承自ImgAlgorithm类
class SingleBattery : public ImgAlgorithm
{
public:	
	//typedef QList<Mat*> ROIS;//存储建立的ROI区域的列表
	//ROIS m_rois;
	vector<Mission> vecMissions;//任务向量
	void getObjs();  //获得所有测量对象的参数
	void doMissions();//执行所有的测量任务
	//ROI_pars m_roipars;//存放ROI参数
	//Mat ImageAverage(int imgNum);  
	//Mat getEdgeVal(Mat srcImg);
	//void createROI(Mat srcImg);//根据子线程中接收的参数列表创建roi区域	
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
	//void getRoughEdge(Mat& input, vector<Point2i>& vecEdgePoint);//边缘粗定位
	//void getNewROI(vector<Point2i>& EdgePoint, Mat& matIn, Mat& matNeibor, int nbsize = 7);//获取以粗边缘为中心的roi
	//void print_px_value(Mat& im);//打印所有像素值,调试用
private:
	Mat batImg; //电池图像
	vector<ObjectOfMission> vecObj;//任务对象向量

	void cal_Straightness(const ObjectOfMission obj, double &straightness, int n = 3);//直线度计算
	//void perpendicularity();//垂直度计算
	//void parallelism();//平行度计算
	//void distance();//距离计算
	
};

//void subpixeltest(Mat OriginalImage);

#endif