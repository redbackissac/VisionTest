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


enum Line_Type//��Ե������
{
	VERTICAL,	//��ֱ
	HORIZONTAL, //ˮƽ
};

struct ObjectOfMission//�������
{
	Vec4i roipars;//
	Mat roi;//��������
	vector<Point2d> VecEdgePoint;//�������ʵ�ʱ�Ե��
	Vec3f line_stds;//��ϳ���׼��ʽֱ�ߵĲ���
	vector<Point2d> standard;//�����ȶԵı�׼���λ��
	vector<vector<double> > Ks;//�궨���ȡ�ı궨ֵ
};

enum TypeOfMission //��������
{
	NONE,//������
	STRAIGHTNESS,//	ֱ�߶�
	PERPENDICULARITY,//��ֱ��
	PARALLELISM,//ƽ�ж�
	DISTANCE//����
};

struct Mission  //����
{
	TypeOfMission type;//��������
	vector<int> vec_object;//�������������
	double result = 0;//������
	void clear()//�������
	{
		type = NONE;
		vec_object.clear();
	}
};

typedef vector<Vec4i> VecRoiParas;//roi����Ĳ���(x,y,width,height)

class ImgAlgorithm
{
public:
	Mat srcImg;//���ڴ����Դͼ��
	VecRoiParas vec_roipars;//roi��������
	vector<Mat> vec_rois;//roi����
public:
	void test();//���ڲ���
	
	void openImg(Mat &srcImg);//�򿪴�����ͼ��
	void createROI(const Mat srcImg, vector<Mat> &vec_rois);//�������߳��н��յĲ�����������roi����	
	void getIGrad(const Mat input, Mat& output, Mat &element);//�Ľ���̬ѧ�ݶȱ�Ե��ȡ
	void getRoughEdge_All(const Mat input, vector<Point2i>& vecEdgePoint);//��ȡ���еĴֱ�Ե������
	void getRoughEdge_Normal(const Mat Input, Mat &Output, vector<Rect> &vecEdgeOutline);//��ȡ�����ֱ�Ե����
	void getNeiborROI(const vector<Point2i> EdgePoint, const Mat matIn, Mat& matNeibor, int nbsize = 7);//��ȡ�Դֱ�ԵΪ���ĵ�������Ϊroi
	void getNeiborOfPoints(const vector<Point2i> EdgePoint, const Mat matIn, vector<Mat> &matNeibor, int nbsize = 7);//��õ������n*n����
	void getSubPixEdge(const Mat InputNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize = N, int ZerBgrL = 120, int ZerBgrH = 255);//��ȡ�����ر�Ե
	void changeLine2std(const Vec4f InputLine, Vec3f &OutputLine);//����ϵ�ֱ��ת��Ϊax + by + c = 0�ı�׼��ʽ
};


#endif 