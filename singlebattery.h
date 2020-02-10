#pragma once
#ifndef	SINGLEBATTERY_H
#define SINGLEBATTERY_H
#include <opencv2\opencv.hpp>
#include <iostream>
//#include <string>
#include <QImage>

using namespace cv;
using namespace std;

struct roi_parameters             //roi����Ĳ���
{
	int16_t x;  
	int16_t y;
	int16_t width;
	int16_t height;
};
typedef QList<roi_parameters*> ROI_pars;//��������ROI���������QList

class SingleBattery
{
public:	
	typedef QList<Mat*> ROIS;//�洢������ROI������б�
	ROIS m_rois;
	void MeasureOneBattery();  //����һ����
	ROI_pars m_roipars;//���ROI����
	Mat ImageAverage(int imgNum);  
	Mat getEdgeVal(Mat srcImg);
	void createROI(Mat srcImg);//�������߳��н��յĲ����б���roi����	
	void edge(Mat Input);//�ö�ֵ���ķ�����ȡ��Ե
	
//private:
	
};

#endif