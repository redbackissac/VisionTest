#include "singlebattery.h"

/*
������в�������Ĳ���
*/
void SingleBattery::getObjs()
{
	openImg(srcImg);//��ͼ��
	createROI(srcImg, vec_rois);//����roi
	/*for (auto it_roi : vec_rois)
	{
		imshow("rois", it_roi);
		waitKey(0);
	}*/


	//ֻ����ʽ����roi
	for (auto it_roi : vec_rois)
	{
		/*��ôֱ�Եλ��vecEdgePoint*/
		vector<Point2i> vecEdgePoint;//�ֱ�Ե����		
		getRoughEdge_All(it_roi, vecEdgePoint);//��ȡ���Ա�Ե����

		/*�����ֱ�Ե�����չ7*7����*/
		int neiborNum;//���������������Ե�������
		Mat AllNeibor;//�ֱ�Ե���7*7����
		//neiborNum = vecEdgePoint.size();

		getNeiborROI(vecEdgePoint, it_roi, AllNeibor);

		/*�����ؾ�ȷ��Եλ��*/
		vector<Vec4d> vecPara;
		vector<Point2d> VecSubPixelEdgePoint;
		getSubPixEdge(AllNeibor, vecPara, VecSubPixelEdgePoint);

		/*ֱ�����*/
		Vec4f line_para;//��ϳ�ֱ�ߵĲ���
		fitLine(VecSubPixelEdgePoint, line_para, DIST_HUBER, 0, 0.000001, 0.000001);	

		/*��ӵ���������*/
		ObjectOfMission objtmp;
		objtmp.VecEdgePoint = VecSubPixelEdgePoint;//ʵ�ʱ�Ե��
		Vec3f line_tmp;
		changeLine2std(line_para, line_tmp);
		objtmp.line_stds = line_tmp;//��ϵ�ֱ��
		vecObj.push_back(objtmp);
	}
	double Straightness;//ֱ�߶�
	cal_Straightness(vecObj[0], Straightness);

	int aaa = 000;
}

/*
ִ�����е�����
*/
void SingleBattery::doMissions()
{
	//��������
	for(auto it_mission: vecMissions)
		switch (it_mission.type)
		{
		case NONE:
			break;
		case STRAIGHTNESS:			
			cal_Straightness(vecObj[it_mission.vec_object[0]],it_mission.result);
			break;
		case PERPENDICULARITY:
			break;
		case PARALLELISM:
			break;
		case DISTANCE:
			break;

		}
}


/*
ֱ�߶ȼ���
vecPoints:�������
straightness:������,ֱ�߶�
n:ȡn�������
*/
void SingleBattery::cal_Straightness(const ObjectOfMission obj, double &straightness,int n)
{
	//�㵽ֱ�߾���:��ֱ�� L �ķ���ΪAx + By + C = 0���� P ������Ϊ��X0��Y0������� P ��ֱ�� L �ľ���Ϊ : | AX0 + BY0 + C | / sqrt(A ^ 2 + B ^ 2)
	vector<Point2d> vecPoints_tmp(obj.VecEdgePoint);//����һ�ݱ�Ե��
	Vec3f line_std(obj.line_stds);//����һ����ϳ���ֱ�߲���
	vector<double>vecDis;//���е㵽��ϳ���ֱ�ߵľ���
	int a = 0, b = 1, c = 2;
	const double Den = sqrt(line_std[a] * line_std[a] + line_std[b] * line_std[b]);//�������ʱ�ķ�ĸ
	for (auto it_Ptmp : vecPoints_tmp)
	{
		double dis;//�����㵽��ϳ���ֱ�ߵľ���	
		dis = (line_std[a] * it_Ptmp.x + line_std[b] * it_Ptmp.y + line_std[c])/Den;//Ϊ���ֵ��λ�ã�����������
		vecDis.push_back(dis);
	}
	sort(vecDis.begin(), vecDis.end());//Ĭ�ϴ�С��������
	/*���㵽ֱ�ߵ�������С����*/
	double a_max = 0,b_min = 0;
	const size_t sizeOfDis= vecDis.size();
	for (int i = 0; i < n; i++)//ȡn����ȡƽ��
	{
		a_max += vecDis[i];//������
		b_min += vecDis[sizeOfDis - 1 - i];//��С����
	}
	a_max /= n;//ȡƽ��
	b_min /= n;//ȡƽ��

	/*�õ�ֱ�߶�*/
	straightness = a_max - b_min;
}








//
///*
//���ƽ���˲�
//�������:int imgNumͼ������
//���:Mat����ƽ����ͼ��
//*/
//Mat SingleBattery::ImageAverage(int imgNum)
//{
//	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".png", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
//	cvtColor(temp, temp, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", temp);//������ƽ���˲����ͼ��
//	cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
//	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC1);                                       //��ʼ��ƽ��ͼ��Mat����ʽΪCV_32FC
//	for (int i = 1; i <= imgNum; i++)                                                                 //���δ�3��ͼƬ
//	{
//		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg", IMREAD_UNCHANGED);//�����i��ͼƬ		                                                       
//		accumulate(temp, AverageImage);                                                         //����ʱͼ����ƽ��ͼ�����
//	}
//	AverageImage /= imgNum;                                                                     //ȡƽ��	
//	AverageImage.convertTo(AverageImage, CV_8UC1);                                              //Ϊ��ʾ��Ҫ������ת��Ϊ8UC1
//	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//������ƽ���˲����ͼ��
//	return AverageImage;	
//}
//
//
//Mat SingleBattery::getEdgeVal(Mat srcImg)
//{
//	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
//
//	//cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ
//
//	Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);    //��x����ʹ��Sobel()����
//	convertScaleAbs(grad_x, abs_grad_x);   //��Ե���ݶȷ���ֱ��������������Ļ��أ���Ե�Ǻ������������ĳһ������ݶ��Ǵ�ֱ��
//
//	           
//	Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
//	convertScaleAbs(grad_y, abs_grad_y);	
//
//	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, srcImg);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
//	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//������ƽ���˲����ͼ��		
//	return dstimage;
//}
//
///*
//���������߳��н��յĲ����б���ROI
//*/
//void SingleBattery::createROI(Mat srcImg)
//{
//	m_rois.reserve(0);//���roi�б�Ϊ����roi��׼��
//	//���������б�
//	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
//	{
//		roi_parameters *pars = *it;//����ת��
//		Mat *RoiImgs = new Mat;//Ϊ�µ�roi�����ڴ�	
//		*RoiImgs = srcImg(Rect(pars->x, pars->y, pars->width, pars->height));//����roi
//		m_rois.push_back(RoiImgs);//���´�����roi����roi�б�	
//	}
//}
//
///*
//�ö�ֵ���ķ�����ȡ��Ե
//*/
//void SingleBattery::edge(Mat Input)
//{
//
//	threshold(Input, Input, 170, 255, 3);
//
//}
//
///*
//����һ����
//*/
//void SingleBattery::getObjs()
//{
//	//Mat src;//����ͼ��	
//	//batImg = ImageAverage(1);//���ƽ��
//	batImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
//	cout << "channels:" << batImg.channels() << endl;	//��ӡͼ��ͨ����//cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
//	createROI(batImg);//����roi	
//	//subpixeltest(batImg);
//	//print_px_value(IGrad);
//	//int i= imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\1(new).jpg", roughEdge);//������ƽ���˲����ͼ��	
//	//cout << i << endl;
//	//��������roi����
//	for (int i = 0; i != m_rois.size(); ++i)
//	{
//		/*��ôֱ�Եλ��vecEdgePoint*/
//		vector<Point2i> vecEdgePoint;//�ֱ�Ե����		
//		getRoughEdge(*m_rois[i], vecEdgePoint);//��ȡ���Ա�Ե����
//
//		/*�����ֱ�Ե���7*7����*/		
//		int neiborNum;//���������������Ե�������
//		Mat AllNeibor;//�ֱ�Ե���7*7����
//		neiborNum = vecEdgePoint.size();
//		//AllNeibor = new Mat[neiborNum];		
//		//getNeibor(vecEdgePoint, *m_rois[i], AllNeibor);
//		getNewROI(vecEdgePoint, *m_rois[i], AllNeibor);
//
//		///*��������в�ֵ���Ҽ����Ե����*/
//		//Mat* matResizeNeibor;//��ֵ��õ�������
//		//matResizeNeibor = new Mat[neiborNum];
//		//resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);
//		
//
//		/*�����ؾ�ȷ��Եλ��*/
//		vector<Vec4d> vecPara;
//		vector<Point2d> subPixelRela;
//		m_calEdgePara(AllNeibor, vecPara, subPixelRela);	
//		//subpixeltest(AllNeibor);
//
//
//		/*ֱ�����*/
//		Vec4f line_para;//��ϳ�ֱ�ߵĲ���
//		fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
//		int j = INT_MAX;
//	}
//	
//
//}
//
//
///*��ôֱ�Եλ��vecEdgePoint*/
//void SingleBattery::getCovPoint(Mat& matIn, vector<Point2i>& vecEdgePoint, int cannyL, int cannyH, int cannyCore)
//{
//	Point2i  pointTemp;
//	Mat matCanny;
//	Canny(matIn, matCanny, cannyL, cannyH, cannyCore);
//	for (int i = 0; i < matCanny.rows; i++)
//	{
//		for (int j = 0; j < matCanny.cols; j++)
//		{
//			if (matCanny.at<uchar>(i, j) == 255)
//			{
//				//image.at<>(x,y)������õĵ�x��y�Ƿ�������
//				pointTemp.x = i;
//				pointTemp.y = j;
//				vecEdgePoint.push_back(pointTemp);				
//			}
//		}
//	}
//	//matCanny.copyTo(matIn);
//}
//
//
///*
//��ñ�Ե7 * 7����
//EdgePoint:Ҫ����ı�Ե��(y,x)
//matIn:�������
//matNeibor:������������
//nbsize:�����С
//*/
//void SingleBattery::getNeibor(vector<Point2i>& EdgePoint, Mat& matIn, Mat* matNeibor, int nbsize)
//{
//	Mat matInRoi, matNewRoi;
//	int halfN = (nbsize - 1) / 2;
//	//�������д���ı�Ե��
//	for (int i = 0; i < EdgePoint.size(); i++)
//	{
//		matInRoi = matIn(Rect(EdgePoint[i].y, EdgePoint[i].x, 1, 1));//������ͼ����ѡȡroi
//		matInRoi.adjustROI(halfN, halfN, halfN, halfN);//��roi����Ϊ7*7
//		matNeibor[i] = matInRoi;
//		/*print_px_value(matInRoi);
//		imshow("roi",matInRoi);
//		waitKey(0);*/
//	}
//}
//
//
///*
//��ȡ��Ե�ݶ�
//matNeibor:�������
//neiborNum:Ҫ�������������
//vecDxdy:�����������ݶ�
//*/
//void SingleBattery::calEdgedxdy(Mat* matNeibor, int neiborNum, vector<Point2i>& vecDxdy)
//{
//	Mat matTemp;
//	Point2i dxdy;
//	for (int i = 0; i < neiborNum; i++)
//	{
//		matTemp = matNeibor[i];
//		matTemp.convertTo(matTemp, CV_64FC1);
//		double dx = matTemp.dot(SOBELX);
//		double dy = matTemp.dot(SOBELY);
//		dxdy.x = dx;
//		dxdy.y = dy;
//		vecDxdy.push_back(dxdy);
//	}
//}
//
//double SingleBattery::calRratio(double absdx, double absdy)
//{
//	double ratio;
//	if (absdx>absdy)
//	{
//		ratio = absdy / absdx;
//	}
//	else
//	{
//		ratio = absdx / absdy;
//	}
//	return ratio;
//}
//
///*
//ͨ���ݶ�(dx,dy)ȷ�������ֵ����(����)
//vecDxdy:������ݶ�(dx,dy)
//neiborNum:��������
//vecResizeXY:����ļ���õ��Ĳ�ֵ�ı���
//VHtime:Ԥ���ˮƽ�ʹ�ֱ�����ֵ�ı���
//*/
//void SingleBattery::calInterTime(vector<Point2i>& vecDxdy, int neiborNum, vector<Point2i>& vecResizeXY, Point2i VHtime)
//{
//	Point2i resizeXYtime;
//	int thresholdHori = 200;
//	for (int i = 0; i < neiborNum; i++)
//	{
//		int dx = abs(vecDxdy[i].x);
//		int dy = abs(vecDxdy[i].y);
//		int diff = abs(dx - dy);
//		/*����ˮƽ��Ե�ʹ�ֱ��Ե*/
//		if (diff > thresholdHori)
//		{
//			resizeXYtime.x = VHtime.x;
//			resizeXYtime.y = VHtime.y;
//			vecResizeXY.push_back(resizeXYtime);
//		}
//		/*����������Ե*/
//		else
//		{
//			double ratio = calRratio(dx, dy);
//			resizeXYtime.y = 5;
//
//			if (ceil(5.000 * ratio) != 0)
//			{
//				resizeXYtime.x = ceil(5.000 * ratio);
//			}
//			else
//			{
//				resizeXYtime.x = 1;
//			}
//			vecResizeXY.push_back(resizeXYtime);
//
//		}
//	}
//}
//
///*
//��������в�ֵ
//matNeibor:����Ĵ���ֵ����
//matResizeNeibor:����Ĳ�ֵ�������
//vecResizeXY:����Ĳ�ֵ�ı���
//neiborNum:��������
//*/
//void SingleBattery::resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum)
//{
//	for (int i = 0; i < neiborNum; i++)
//	{
//		resize(matNeibor[i], matResizeNeibor[i], Size(7 * vecResizeXY[i].x, 7 * vecResizeXY[i].y));		
//	}
//}
//
////�����Ե���� L,K
//void SingleBattery::calEdgePara(Mat& matSingleResizeNeibor, Point2i resizeXY, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize, int ZerBgrL, int ZerBgrH)
//{
//
//	Vec4d  para;
//	Point2d point;
//
//	Mat mZerImageM00;
//	Mat mZerImageM11R;
//	Mat mZerImageM11I;
//	Mat mZerImageM20;
//	Mat mZerImageM31R;
//	Mat mZerImageM31I;
//	Mat mZerImageM40;
//
//	//���
//	filter2D(matSingleResizeNeibor, mZerImageM00, CV_64F, ZERPOLY00);
//	//print_px_value(mZerImageM00);
//	filter2D(matSingleResizeNeibor, mZerImageM11R, CV_64F, ZERPOLY11R);
//	filter2D(matSingleResizeNeibor, mZerImageM11I, CV_64F, ZERPOLY11I);
//	filter2D(matSingleResizeNeibor, mZerImageM20, CV_64F, ZERPOLY20);
//	//print_px_value(mZerImageM20);
//	filter2D(matSingleResizeNeibor, mZerImageM31R, CV_64F, ZERPOLY31R);
//	filter2D(matSingleResizeNeibor, mZerImageM31I, CV_64F, ZERPOLY31I);
//	filter2D(matSingleResizeNeibor, mZerImageM40, CV_64F, ZERPOLY40);
//	//print_px_value(mZerImageM40);
//	double rotated_z11 = 0.0;
//	double rotated_z31 = 0.0;
//	double l_method1 = 0.0;
//	double l_method2 = 0.0;
//
//	double l_t1 = sqrt(2) / (2.00 * nbsize);
//	double l_t2 = sqrt(2) / 2.00;
//
//	int row_number = matSingleResizeNeibor.rows;
//	int col_number = matSingleResizeNeibor.cols;
//	//ʹ��7����7*7��Zernikeģ�壨�䱾���Ǹ�����M00��M11R��M11I��M20��M31R��M31I��M40���ֱ���ͼ����о�����õ�ÿ�����ص���߸�Zernike��Z00��Z11R��Z11I��Z20��Z31R��Z31I��Z40
//
//	//����ÿ���㣬���������߸�Zernike�أ���þ������l�ͻҶȲ����k����l��k�������趨������ʱ�����ж��õ�Ϊ��Ե�㣬����һ����������7��Zernike������õ�������ؼ�����
//
//	//���l��k�������趨����������õ㲻�Ǳ�Ե�㣬ת����һ�������������l�ͻҶȲ����k
//	for (int i = 0; i < row_number; i++)
//	{
//		for (int j = 0; j < col_number; j++)
//		{
//			if (mZerImageM00.at<double>(i, j) == 0)
//			{
//				continue;
//			}
//			para[THETA] = atan2(mZerImageM31I.at<double>(i, j), mZerImageM31R.at<double>(i, j));
//
//			//����Z11'��Z31'Ϊ����L1,L2��׼��,rotated_z11=Z11',rotated_z31=Z31'
//
//			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
//			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));
//
//			//����L1��L2,
//			cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
//			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
//			cout << " " << endl;
//			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
//			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
//			para[L] = (l_method1 + l_method2) / 2;
//			//l = l - 0.207107;//��ȥ����ֵk
//
//			//����k��h 
//			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
//			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;
//
//			vecPara.push_back(para);
//			/*��ֵ����*/
//			if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH)
//			{
//				/*��Ե�߶Ȼָ�*/
//				point.x = (j + para[L] * nbsize*cos(para[THETA]) / 2.00) / (double)resizeXY.x;
//				point.y = (i + para[L] * nbsize*sin(para[THETA]) / 2.00) / (double)resizeXY.y;
//				subPixelRela.push_back(point);
//			}
//
//		}
//	}
//}
//
//
//void subpixeltest(Mat OriginalImage)
//{
//	const int g_N = 7;
//
//	Mat M00 = (Mat_<double>(7, 7) <<
//
//		0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0,
//
//		0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
//
//		0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
//
//		0.0807, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0807,
//
//		0.0686, 0.0816, 0.0816, 0.0816, 0.0816, 0.0816, 0.0686,
//
//		0.0287, 0.0815, 0.0816, 0.0816, 0.0816, 0.0815, 0.0287,
//
//		0, 0.0287, 0.0686, 0.0807, 0.0686, 0.0287, 0);
//
//
//
//	Mat M11R = (Mat_<double>(7, 7) <<
//
//		0, -0.015, -0.019, 0, 0.019, 0.015, 0,
//
//		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
//
//		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
//
//		-0.069, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.069,
//
//		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
//
//		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
//
//		0, -0.015, -0.019, 0, 0.019, 0.015, 0);
//
//
//
//	Mat M11I = (Mat_<double>(7, 7) <<
//
//		0, -0.0224, -0.0573, -0.069, -0.0573, -0.0224, 0,
//
//		-0.015, -0.0466, -0.0466, -0.0466, -0.0466, -0.0466, -0.015,
//
//		-0.019, -0.0233, -0.0233, -0.0233, -0.0233, -0.0233, -0.019,
//
//		0, 0, 0, 0, 0, 0, 0,
//
//		0.019, 0.0233, 0.0233, 0.0233, 0.0233, 0.0233, 0.019,
//
//		0.015, 0.0466, 0.0466, 0.0466, 0.0466, 0.0466, 0.015,
//
//		0, 0.0224, 0.0573, 0.069, 0.0573, 0.0224, 0);
//
//
//
//	Mat M20 = (Mat_<double>(7, 7) <<
//
//		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0,
//
//		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
//
//		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
//
//		0.0396, -0.0261, -0.0661, -0.0794, -0.0661, -0.0261, 0.0396,
//
//		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
//
//		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
//
//		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0);
//
//
//
//	Mat M31R = (Mat_<double>(7, 7) <<
//
//		0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0,
//
//		-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
//
//		-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
//
//		-0.0190, 0.0438, 0.0390, 0, -0.0390, -0.0438, 0.0190,
//
//		-0.0223, 0.0324, 0.0333, 0, -0.0333, -0.0324, 0.0223,
//
//		-0.0153, -0.0018, 0.0162, 0, -0.0162, 0.0018, 0.0153,
//
//		0, -0.0103, -0.0073, 0, 0.0073, 0.0103, 0);
//
//
//
//	Mat M31I = (Mat_<double>(7, 7) <<
//
//		0, -0.0153, -0.0223, -0.019, -0.0223, -0.0153, 0,
//
//		-0.0103, -0.0018, 0.0324, 0.0438, 0.0324, -0.0018, -0.0103,
//
//		-0.0073, 0.0162, 0.0333, 0.039, 0.0333, 0.0162, -0.0073,
//
//		0, 0, 0, 0, 0, 0, 0,
//
//		0.0073, -0.0162, -0.0333, -0.039, -0.0333, -0.0162, 0.0073,
//
//		0.0103, 0.0018, -0.0324, -0.0438, -0.0324, 0.0018, 0.0103,
//
//		0, 0.0153, 0.0223, 0.0190, 0.0223, 0.0153, 0);
//
//
//
//	Mat M40 = (Mat_<double>(7, 7) <<
//
//		0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0,
//
//		0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
//
//		0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
//
//		-0.0018, -0.0239, 0.0406, 0.0751, 0.0406, -0.0239, -0.0018,
//
//		0.0056, -0.0323, 0.0125, 0.0406, 0.0125, -0.0323, 0.0056,
//
//		0.0130, -0.0186, -0.0323, -0.0239, -0.0323, -0.0186, 0.0130,
//
//		0, 0.013, 0.0056, -0.0018, 0.0056, 0.013, 0);
//
//	Mat NewSmoothImage;
//
//	medianBlur(OriginalImage, NewSmoothImage, 13);
//
//
//
//	//Mat NewAdaThresImage;
//	Mat NewAdaThresImage = NewSmoothImage;
//
//	//adaptiveThreshold(NewSmoothImage, NewAdaThresImage, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 7, 4);
//
//
//	
//	vector<Point2d> SubEdgePoints;
//
//
//
//	Mat ZerImageM00;
//
//	filter2D(NewAdaThresImage, ZerImageM00, CV_64F, M00, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D( cannyImage, zerImageM00, CV_64F, M00, Point(-1,-1), 0, BORDER_DEFAULT);
//
//
//
//	Mat ZerImageM11R;
//
//	filter2D(NewAdaThresImage, ZerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D( cannyImage, zerImageM11R, CV_64F, M11R, Point(-1, -1), 0, BORDER_DEFAULT);
//
//
//
//	Mat ZerImageM11I;
//
//	filter2D(NewAdaThresImage, ZerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D( cannyImage, zerImageM11I, CV_64F, M11I, Point(-1, -1), 0, BORDER_DEFAULT);
//
//
//
//	Mat ZerImageM20;
//
//	filter2D(NewAdaThresImage, ZerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D( cannyImage, zerImageM20, CV_64F, M20, Point(-1, -1), 0, BORDER_DEFAULT);
//
//
//
//	Mat ZerImageM31R;
//
//	filter2D(NewAdaThresImage, ZerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D(cannyImage, zerImageM31R, CV_64F, M31R, Point(-1, -1), 0, BORDER_DEFAULT);
//
//
//
//	Mat ZerImageM31I;
//
//	filter2D(NewAdaThresImage, ZerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D(cannyImage, zerImageM31I, CV_64F, M31I, Point(-1, -1), 0, BORDER_DEFAULT);
//
//
//
//	Mat ZerImageM40;
//
//	filter2D(NewAdaThresImage, ZerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);
//
//	//////////filter2D(cannyImage, zerImageM40, CV_64F, M40, Point(-1, -1), 0, BORDER_DEFAULT);
//
//
//
//
//
//
//
//	int row_number = NewAdaThresImage.rows;
//
//	int col_number = NewAdaThresImage.cols;
//
//	//ʹ��7����7*7��Zernikeģ�壨�䱾���Ǹ�����M00��M11R��M11I��M20��M31R��M31I��M40���ֱ���ͼ����о�����õ�ÿ�����ص���߸�Zernike��Z00��Z11R��Z11I��Z20��Z31R��Z31I��Z40
//
//	//����ÿ���㣬���������߸�Zernike�أ���þ������l�ͻҶȲ����k����l��k�������趨������ʱ�����ж��õ�Ϊ��Ե�㣬����һ����������7��Zernike������õ�������ؼ�����
//
//	//���l��k�������趨����������õ㲻�Ǳ�Ե�㣬ת����һ�������������l�ͻҶȲ����k
//
//	for (int i = 0; i < row_number; i++)
//
//	{
//
//		for (int j = 0; j <col_number; j++)
//
//		{
//
//			if (ZerImageM00.at<double>(i, j) == 0)
//
//			{
//
//				continue;
//
//			}
//
//
//
//			//compute theta
//
//			//vector<vector<double> > theta2(0);
//
//			double theta_temporary = atan2(ZerImageM31I.at<double>(i, j), ZerImageM31R.at<double>(i, j));
//
//			//theta2[i].push_back(thetaTem);
//
//
//
//			//compute Z11'/Z31'
//
//			double rotated_z11 = 0.0;
//
//			rotated_z11 = sin(theta_temporary)*(ZerImageM11I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM11R.at<double>(i, j));
//
//			double rotated_z31 = 0.0;
//
//			rotated_z31 = sin(theta_temporary)*(ZerImageM31I.at<double>(i, j)) + cos(theta_temporary)*(ZerImageM31R.at<double>(i, j));
//
//
//
//			//compute l
//
//			double l_method1 = sqrt((5 * ZerImageM40.at<double>(i, j) + 3 * ZerImageM20.at<double>(i, j)) / (8 * ZerImageM20.at<double>(i, j)));
//
//			double l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
//
//			double l = (l_method1 + l_method2) / 2;
//
//			//compute k/h
//
//			double k, h;
//
//
//
//			k = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
//
//			h = (ZerImageM00.at<double>(i, j) - k*PI / 2 + k*asin(l_method2) + k*l_method2*sqrt(1 - l_method2*l_method2)) / PI;
//
//
//
//			//judge the edge
//
//			double k_value = 20.0;
//
//
//
//			double l_value = sqrt(2) / g_N;
//
//
//
//			double absl = abs(l_method2 - l_method1);
//
//			//if (k >= k_value && absl <= l_value)
//			if (1)
//			{
//
//				Point2d point_temporary;
//
//				point_temporary.x = j + g_N*l*cos(theta_temporary) / 2;
//
//				point_temporary.y = i + g_N*l*sin(theta_temporary) / 2;
//
//				SubEdgePoints.push_back(point_temporary);
//
//			}
//
//			else
//
//			{
//
//				continue;
//
//			}
//
//		}
//
//	}
//
//	//��ʾ����⵽�������ر�Ե
//
//	for (size_t i = 0; i < SubEdgePoints.size(); i++)
//
//	{
//
//		Point center_forshow(cvRound(SubEdgePoints[i].x), cvRound(SubEdgePoints[i].y));
//
//		circle(OriginalImage, center_forshow, 1, 255, 1, 8, 0);
//
//	}
//	/*int i = 0;*/
//	imshow("�����ر�Ե", OriginalImage);
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\�����ر�Ե.jpg" , OriginalImage);//������ƽ���˲����ͼ��	
//
//	waitKey(0);
//}
//
//
///*
//��̬ѧ��Ե��ȡ
//input:����ͼ��
//output:���ͼ��
//element:ģ��
//*/
//void  SingleBattery::getIGrad(const Mat input, Mat& output, Mat &element)
//{
//	//IGrad(f) = (f open g)	dilate g - (f close g) erode g
//
//	Mat erode_ouput, dilate_output, open_output, close_output;
//
//	morphologyEx(input, open_output, MORPH_OPEN, element);//������
//	morphologyEx(input, close_output, MORPH_CLOSE, element);//�ղ���
//
//	dilate(open_output, dilate_output, element); //���Ϳ��������ͼ��
//	erode(close_output, erode_ouput, element); //��ʴ�ղ������ͼ��
//
//	absdiff(dilate_output, erode_ouput, output);
//}
//
//
//
///*
//��̬ѧ��Ե��ȡ
//input:����ͼ��
//vecEdgePoint:��¼�ı�Ե��
//*/
//void SingleBattery::getRoughEdge(Mat& input, vector<Point2i>& vecEdgePoint)
//{	
//	// �����Զ���ṹԪ��
//	Mat element_1 = (Mat_<uchar>(3, 3) <<   //ʮ�ֽṹԪ��
//		0, 1, 0,
//		1, 1, 1,
//		0, 1, 0);	
//
//	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x�νṹԪ��
//		1, 0,  1,
//		0, -1, 0,
//		1, 0,  1);
//	
//	Mat output_1, output_2;
//
//	getIGrad(input,output_1,element_1);
//	getIGrad(input, output_2, element_2);
//
//	Mat output;
//	addWeighted(output_1, 0.5, output_2, 0.5, 0, output);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
//
//	
//	convertScaleAbs(output, output, 3.0, 10);	//ͼ����ǿ
//	threshold(output, output, 130, 255, THRESH_BINARY); //��ֵ��
//
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", output);//������ƽ���˲����ͼ��	
//	
//    //��¼���дֱ�Ե�������
//	Point2i  pointTemp;
//	for (int i = 0; i < output.rows; i++)
//	{
//		for (int j = 0; j < output.cols; j++)
//		{
//			if (output.at<uchar>(i, j) == 255)
//			{
//				//image.at<>(x,y)������õĵ�x��y�Ƿ�������
//				pointTemp.x = i;
//				pointTemp.y = j;
//				vecEdgePoint.push_back(pointTemp);
//			}
//		}
//	}
//}
//
//
//
//
////��ӡmat�����е�����ֵ��������
//void SingleBattery::print_px_value(Mat& im)
//{
//	int rowNumber = im.rows;  //����
//	int colNumber = im.cols * im.channels();  //���� x ͨ����=ÿһ��Ԫ�صĸ���
//
//	 //˫��ѭ�����������е�����ֵ
//	for (int i = 0; i < rowNumber; i++)  //��ѭ��
//	{
//		uchar* data = im.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
//		for (int j = 0; j < colNumber; j++)   //��ѭ��
//		{
//			//data[j] = data[j] / div * div + div / 2;
//			cout << (int)data[j]<<" " ;
//		}  //�д������
//		cout << endl;
//	}
//	cout <<""<< endl;
//}
//
//
//
//
//void SingleBattery::m_calEdgePara(Mat& matSingleResizeNeibor, vector<Vec4d>& vecPara, vector<Point2d>& subPixelRela, int nbsize, int ZerBgrL, int ZerBgrH)
//{
//
//	Vec4d  para;
//	Point2d point;
//
//	Mat mZerImageM00;
//	Mat mZerImageM11R;
//	Mat mZerImageM11I;
//	Mat mZerImageM20;
//	Mat mZerImageM31R;
//	Mat mZerImageM31I;
//	Mat mZerImageM40;
//
//	//���
//	filter2D(matSingleResizeNeibor, mZerImageM00, CV_64F, ZERPOLY00);
//	filter2D(matSingleResizeNeibor, mZerImageM11R, CV_64F, ZERPOLY11R);
//	filter2D(matSingleResizeNeibor, mZerImageM11I, CV_64F, ZERPOLY11I);
//	filter2D(matSingleResizeNeibor, mZerImageM20, CV_64F, ZERPOLY20);
//	filter2D(matSingleResizeNeibor, mZerImageM31R, CV_64F, ZERPOLY31R);
//	filter2D(matSingleResizeNeibor, mZerImageM31I, CV_64F, ZERPOLY31I);
//	filter2D(matSingleResizeNeibor, mZerImageM40, CV_64F, ZERPOLY40);
//
//	double rotated_z11 = 0.0;
//	double rotated_z31 = 0.0;
//	double l_method1 = 0.0;
//	double l_method2 = 0.0;
//
//	double l_t1 = sqrt(2) / (2.00 * nbsize);
//	double l_t2 = sqrt(2) / 2.00;
//
//	int row_number = matSingleResizeNeibor.rows;
//	int col_number = matSingleResizeNeibor.cols;
//	//ʹ��7����7*7��Zernikeģ�壨�䱾���Ǹ�����M00��M11R��M11I��M20��M31R��M31I��M40���ֱ���ͼ����о�����õ�ÿ�����ص���߸�Zernike��Z00��Z11R��Z11I��Z20��Z31R��Z31I��Z40
//
//	//����ÿ���㣬���������߸�Zernike�أ���þ������l�ͻҶȲ����k����l��k�������趨������ʱ�����ж��õ�Ϊ��Ե�㣬����һ����������7��Zernike������õ�������ؼ�����
//
//	//���l��k�������趨����������õ㲻�Ǳ�Ե�㣬ת����һ�������������l�ͻҶȲ����k
//	for (int i = 0; i < row_number; i++)
//	{
//		for (int j = 0; j < col_number; j++)
//		{
//			if (mZerImageM00.at<double>(i, j) == 0)
//			{
//				continue;
//			}
//			para[THETA] = atan2(mZerImageM31I.at<double>(i, j), mZerImageM31R.at<double>(i, j));
//
//			//����Z11'��Z31'Ϊ����L1,L2��׼��,rotated_z11=Z11',rotated_z31=Z31'
//
//			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
//			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));
//
//			//����L1��L2,
//		/*	cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
//			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
//			cout << " " << endl;*/
//			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
//			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
//			para[L] = (l_method1 + l_method2) / 2;
//			//l = l - 0.207107;//��ȥ����ֵk
//
//			//����k��h 
//			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
//			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;
//
//			vecPara.push_back(para);
//			/*��ֵ����*/
//			//if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH) 
//			if (abs(l_method1 - l_method2) <= (sqrt(2) / (2.00*7.00)) && para[L]<l_t2 && para[K]>ZerBgrL && para[H] <50)
//			//if (1)
//			{
//				/*��Ե�߶Ȼָ�*/
//				point.x = (j + para[L] * nbsize*cos(para[THETA]) / 2.00);
//				point.y = (i + para[L] * nbsize*sin(para[THETA]) / 2.00);
//				subPixelRela.push_back(point);				
//			}
//			else
//			{
//				continue;
//			}
//
//		}
//	}
//
//
//	//��ʾ����⵽�������ر�Ե
//
// //	for (size_t i = 0; i < subPixelRela.size(); i++)
//
//	//{
//
//	//	Point center_forshow(cvRound(subPixelRela[i].x), cvRound(subPixelRela[i].y));
//
//	//	circle(matSingleResizeNeibor, center_forshow, 1, 255, 1, 8, 0);
//
//	//}
//	//int i = 0;
//	//imshow("�����ر�Ե", matSingleResizeNeibor);
//	////imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\�����ر�Ե.jpg", matSingleResizeNeibor);//������ƽ���˲����ͼ��	
//
//	//waitKey(0);
//}
//
//
//
///*
//��ñ�Ե7 * 7����
//EdgePoint:Ҫ����ı�Ե��(y,x)
//matIn:�������
//matNeibor:������������
//nbsize:�����С
//*/
//void SingleBattery::getNewROI(vector<Point2i>& EdgePoint, Mat& matIn, Mat& matNeibor, int nbsize)
//{
//	Mat matInRoi, matNewRoi;
//	int halfN = (nbsize - 1) / 2;
//	int x_MAX = 0;
//	int x_MIN = INT_MAX;
//	int y_MAX = 0;
//	int y_MIN = INT_MAX;
//	//�������д���ı�Ե��
//	for (int i = 0; i < EdgePoint.size(); i++)
//	{
//		if (x_MAX < EdgePoint[i].x) x_MAX = EdgePoint[i].x;
//		if (x_MIN > EdgePoint[i].x) x_MIN = EdgePoint[i].x;
//		if (y_MAX < EdgePoint[i].y) y_MAX = EdgePoint[i].y;
//		if (y_MIN > EdgePoint[i].y) y_MIN = EdgePoint[i].y;
//		//matInRoi = matIn(Rect(EdgePoint[i].y, EdgePoint[i].x, 1, 1));//������ͼ����ѡȡroi
//		//matInRoi.adjustROI(halfN, halfN, halfN, halfN);//��roi����Ϊ7*7
//		//matNeibor[i] = matInRoi;
//		/*print_px_value(matInRoi);
//		imshow("roi",matInRoi);
//		waitKey(0);*/
//	}
//	matInRoi = matIn(Range(x_MIN, x_MAX),Range(y_MIN, y_MAX));//������ͼ����ѡȡroi
//	matInRoi.adjustROI(halfN, halfN, halfN, halfN);//��roi����Ϊ7*7
//	matNeibor = matInRoi;
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\�����ر�Ե.jpg", matInRoi);//������ƽ���˲����ͼ��	
//	/*imshow("roi",matNeibor);
//	waitKey(0);*/
//}