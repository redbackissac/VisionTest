#ifndef H_SUBPIXELCAL
#define H_SUBPIXELCAL
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp> 
#include <iostream>
#include "zernikeMask.h"
#include <stdio.h>


#define R2D    57.295779513082323
#define Deg2Rad(Deg) (Deg)/ R2D  // �Ƕȵ�����ת��
#define Rad2Deg(Rad) (Rad)* R2D  // ���ȵ��Ƕ�ת��

#define WHITE 255
#define BLACK 0

#define YESMEDIANBLUR	true
#define NOMEDIANBLUR	false

//�ṹ�����ڴ洢���β����Ľ��
typedef struct {
	double distance_mm = 0.0;
	double distance_pixel = 0.0;
	Point2d line1_kb = Point2d(0.0, 0.0);
	Point2d line2_kb = Point2d(0.0, 0.0);
    Mat matedge = Mat();
} ZerResult;

/*������������*/
void getCovPoint(Mat& matIn, vector<Point2i>& vecEdgePoint, int cannyL=150, int cannyH=200, int cannyCore=3);
void getNeibor(vector<Point2i>& vecEdgePoint, Mat& matIn, Mat* matNeibor, int nbsize=N);
void calEdgedxdy(Mat* matNeibor, int neiborNum, vector<Point2i>& vecDxdy);
double calRratio(double absdx, double absdy);
void calInterTime(vector<Point2i>& vecDxdy, int neiborNum, vector<Point2i>& vecResizeXY,Point2i VHtime=Point2i(4,4));
void resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum);
void calEdgePara(Mat& matSingleResizeNeibor, Point2i resizeXY, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize=N, int ZerBgrL=10, int ZerBgrH=50);
void DrawRectangle(Mat& img, Rect box, int drawColor=BLACK);
void drawLine(cv::Mat &image, double theta, double rho, cv::Scalar color);

//ֱ��������
//void fitLinev3(vector<Point2d>& vecLine, float* line);

//���Ϻ���,�����з��������ڴ˺�����

ZerResult CalDistanceSquare(Mat& matRoi, double rto = MMPERPIXEL, 
		int drawColor = WHITE, 
		int cannyL = 150, int cannyH = 200, int cannyCore = 3,
		int nbsize = N, Point2i VHtime = Point2i(4, 4),
		int ZerBgrL = 10, int ZerBgrH = 50
	
	);


#endif
