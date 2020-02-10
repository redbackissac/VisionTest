#pragma once
#ifndef	SINGLEBATTERY_H
#define SINGLEBATTERY_H
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <QImage>

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

class SingleBattery
{
public:	
	ROI_pars m_roipars;//存放ROI参数
	Mat ImageAverage(int imgNum);  
	Mat getEdgeVal(Mat srcImg);
	void createROI(Mat srcImg);//根据子线程中接收的参数列表创建roi区域	
	void edge();//用二值化的方法提取边缘
	typedef QList<Mat*> ROIS;//存储建立的ROI区域的列表
	ROIS m_rois;
};

#endif