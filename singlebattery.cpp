#include "singlebattery.h"

/*
���ƽ���˲�
�������:int imgNumͼ������
���:Mat����ƽ����ͼ��
*/
Mat SingleBattery::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".png", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
	cvtColor(temp, temp, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", temp);//������ƽ���˲����ͼ��
	cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC1);                                       //��ʼ��ƽ��ͼ��Mat����ʽΪCV_32FC
	for (int i = 1; i <= imgNum; i++)                                                                 //���δ�3��ͼƬ
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg", IMREAD_UNCHANGED);//�����i��ͼƬ		                                                       
		accumulate(temp, AverageImage);                                                         //����ʱͼ����ƽ��ͼ�����
	}
	AverageImage /= imgNum;                                                                     //ȡƽ��	
	AverageImage.convertTo(AverageImage, CV_8UC1);                                              //Ϊ��ʾ��Ҫ������ת��Ϊ8UC1
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//������ƽ���˲����ͼ��
	return AverageImage;	
}


Mat SingleBattery::getEdgeVal(Mat srcImg)
{
	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;

	//cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ

	Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);    //��x����ʹ��Sobel()����
	convertScaleAbs(grad_x, abs_grad_x);   //��Ե���ݶȷ���ֱ��������������Ļ��أ���Ե�Ǻ������������ĳһ������ݶ��Ǵ�ֱ��

	           
	Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);	

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, srcImg);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//������ƽ���˲����ͼ��		
	return dstimage;
}

/*
���������߳��н��յĲ����б���ROI
*/
void SingleBattery::createROI(Mat srcImg)
{
	m_rois.reserve(0);//���roi�б�Ϊ����roi��׼��
	//���������б�
	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	{
		roi_parameters *pars = *it;//����ת��
		Mat *RoiImgs = new Mat;//Ϊ�µ�roi�����ڴ�	
		*RoiImgs = srcImg(Rect(pars->x, pars->y, pars->width, pars->height));//����roi
		m_rois.push_back(RoiImgs);//���´�����roi����roi�б�	
	}
}

/*
�ö�ֵ���ķ�����ȡ��Ե
*/
void SingleBattery::edge(Mat Input)
{

	threshold(Input, Input, 170, 255, 3);

}

/*
����һ����
*/
void SingleBattery::MeasureOneBattery()
{
	//Mat src;//����ͼ��	
	//batImg = ImageAverage(1);//���ƽ��
	batImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
	//cout << "channels:" << batImg.channels() << endl;	//��ӡͼ��ͨ����//cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
	createROI(batImg);//����roi	
	
	//print_px_value(IGrad);
	//int i= imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\1(new).jpg", roughEdge);//������ƽ���˲����ͼ��	
	//cout << i << endl;
	//��������roi����
	for (int i = 0; i != m_rois.size(); ++i)
	{
		/*��ôֱ�Եλ��vecEdgePoint*/
		vector<Point2i> vecEdgePoint;
		//vector<Point2i> vecEdgePointPart;//(row,col)
		//getCovPoint(*m_rois[i], vecEdgePoint, 240, 250, 5);
		getRoughEdge(*m_rois[i], vecEdgePoint);
	}


	//for (int i = 0; i != m_rois.size(); ++i)
	//{	
	//	
	//	//��ֵ�˲�
	//	//medianBlur(*m_rois[i], *m_rois[i], 3);

	//	//subpixeltest(*m_rois[i]);
	//	///*��ôֱ�Եλ��vecEdgePoint*/
	//	//vector<Point2i> vecEdgePoint;
	//	//vector<Point2i> vecEdgePointPart;//(row,col)
	//	//getCovPoint(*m_rois[i], vecEdgePoint, 240, 250, 5);



	//	///*��ñ�Ե7*7����matAllNeibor*/
	//	//int neiborNum;//���������
	//	//Mat* matAllNeibor;//�ֱ�Ե���7*7����
	//	//neiborNum = vecEdgePoint.size();
	//	//matAllNeibor = new Mat[neiborNum];		
	//	//getNeibor(vecEdgePoint, *m_rois[i], matAllNeibor, 7);


	//	
	//	
	//	///*�����ھ��*/
	//	///*�����Ե��dx,dy*/
	//	//vector<Point2i> vecDxdy;//�ݶ�
	//	////���ڱ�׼��ѧ����
	//	//calEdgedxdy(matAllNeibor, neiborNum, vecDxdy);

	//	///*ͨ���ݶȣ�dx��dy��ȷ�������ֵ���򣨱�����*/
	//	//vector<Point2i> vecResizeXY;//��ֵ�ı���
	//	////Point2i VHtime = (4,4);
	//	//calInterTime(vecDxdy, neiborNum, vecResizeXY, Point2i(4, 4));

	//	///*��������в�ֵ���Ҽ����Ե����*/
	//	//Mat* matResizeNeibor;//��ֵ��õ�������
	//	//matResizeNeibor = new Mat[neiborNum];
	//	//resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);

	//
	//	

	//	///*���㵥������ľ��Ա�Ե����*/
	//	//vector<Vec4d> vecPara;
	//	//vector<Point2d> subPixelRela;
	//	//vector<Point2d> subPixelabs;
	//	//Point2d tempPoint;

	//	//for (int i = 0; i < neiborNum; i++)
	//	//{
	//	//	calEdgePara(matResizeNeibor[i], vecResizeXY[i], vecPara, subPixelRela, 7, 10, 50);
	//	//	for (int in = 0; in<subPixelRela.size(); in++)
	//	//	{
	//	//		/*�������ת��ͼ����ͼ���ľ�������*/
	//	//		tempPoint.x = (double)vecEdgePointPart[i].y + (subPixelRela[in].x - (7.00 - 1.00) / 2.00);
	//	//		tempPoint.y = (double)vecEdgePointPart[i].x + (subPixelRela[in].y - (7.00 - 1.00) / 2.00);
	//	//		/*�����pixel����*/
	//	//		subPixelabs.push_back(tempPoint);
	//	//	}
	//	//	subPixelRela.clear();
	//	//}
	//	///*ʾ�ⲿ�֣�����pixel����ȡ�������ں�ɫ������*/
	//	//Mat matBlackboard((*m_rois[i]).size(), CV_8UC1, Scalar(0));

	//	//Point center_forshow;
	//	//for (int i = 0; i < subPixelabs.size(); i++)
	//	//{
	//	//	center_forshow.x = cvRound(subPixelabs[i].x);
	//	//	center_forshow.y = cvRound(subPixelabs[i].y);
	//	//	circle(matBlackboard, center_forshow, 0.01, Scalar(255), -1);
	//	//}
	//	//imshow("test", matBlackboard);

	//}
	//getEdgeVal(batImg);
	
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", batImg);//������ƽ���˲����ͼ��	
}


/*��ôֱ�Եλ��vecEdgePoint*/
void SingleBattery::getCovPoint(Mat& matIn, vector<Point2i>& vecEdgePoint, int cannyL, int cannyH, int cannyCore)
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
				//image.at<>(x,y)������õĵ�x��y�Ƿ�������
				pointTemp.x = i;
				pointTemp.y = j;
				vecEdgePoint.push_back(pointTemp);				
			}
		}
	}
	//matCanny.copyTo(matIn);
}


/*
��ñ�Ե7 * 7����
vecEdgePoint:Ҫ����ı�Ե��(y,x)
matIn:�������
matNeibor:������������
nbsize:�����С
*/
void SingleBattery::getNeibor(vector<Point2i>& vecEdgePoint, Mat& matIn, Mat* matNeibor, int nbsize)
{
	Mat matInRoi, matNewRoi;
	int halfN = (nbsize - 1) / 2;
	//�������д���ı�Ե��
	for (int i = 0; i < vecEdgePoint.size(); i++)
	{
		matInRoi = matIn(Rect(vecEdgePoint[i].y, vecEdgePoint[i].x, 1, 1));//������ͼ����ѡȡroi
		matInRoi.adjustROI(halfN, halfN, halfN, halfN);//��roi����Ϊ7*7
		matNeibor[i] = matInRoi;		
	}
}


/*
��ȡ��Ե�ݶ�
matNeibor:�������
neiborNum:Ҫ�������������
vecDxdy:�����������ݶ�
*/
void SingleBattery::calEdgedxdy(Mat* matNeibor, int neiborNum, vector<Point2i>& vecDxdy)
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

double SingleBattery::calRratio(double absdx, double absdy)
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

/*
ͨ���ݶ�(dx,dy)ȷ�������ֵ����(����)
vecDxdy:������ݶ�(dx,dy)
neiborNum:��������
vecResizeXY:����ļ���õ��Ĳ�ֵ�ı���
VHtime:Ԥ���ˮƽ�ʹ�ֱ�����ֵ�ı���
*/
void SingleBattery::calInterTime(vector<Point2i>& vecDxdy, int neiborNum, vector<Point2i>& vecResizeXY, Point2i VHtime)
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

/*
��������в�ֵ
matNeibor:����Ĵ���ֵ����
matResizeNeibor:����Ĳ�ֵ�������
vecResizeXY:����Ĳ�ֵ�ı���
neiborNum:��������
*/
void SingleBattery::resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum)
{
	for (int i = 0; i < neiborNum; i++)
	{
		resize(matNeibor[i], matResizeNeibor[i], Size(7 * vecResizeXY[i].x, 7 * vecResizeXY[i].y));		
	}
}

//�����Ե���� L,K
void SingleBattery::calEdgePara(Mat& matSingleResizeNeibor, Point2i resizeXY, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize, int ZerBgrL, int ZerBgrH)
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
	print_px_value(mZerImageM00);
	filter2D(matSingleResizeNeibor, mZerImageM11R, CV_64F, ZERPOLY11R);
	filter2D(matSingleResizeNeibor, mZerImageM11I, CV_64F, ZERPOLY11I);
	filter2D(matSingleResizeNeibor, mZerImageM20, CV_64F, ZERPOLY20);
	print_px_value(mZerImageM20);
	filter2D(matSingleResizeNeibor, mZerImageM31R, CV_64F, ZERPOLY31R);
	filter2D(matSingleResizeNeibor, mZerImageM31I, CV_64F, ZERPOLY31I);
	filter2D(matSingleResizeNeibor, mZerImageM40, CV_64F, ZERPOLY40);
	print_px_value(mZerImageM40);
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
			cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
			cout << " " << endl;
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


void subpixeltest(Mat OriginalImage)
{
	const int g_N = 7;

	Mat M00 = (Mat_<double>(7, 7) <<

		0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0,

		0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,

		0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,

		0.0807, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0807,

		0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,

		0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,

		0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0);



	Mat M11R = (Mat_<double>(7, 7) <<

		0, -0.015, -0.019, 0, 0.019, 0.015, 0,

		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,

		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,

		-0.069, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.069,

		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,

		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,

		0, -0.015, -0.019, 0, 0.019, 0.015, 0);



	Mat M11I = (Mat_<double>(7, 7) <<

		0, -0.0224, -0.0573, -0.069, -0.0573, -0.0224, 0,

		-0.015, -0.0466, -0.0466, -0.0466, -0.0466, -0.0466, -0.015,

		-0.019, -0.0233, -0.0233, -0.0233, -0.0233, -0.0233, -0.019,

		0, 0, 0, 0, 0, 0, 0,

		0.019, 0.0233, 0.0233, 0.0233, 0.0233, 0.0233, 0.019,

		0.015, 0.0466, 0.0466, 0.0466, 0.0466, 0.0466, 0.015,

		0, 0.0224, 0.0573, 0.069, 0.0573, 0.0224, 0);



	Mat M20 = (Mat_<double>(7, 7) <<

		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0,

		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,

		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,

		0.0396, -0.0261, -0.0661, -0.0794, -0.0661, -0.0261, 0.0396,

		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,

		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,

		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0);



	Mat M31R = (Mat_<double>(7, 7) <<

		0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0,

		-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,

		-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,

		-0.0190, 0.0438, 0.0390, 0, -0.0390, -0.0438, 0.0190,

		-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,

		-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,

		0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0);



	Mat M31I = (Mat_<double>(7, 7) <<

		0, -0.0153, -0.0223, -0.019, -0.0223, -0.0153, 0,

		-0.0103, -0.0018, 0.0324, 0.0438, 0.0324, -0.0018, -0.0103,

		-0.0073, 0.0162, 0.0333, 0.039, 0.0333, 0.0162, -0.0073,

		0, 0, 0, 0, 0, 0, 0,

		0.0073, -0.0162, -0.0333, -0.039, -0.0333, -0.0162, 0.0073,

		0.0103, 0.0018, -0.0324, -0.0438, -0.0324, 0.0018, 0.0103,

		0, 0.0153, 0.0223, 0.0190, 0.0223, 0.0153, 0);



	Mat M40 = (Mat_<double>(7, 7) <<

		0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0,

		0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,

		0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,

		-0.0018, -0.0239, 0.0406, 0.0751, 0.0406, -0.0239, -0.0018,

		0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,

		0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,

		0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0);

	Mat NewSmoothImage;

	medianBlur(OriginalImage, NewSmoothImage, 13);



	//Mat NewAdaThresImage;
	Mat NewAdaThresImage = NewSmoothImage;

	//adaptiveThreshold(NewSmoothImage, NewAdaThresImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 7, 4);


	
	vector<Point2d> SubEdgePoints;



	Mat ZerImageM00;

	filter2D(NewAdaThresImage, ZerImageM00, CV_64F, M00, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D( cannyImage, zerImageM00, CV_64F, M00, Point(-1,-1), 0, BORDER_DEFAULT);



	Mat ZerImageM11R;

	filter2D(NewAdaThresImage, ZerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D( cannyImage, zerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);



	Mat ZerImageM11I;

	filter2D(NewAdaThresImage, ZerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D( cannyImage, zerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);



	Mat ZerImageM20;

	filter2D(NewAdaThresImage, ZerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D( cannyImage, zerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);



	Mat ZerImageM31R;

	filter2D(NewAdaThresImage, ZerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D(cannyImage, zerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);



	Mat ZerImageM31I;

	filter2D(NewAdaThresImage, ZerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D(cannyImage, zerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);



	Mat ZerImageM40;

	filter2D(NewAdaThresImage, ZerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);

	//////////filter2D(cannyImage, zerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);







	int row_number = NewAdaThresImage.rows;

	int col_number = NewAdaThresImage.cols;

	//ʹ��7����7*7��Zernikeģ�壨�䱾���Ǹ�����M00��M11R��M11I��M20��M31R��M31I��M40���ֱ���ͼ����о�����õ�ÿ�����ص���߸�Zernike��Z00��Z11R��Z11I��Z20��Z31R��Z31I��Z40

	//����ÿ���㣬���������߸�Zernike�أ���þ������l�ͻҶȲ����k����l��k�������趨������ʱ�����ж��õ�Ϊ��Ե�㣬����һ����������7��Zernike������õ�������ؼ�����

	//���l��k�������趨����������õ㲻�Ǳ�Ե�㣬ת����һ�������������l�ͻҶȲ����k

	for (int i = 0; i < row_number; i++)

	{

		for (int j = 0; j <col_number; j++)

		{

			if (ZerImageM00.at<double>(i, j) == 0)

			{

				continue;

			}



			//compute theta

			//vector<vector<double> > theta2(0);

			double theta_temporary = atan2(ZerImageM31I.at<double>(i, j), ZerImageM31R.at<double>(i, j));

			//theta2[i].push_back(thetaTem);



			//compute Z11'/Z31'

			double rotated_z11 = 0.0;

			rotated_z11 = sin(theta_temporary)*(ZerImageM11I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM11R.at<double>(i, j));

			double rotated_z31 = 0.0;

			rotated_z31 = sin(theta_temporary)*(ZerImageM31I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM31R.at<double>(i, j));



			//compute l

			double l_method1 = sqrt((5 * ZerImageM40.at<double>(i, j) + 3 * ZerImageM20.at<double>(i, j)) / (8 * ZerImageM20.at<double>(i, j)));

			double l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));

			double l = (l_method1 + l_method2) / 2;

			//compute k/h

			double k, h;



			k = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);

			h = (ZerImageM00.at<double>(i, j) - k*PI / 2 + k*asin(l_method2) + k*l_method2*sqrt(1 - l_method2*l_method2)) / PI;



			//judge the edge

			double k_value = 20.0;



			double l_value = sqrt(2) / g_N;



			double absl = abs(l_method2 - l_method1);

			if (k >= k_value && absl <= l_value)

			{

				Point2d point_temporary;

				point_temporary.x = j + g_N*l*cos(theta_temporary) / 2;

				point_temporary.y = i + g_N*l*sin(theta_temporary) / 2;

				SubEdgePoints.push_back(point_temporary);

			}

			else

			{

				continue;

			}

		}

	}

	//��ʾ����⵽�������ر�Ե

	for (size_t i = 0; i < SubEdgePoints.size(); i++)

	{

		Point center_forshow(cvRound(SubEdgePoints[i].x), cvRound(SubEdgePoints[i].y));

		circle(OriginalImage, center_forshow, 1, 255, 1, 8, 0);

	}
	/*int i = 0;*/
	imshow("�����ر�Ե", OriginalImage);
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\�����ر�Ե.jpg" , OriginalImage);//������ƽ���˲����ͼ��	

	waitKey(0);
}


/*
��̬ѧ��Ե��ȡ
input:����ͼ��
output:���ͼ��
element:ģ��
*/
void  SingleBattery::getIGrad(Mat& input, Mat& output, Mat &element)
{
	//IGrad(f) = (f open g)	dilate g - (f close g) erode g

	Mat erode_ouput, dilate_output, open_output, close_output;

	morphologyEx(input, open_output, MORPH_OPEN, element);//������
	morphologyEx(input, close_output, MORPH_CLOSE, element);//�ղ���

	dilate(open_output, dilate_output, element); //���Ϳ��������ͼ��
	erode(close_output, erode_ouput, element); //��ʴ�ղ������ͼ��

	absdiff(dilate_output, erode_ouput, output);
}



/*
��̬ѧ��Ե��ȡ
input:����ͼ��
vecEdgePoint:��¼�ı�Ե��
*/
void SingleBattery::getRoughEdge(Mat& input, vector<Point2i>& vecEdgePoint)
{	
	// �����Զ���ṹԪ��
	Mat element_1 = (Mat_<uchar>(3, 3) <<   //ʮ�ֽṹԪ��
		0, 1, 0,
		1, 1, 1,
		0, 1, 0);	

	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x�νṹԪ��
		1, 0,  1,
		0, -1, 0,
		1, 0,  1);
	
	Mat output_1, output_2;

	getIGrad(input,output_1,element_1);
	getIGrad(input, output_2, element_2);

	Mat output;
	addWeighted(output_1, 0.5, output_2, 0.5, 0, output);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��

	
	convertScaleAbs(output, output, 3.0, 10);	//ͼ����ǿ
	threshold(output, output, 130, 255, THRESH_BINARY); //��ֵ��

	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", output);//������ƽ���˲����ͼ��	

	Point2i  pointTemp;
	for (int i = 0; i < output.rows; i++)
	{
		for (int j = 0; j < output.cols; j++)
		{
			if (output.at<uchar>(i, j) == 255)
			{
				//image.at<>(x,y)������õĵ�x��y�Ƿ�������
				pointTemp.x = i;
				pointTemp.y = j;
				vecEdgePoint.push_back(pointTemp);
			}
		}
	}
}




//��ӡmat�����е�����ֵ��������
void SingleBattery::print_px_value(Mat& im)
{
	int rowNumber = im.rows;  //����
	int colNumber = im.cols * im.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���

	 //˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i++)  //��ѭ��
	{
		int* data = im.ptr<int>(i);  //��ȡ��i�е��׵�ַ
		for (int j = 0; j < colNumber; j++)   //��ѭ��
		{
			//data[j] = data[j] / div * div + div / 2;
			cout << (int)data[j]<<" " ;
		}  //�д������
		cout << endl;
	}
	cout <<""<< endl;
}

