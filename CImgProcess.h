#pragma once
#ifndef	CIMGPROCESS_H
#define CIMGPROCESS_H
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <QImage>

using namespace cv;

class CImgProcess
{
public:	
	Mat ImageAverage(int imgNum);  
	Mat getEdgeVal(Mat srcImg);
	Mat createROI(Mat srcImg, int x, int y, int width, int height);	
	//typedef QList<Mat> ROIS;//存储建立的ROI区域的列表
	//ROIS m_rois;
};

#endif