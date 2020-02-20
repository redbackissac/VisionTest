#include "subPixelCal.h"

/*ȫ�ֱ���*/
bool drawRectangle = false;
//�����������ѡ������
vector<Rect> vevRec;
Rect rect;
//Բ���������ѡ������
vector<Rect> vevRecCir;
Rect rectCir;
using namespace cv;
using namespace std;

void ResetRect(){
   vevRec.clear();
   vevRecCir.clear();
   rect = Rect();
   rectCir = Rect();
}

/*��ôֱ�Եλ��vecEdgePoint*/
void getCovPoint(Mat& matIn, vector<Point2i>& vecEdgePoint, int cannyL, int cannyH,int cannyCore)
{
	Point2i  pointTemp;
	Mat matCanny;
	Canny(matIn, matCanny, cannyL, cannyH, cannyCore);
	for (int i = 0; i < matCanny.rows; i++)
	{
		for (int j = 0; j < matCanny.cols; j++)
		{
			if (matCanny.at<uchar>(i, j) == 255)
			{
				pointTemp.x = i;
				pointTemp.y = j;
				vecEdgePoint.push_back(pointTemp);
			}
		}
	}
}

void getNeibor(vector<Point2i>& vecEdgePoint, Mat& matIn, Mat* matNeibor, int nbsize)
{
	Mat matInRoi, matNewRoi;
	int halfN = (nbsize - 1) / 2;
	for (int i = 0; i < vecEdgePoint.size(); i++)
	{
		matInRoi = matIn(Rect(vecEdgePoint[i].y, vecEdgePoint[i].x, 1, 1));
		matInRoi.adjustROI(halfN, halfN, halfN, halfN);
		matNeibor[i] = matInRoi;
	}
}

void calEdgedxdy(Mat* matNeibor, int neiborNum, vector<Point2i>& vecDxdy)
{
	Mat matTemp;
	Point2i dxdy;
	for (int i = 0; i < neiborNum; i++)
	{
		matTemp = matNeibor[i];
		matTemp.convertTo(matTemp, CV_64FC1);
		double dx = matTemp.dot(SOBELX);
		double dy = matTemp.dot(SOBELY);
		dxdy.x = dx;
		dxdy.y = dy;
		vecDxdy.push_back(dxdy);
	}

}
double calRratio(double absdx, double absdy)
{
	double ratio;
	if (absdx>absdy)
	{
		ratio = absdy / absdx;
	}
	else
	{
		ratio = absdx / absdy;
	}
	return ratio;
}

void calInterTime(vector<Point2i>& vecDxdy, int neiborNum, vector<Point2i>& vecResizeXY, Point2i VHtime)
{
	Point2i resizeXYtime;
	int thresholdHori = 200;
	for (int i = 0; i < neiborNum; i++)
	{
		int dx = abs(vecDxdy[i].x);
		int dy = abs(vecDxdy[i].y);
		int diff = abs(dx - dy);
		/*����ˮƽ��Ե�ʹ�ֱ��Ե*/
		if (diff > thresholdHori)
		{
			resizeXYtime.x = VHtime.x;
			resizeXYtime.y = VHtime.y;
			vecResizeXY.push_back(resizeXYtime);
		}
		/*����������Ե*/
		else
		{
			double ratio = calRratio(dx, dy);
			resizeXYtime.y = 5;

			if (ceil(5.000 * ratio) != 0)
			{
				resizeXYtime.x = ceil(5.000 * ratio);
			}
			else
			{
				resizeXYtime.x = 1;
			}
			vecResizeXY.push_back(resizeXYtime);


		}
	}

}
void resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum)
{
	for (int i = 0; i < neiborNum; i++)
	{
		resize(matNeibor[i], matResizeNeibor[i], Size(N * vecResizeXY[i].x, N * vecResizeXY[i].y));
	}

}
void calEdgePara(Mat& matSingleResizeNeibor, Point2i resizeXY, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize,int ZerBgrL,int ZerBgrH)
{

	Vec4d  para;
	Point2d point;

	Mat mZerImageM00;
	Mat mZerImageM11R;
	Mat mZerImageM11I;
	Mat mZerImageM20;
	Mat mZerImageM31R;
	Mat mZerImageM31I;
	Mat mZerImageM40;

	//���
	filter2D(matSingleResizeNeibor, mZerImageM00, CV_64F, ZERPOLY00);
	filter2D(matSingleResizeNeibor, mZerImageM11R, CV_64F, ZERPOLY11R);
	filter2D(matSingleResizeNeibor, mZerImageM11I, CV_64F, ZERPOLY11I);
	filter2D(matSingleResizeNeibor, mZerImageM20, CV_64F, ZERPOLY20);
	filter2D(matSingleResizeNeibor, mZerImageM31R, CV_64F, ZERPOLY31R);
	filter2D(matSingleResizeNeibor, mZerImageM31I, CV_64F, ZERPOLY31I);
	filter2D(matSingleResizeNeibor, mZerImageM40, CV_64F, ZERPOLY40);
	double rotated_z11 = 0.0;
	double rotated_z31 = 0.0;
	double l_method1 = 0.0;
	double l_method2 = 0.0;

	double l_t1 = sqrt(2) / (2.00 * nbsize);
	double l_t2 = sqrt(2) / 2.00;

	int row_number = matSingleResizeNeibor.rows;
	int col_number = matSingleResizeNeibor.cols;
	for (int i = 0; i < row_number; i++)
	{
		for (int j = 0; j < col_number; j++)
		{
			if (mZerImageM00.at<double>(i, j) == 0)
			{
				continue;
			}
			para[THETA] = atan2(mZerImageM31I.at<double>(i, j), mZerImageM31R.at<double>(i, j));

			//����Z11'��Z31'Ϊ����L1,L2��׼��,rotated_z11=Z11',rotated_z31=Z31'

			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));

			//����L1��L2,
			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
			para[L] = (l_method1 + l_method2) / 2;
			//l = l - 0.207107;//��ȥ����ֵk

			//����k��h 
			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;

			vecPara.push_back(para);
			/*��ֵ����*/
			if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH)
			{
				/*��Ե�߶Ȼָ�*/
				point.x = (j + para[L] * nbsize*cos(para[THETA]) / 2.00) / (double)resizeXY.x;
				point.y = (i + para[L] * nbsize*sin(para[THETA]) / 2.00) / (double)resizeXY.y;
				subPixelRela.push_back(point);

			}

		}
	}
}


void DrawRectangle(Mat& img, Rect box, int drawColor)
{
	rectangle(img, box, Scalar(drawColor));
}
void drawLine(cv::Mat &image, double theta, double rho, cv::Scalar color)
{
	if (theta < PI / 4. || theta > 3.*PI / 4.)// ~vertical line
	{
		cv::Point pt1(rho / cos(theta), 0);
		cv::Point pt2((rho - image.rows * sin(theta)) / cos(theta), image.rows);
		cv::line(image, pt1, pt2, cv::Scalar(255), 1);
	}
	else
	{
		cv::Point pt1(0, rho / sin(theta));
		cv::Point pt2(image.cols, (rho - image.cols * cos(theta)) / sin(theta));
		cv::line(image, pt1, pt2, color, 1);
	}
}

//void fitLinev3(vector<Point2d>& vecLine, float* line)
//{
//	char key;
//	int i;
//	int count = vecLine.size();;
//	Point* points = (Point*)malloc(count * sizeof(points[0])); //�����������ĵ�㣬��ĿΪcount
//	Mat pointMat = Mat(1, count, CV_32SC2, points); //�㼯, �洢count�������points
//
//	for (int i = 0; i <count; i++)
//	{
//		points[i].x = vecLine[i].x;
//		points[i].y = vecLine[i].y;
//	}
//
//	fitLine(pointMat, line, CV_DIST_HUBER, 1, 0.000001, 0.000001, );
//
//}
ZerResult CalDistanceSquare(Mat& matRoi, double rto, int drawColor,
	int cannyL, int cannyH, int cannyCore, int nbsize, Point2i VHtime,
	int ZerBgrL, int ZerBgrH)
{
	ZerResult result;
	
	//��������
	Mat matRoiBlur;	
	matRoiBlur = matRoi;
							

	/*��ôֱ�Եλ��vecEdgePoint*/
	vector<Point2i> vecEdgePoint;
	vector<Point2i> vecEdgePointPart;//(row,col)
	getCovPoint(matRoiBlur, vecEdgePoint, cannyL, cannyH, cannyCore);

    /*select ROI*/
	Mat tempImg;
    namedWindow("diagram");
    imshow("diagram", matRoi);
	char wait;
   // setMouseCallback("diagram", on_MouseHandle, (void*)&matRoi);
	while (1)
	{
		matRoi.copyTo(tempImg);

		if (drawRectangle)
		{
			DrawRectangle(tempImg, rect, drawColor);
		}
        imshow("diagram", tempImg);
        /*enter Esc to quit*/
		wait = waitKey(10);
		if (wait == 27)
		{
			break;
		}
	}

	/*����1���ϽǺ����½�(x, y)*/
	Point tl1 = vevRec[0].tl();
	Point br1 = vevRec[0].br();
	/*����2���ϽǺ����½�*/
	Point tl2 = vevRec[1].tl();
	Point br2 = vevRec[1].br();
	//vector<Point2d> vecLine3;
	/*�����ݴ����*/
	double tempx, tempy;

	for (int i = 0; i < vecEdgePoint.size(); i++)
	{
		tempx = vecEdgePoint[i].y;
		tempy = vecEdgePoint[i].x;
		if (tempx>tl1.x && tempx<br1.x && tempy>tl1.y && tempy<br1.y)
		{		
			vecEdgePointPart.push_back(vecEdgePoint[i]);
		}
		if (tempx>tl2.x && tempx<br2.x && tempy>tl2.y && tempy<br2.y)
		{
			vecEdgePointPart.push_back(vecEdgePoint[i]);
		}
		/*tempx = vecEdgePoint[i].x;
		tempy = vecEdgePoint[i].y;
		vecEdgePointPart.push_back(vecEdgePoint[i]);*/

	}
    /*ʾ�ⲿ�֣�����pixel����ȡ�������ں�ɫ������*/
	//Mat matBlackboard(matRoiBlur.size(), CV_8UC1, Scalar(0));

	//Point center_forshow;
	//for (int i = 0; i < vecEdgePointPart.size(); i++)
	//{
	//	center_forshow.x = cvRound(vecEdgePointPart[i].x);
	//	center_forshow.y = cvRound(vecEdgePointPart[i].y);
	//	circle(matBlackboard, center_forshow, 0.01, Scalar(255), -1);//����(x, y)��
	//}
	//imshow("test", matBlackboard);


	/*��ñ�Ե7*7����matAllNeibor*/
	int neiborNum;
	Mat* matAllNeibor;
	neiborNum = vecEdgePointPart.size();
	matAllNeibor = new Mat[neiborNum];
	getNeibor(vecEdgePointPart, matRoiBlur, matAllNeibor, nbsize);

	/*�����ھ��*/
	/*�����Ե��dx,dy*/
	vector<Point2i> vecDxdy;
	//���ڱ�׼��ѧ����
	calEdgedxdy(matAllNeibor, neiborNum, vecDxdy);

	/*ͨ���ݶȣ�dx��dy��ȷ�������ֵ���򣨱�����*/
	vector<Point2i> vecResizeXY;
	calInterTime(vecDxdy, neiborNum, vecResizeXY, VHtime);

	/*��������в�ֵ���Ҽ����Ե����*/
	Mat* matResizeNeibor;
	matResizeNeibor = new Mat[neiborNum];
	resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);

	/*���㵥������ľ��Ա�Ե����*/
	vector<Vec4d> vecPara;
	vector<Point2d> subPixelRela;
	vector<Point2d> subPixelabs;
	Point2d tempPoint;

	for (int i = 0; i < neiborNum; i++)
	{
		calEdgePara(matResizeNeibor[i], vecResizeXY[i], vecPara, subPixelRela, nbsize, ZerBgrL, ZerBgrH);
		for (int in = 0; in<subPixelRela.size(); in++)
		{
			/*�������ת��ͼ����ͼ���ľ�������*/
			tempPoint.x = (double)vecEdgePointPart[i].y + (subPixelRela[in].x - (nbsize - 1.00) / 2.00);
			tempPoint.y = (double)vecEdgePointPart[i].x + (subPixelRela[in].y - (nbsize - 1.00) / 2.00);
            /*�����pixel����*/
			subPixelabs.push_back(tempPoint);
		}
		subPixelRela.clear();

	}
    /*ʾ�ⲿ�֣�����pixel����ȡ�������ں�ɫ������*/
	Mat matBlackboard(matRoiBlur.size(), CV_8UC1, Scalar(0));

	//Point center_forshow;
	//for (int i = 0; i < subPixelabs.size(); i++)
	//{
	//	center_forshow.x = cvRound(subPixelabs[i].x);
	//	center_forshow.y = cvRound(subPixelabs[i].y);
	//	circle(matBlackboard, center_forshow, 0.01, Scalar(255), -1);
	//}
	//imshow("test", matBlackboard);

	/*����ͬ�ĵ���ൽ��ͬ������*/
	vector<Point2d> vecLine1;
	vector<Point2d> vecLine2;

	
	for (int i = 0; i<subPixelabs.size(); i++)
	{
		tempx = subPixelabs[i].x;
		tempy = subPixelabs[i].y;
		if (tempx>tl1.x && tempx<br1.x && tempy>tl1.y && tempy<br1.y)
		{
			vecLine1.push_back(subPixelabs[i]);
		}
		if (tempx>tl2.x && tempx<br2.x && tempy>tl2.y && tempy<br2.y)
		{
			vecLine2.push_back(subPixelabs[i]);
		}
	}


	/*ֱ����ϲ���*/
    Mat edgeLine(matRoi.size(), CV_8UC1, Scalar(0));
	float line1[4];
	float line2[4];
	//fitLinev3(vecLine1, line1);
	//fitLinev3(vecLine2, line2);

	/*�����ϵ�ֱ��*/
	double cos_theta1 = line1[0];
	double sin_theta1 = line1[1];
	double x01 = line1[2], y01 = line1[3];
	double phi1 = atan2(sin_theta1, cos_theta1) + PI / 2.0;
	double rho1 = y01 * cos_theta1 - x01 * sin_theta1;

	double cos_theta2 = line2[0];
	double sin_theta2 = line2[1];
	double x02 = line2[2], y02 = line2[3];
	double phi2 = atan2(sin_theta2, cos_theta2) + PI / 2.0;
	double rho2 = y02 * cos_theta2 - x02 * sin_theta2;

    drawLine(edgeLine, phi1, rho1, Scalar(255));
    drawLine(edgeLine, phi2, rho2, Scalar(255));
    imshow("ֱ�����", edgeLine);

	/*��������ֱ�ߵľ���*/
	float k1 = line1[1] / line1[0];
	float k2 = line2[1] / line2[0];

	float b1 = line1[3] - k1*line1[2];
	float b2 = line2[3] - k2*line2[2];
	double distance = abs(line1[0] * (line2[3] - line1[3]) - line1[1] * (line2[2] - line1[2]));

	/*���������Ϣ*/
    std::cout<<"\n-----------------------------------------------------------------------------------------\n";
    printf("Line 1 equation: y=%fx+%f \n", k1, b1);
    printf("Line 2 equation: y=%fx+%f \n", k2, b2);
    cout << "distance between two lines�� " << distance << "pixel" << endl;
    cout << "convert accroding to standard  picture [0.01453mm/pixel]" << endl;
    cout << "real distance between two lines:" << rto*distance << endl;
    cout << "deviation" << 10 - rto*distance << "mm" << endl;

    result.matedge = edgeLine;
	result.distance_mm = rto*distance;
	result.distance_pixel = distance;

	result.line1_kb = Point2d(k1, b1);
	result.line2_kb = Point2d(k2, b2);

    ResetRect();
	return result;
}
//ZerResultCir CalDistanceCircle(Mat& matRoi,double rto, int drawColor, bool ifmedianBlur,
//	int cannyL, int cannyH, int cannyCore, int nbsize, Point2i VHtime,
//	int ZerBgrL, int ZerBgrH)
//{
//	ZerResultCir result;
//	
//	//��������
//	Mat matRoiBlur;
//	if (ifmedianBlur == true)
//	{
//		medianBlur(matRoi, matRoiBlur, 3);//��ֵ�˲�	
//	}
//	else
//	{
//		matRoiBlur = matRoi;
//	}
//
//	/*��ôֱ�Եλ��vecEdgePoint*/
//	vector<Point2i> vecEdgePoint;
//	vector<Point2i> vecEdgePointPart;
//	getCovPoint(matRoiBlur, vecEdgePoint, cannyL, cannyH, cannyCore);
//
//	////////////////////////////////
//    /*select ROI*/
//	Mat tempImg;
//    namedWindow("diagram");
//    imshow("diagram", matRoi);
//	char wait;
//    setMouseCallback("diagram", on_MouseHandleCir, (void*)&matRoi);
//	while (1)
//	{
//		matRoi.copyTo(tempImg);
//
//		if (drawRectangle)
//		{
//			DrawRectangle(tempImg, rectCir, drawColor);
//		}
//        imshow("diagram", tempImg);
//        /*enter Esc to quit*/
//		wait = waitKey(10);
//		if (wait == 27)
//		{
//			break;
//		}
//
//	}
//
//	/*����1���ϽǺ����½�(x, y)*/
//	Point tl1 = vevRecCir[0].tl();
//	Point br1 = vevRecCir[0].br();
//	///*����2���ϽǺ����½�*/
//	//Point tl2 = vevRec[1].tl();
//	//Point br2 = vevRec[1].br();
//	////vector<Point2d> vecLine3;
//	/*�����ݴ����*/
//	double tempx, tempy;
//
//	for (int i = 0; i < vecEdgePoint.size(); i++)
//	{
//		tempx = vecEdgePoint[i].y;
//		tempy = vecEdgePoint[i].x;
//		if (tempx>tl1.x && tempx<br1.x && tempy>tl1.y && tempy<br1.y)
//		{
//			vecEdgePointPart.push_back(vecEdgePoint[i]);
//		}
//		//if (tempx>tl2.x && tempx<br2.x && tempy>tl2.y && tempy<br2.y)
//		//{
//		//	vecEdgePointPart.push_back(vecEdgePoint[i]);
//		//}
//		/*tempx = vecEdgePoint[i].x;
//		tempy = vecEdgePoint[i].y;
//		vecEdgePointPart.push_back(vecEdgePoint[i]);*/
//
//	}
//
//
//
//	/*��ñ�Ե7*7����matAllNeibor*/
//	int neiborNum;
//	Mat* matAllNeibor;
//	neiborNum = vecEdgePointPart.size();
//	matAllNeibor = new Mat[neiborNum];
//	getNeibor(vecEdgePointPart, matRoiBlur, matAllNeibor, nbsize);
//
//	/*�����ھ��*/
//	/*�����Ե��dx,dy*/
//	vector<Point2i> vecDxdy;
//	//���ڱ�׼��ѧ����
//	calEdgedxdy(matAllNeibor, neiborNum, vecDxdy);
//
//	/*ͨ���ݶȣ�dx��dy��ȷ�������ֵ���򣨱�����*/
//	vector<Point2i> vecResizeXY;
//	calInterTime(vecDxdy, neiborNum, vecResizeXY, VHtime);
//
//	/*��������в�ֵ���Ҽ����Ե����*/
//	Mat* matResizeNeibor;
//	matResizeNeibor = new Mat[neiborNum];
//	resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);
//
//	/*���㵥������ľ��Ա�Ե����*/
//	vector<Vec4d> vecPara;
//	vector<Point2d> subPixelRela;
//	vector<Point2d> subPixelabs;
//	Point2d tempPoint;
//
//	for (int i = 0; i < neiborNum; i++)
//	{
//		calEdgePara(matResizeNeibor[i], vecResizeXY[i], vecPara, subPixelRela, nbsize, ZerBgrL, ZerBgrH);
//		for (int in = 0; in<subPixelRela.size(); in++)
//		{
//			/*�������ת��ͼ����ͼ���ľ�������*/
//			tempPoint.x = (double)vecEdgePointPart[i].y + (subPixelRela[in].x - (nbsize - 1.00) / 2.00);
//			tempPoint.y = (double)vecEdgePointPart[i].x + (subPixelRela[in].y - (nbsize - 1.00) / 2.00);
//            /*�����pixel����*/
//			subPixelabs.push_back(tempPoint);
//		}
//		subPixelRela.clear();
//
//	}
//
//	/*���Բ*/
//	Point2d center;
//	double radius;
//	/*matFitCircle������ʾ��Ͻ��*/
//	//Mat matFitCircle(matRoiBlur.size(), CV_8UC1, Scalar(0));
//
//	CircleInfo(subPixelabs, center, radius);
//	//circle(matFitCircle, Point(round(center.x), round(center.y)), round(radius), Scalar(255));
//    //cv::imshow("Circle fitting result", matRoi);
//
//    Mat edgeCircle(matRoi.size(), CV_8UC1, Scalar(0));
//    circle(edgeCircle, Point(round(center.x), round(center.y)), round(radius), Scalar(255));
//
//
//    std::cout<<"\n-----------------------------------------------------------------------------------------\n";
//    std::cout << "radius fitting: " << radius << "pixel" << endl;
//    std::cout << "Circle centre fitting: " << "(" << center.x << " , " << center.y << ")" << "pixel" << endl;
//    std::cout << "convert accroding to standard  picture [0.01453mm/pixel ]" << endl;
//    std::cout << "real position of circle centre: " << "(" << center.x*rto << " , " << center.y*rto << ")" << "mm" << endl;
//    std::cout << "real position of radius: " << radius*rto << "mm" << endl;
//    std::cout << "deviation: " << radius*rto - 3.000 << "mm" << endl;
//
//	result.radius_mm = radius*rto;
//	result.radius_pixel = radius;
//	result.centerPoint_mm = Point2d(center.x*rto, center.y*rto);
//	result.centerPoint_pixel = Point2d(center.x, center.y);    
//    result.matedge = edgeCircle;
//
//    ResetRect();
//    return result;
//
//}
