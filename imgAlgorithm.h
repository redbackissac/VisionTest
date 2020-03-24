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

//struct roi_parameters             //roi����Ĳ���
//{
//	int16_t x;
//	int16_t y;
//	int16_t width;
//	int16_t height;
//};

struct ObjectOfMission//�������
{
	Mat roi;//��������
	vector<Point2d> standard;//�����ȶԵı�׼���λ��
	vector<vector<double> > Ks;//�궨���ȡ�ı궨ֵ
};


enum TypeOfMission
{
	NONE,//������
	STRAIGHTNESS,//	ֱ�߶�
	PERPENDICULARITY,//��ֱ��
	PARALLELISM,//ƽ�ж�
	DISTANCE//����
};


struct Mission  //Ҫ���������
{
	TypeOfMission type;//��������
	vector<int> vec_object;//�������������
	void clear()//�������
	{
		type = NONE;
		vec_object.clear();
	}
};
typedef vector<Vec4i> VecRoiParas;//roi����Ĳ���(x,y,width,height)
//typedef QList<roi_parameters*> ROI_pars;//��������ROI���������QList

class ImgAlgorithm
{
public:
	Mat srcImg;//���ڴ����Դͼ��
	VecRoiParas vec_roipars;//roi��������
	vector<Mat> vec_rois;//roi����
public:
	//typedef QList<Mat*> ROIS;//�洢������ROI������б�
	//ROIS m_rois;
	void test();//���ڲ���

	void openImg(Mat &srcImg);//�򿪴�����ͼ��
	void createROI(const Mat srcImg, vector<Mat> &vec_rois);//�������߳��н��յĲ�����������roi����	
	void getIGrad(const Mat input, Mat& output, Mat &element);//�Ľ���̬ѧ�ݶȱ�Ե��ȡ
	void getRoughEdge_All(const Mat input, vector<Point2i>& vecEdgePoint);//��ȡ���еĴֱ�Ե������
	void getRoughEdge_Normal(const Mat Input, Mat &Output, vector<Rect> &vecEdgeOutline);//��ȡ�����ֱ�Ե����
	void getNeiborROI(const vector<Point2i> EdgePoint, const Mat matIn, Mat& matNeibor, int nbsize = 7);//��ȡ�Դֱ�ԵΪ���ĵ�������Ϊroi
	void getNeiborOfPoints(const vector<Point2i> EdgePoint, const Mat matIn, vector<Mat> &matNeibor, int nbsize = 7);//��õ������n*n����
	void getSubPixEdge(const Mat InputNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize = N, int ZerBgrL = 120, int ZerBgrH = 255);//��ȡ�����ر�Ե

	//void MeasureOneBattery();  //����һ����
	//
	//Mat ImageAverage(int imgNum);
	//Mat getEdgeVal(Mat srcImg);
	
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
	
	//void getNewROI(vector<Point2i>& EdgePoint, Mat& matIn, Mat& matNeibor, int nbsize = 7);//��ȡ�Դֱ�ԵΪ���ĵ�roi
	//void print_px_value(Mat& im);//��ӡ��������ֵ,������


	


};


#endif 