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

struct roi_parameters             //roi����Ĳ���
{
	int16_t x;  
	int16_t y;
	int16_t width;
	int16_t height;
};
typedef QList<roi_parameters*> ROI_pars;//��������ROI���������QList

//�̳���ImgAlgorithm��
class SingleBattery : public ImgAlgorithm
{
public:	
	//typedef QList<Mat*> ROIS;//�洢������ROI������б�
	//ROIS m_rois;
	vector<Mission> vecMissions;//��������
	void getObjs();  //������в�������Ĳ���
	void doMissions();//ִ�����еĲ�������
	//ROI_pars m_roipars;//���ROI����
	//Mat ImageAverage(int imgNum);  
	//Mat getEdgeVal(Mat srcImg);
	//void createROI(Mat srcImg);//�������߳��н��յĲ����б���roi����	
	//void edge(Mat Input);//�ö�ֵ���ķ�����ȡ��Ե
	//void getCovPoint(Mat& matIn, vector<Point2i>& vecEdgePoint, int cannyL, int cannyH, int cannyCore);//canny�����ֶ�λ
	//void resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum);//��������в�ֵ
	//void getNeibor(vector<Point2i>& vecEdgePoint, Mat& matIn, Mat* matNeibor, int nbsize = 7);//��ñ�Ե7*7����matNeibor
	//void calEdgedxdy(Mat* matNeibor, int neiborNum, vector<Point2i>& vecDxdy);//��ȡ��Ե�ݶ�
	//double calRratio(double absdx, double absdy);
	//void calInterTime(vector<Point2i>& vecDxdy, int neiborNum, vector<Point2i>& vecResizeXY, Point2i VHtime);
	//void calEdgePara(Mat& matSingleResizeNeibor, Point2i resizeXY, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize, int ZerBgrL, int ZerBgrH);
	//void m_calEdgePara(Mat& matSingleResizeNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize = N, int ZerBgrL = 120, int ZerBgrH = 255);
	//void getIGrad(const Mat input, Mat& output, Mat &element);//����Ľ���̬ѧ�ݶ�����
	//void getRoughEdge(Mat& input, vector<Point2i>& vecEdgePoint);//��Ե�ֶ�λ
	//void getNewROI(vector<Point2i>& EdgePoint, Mat& matIn, Mat& matNeibor, int nbsize = 7);//��ȡ�Դֱ�ԵΪ���ĵ�roi
	//void print_px_value(Mat& im);//��ӡ��������ֵ,������
private:
	Mat batImg; //���ͼ��
	vector<ObjectOfMission> vecObj;//�����������

	void cal_Straightness(const ObjectOfMission obj, double &straightness, int n = 3);//ֱ�߶ȼ���
	//void perpendicularity();//��ֱ�ȼ���
	//void parallelism();//ƽ�жȼ���
	//void distance();//�������
	
};

//void subpixeltest(Mat OriginalImage);

#endif