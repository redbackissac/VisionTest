#pragma once
#ifndef	SINGLEBATTERY_H
#define SINGLEBATTERY_H
#include <opencv2\opencv.hpp>
#include <iostream>
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
	typedef QList<Mat*> ROIS;//存储建立的ROI区域的列表
	ROIS m_rois;
	void MeasureOneBattery();  //处理一块电池
	ROI_pars m_roipars;//存放ROI参数
	Mat ImageAverage(int imgNum);  
	Mat getEdgeVal(Mat srcImg);
	void createROI(Mat srcImg);//根据子线程中接收的参数列表创建roi区域	
	void edge(Mat Input);//用二值化的方法提取边缘
	
private:
	Mat batImg; //电池图像
	
};

#endif