#include "singlebattery.h"

/*
获得所有测量对象的参数
*/
void SingleBattery::getObjs()
{
	openImg(srcImg);//打开图像
	createROI(srcImg, vec_rois);//创建roi
	/*for (auto it_roi : vec_rois)
	{
		imshow("rois", it_roi);
		waitKey(0);
	}*/


	//只读方式遍历roi
	for (auto it_roi : vec_rois)
	{
		/*获得粗边缘位置vecEdgePoint*/
		vector<Point2i> vecEdgePoint;//粗边缘坐标		
		getRoughEdge_All(it_roi, vecEdgePoint);//提取粗略边缘坐标

		/*创建粗边缘点的扩展7*7邻域*/
		int neiborNum;//邻域的数量，即边缘点的数量
		Mat AllNeibor;//粗边缘点的7*7邻域
		//neiborNum = vecEdgePoint.size();

		getNeiborROI(vecEdgePoint, it_roi, AllNeibor);

		/*亚像素精确边缘位置*/
		vector<Vec4d> vecPara;
		vector<Point2d> VecSubPixelEdgePoint;
		getSubPixEdge(AllNeibor, vecPara, VecSubPixelEdgePoint);

		/*直线拟合*/
		Vec4f line_para;//拟合出直线的参数
		fitLine(VecSubPixelEdgePoint, line_para, DIST_HUBER, 0, 0.000001, 0.000001);	

		/*添加到对象向量*/
		ObjectOfMission objtmp;
		objtmp.VecEdgePoint = VecSubPixelEdgePoint;//实际边缘点
		Vec3f line_tmp;
		changeLine2std(line_para, line_tmp);
		objtmp.line_stds = line_tmp;//拟合的直线
		vecObj.push_back(objtmp);
	}
	double Straightness;//直线度
	cal_Straightness(vecObj[0], Straightness);

	int aaa = 000;
}

/*
执行所有的任务
*/
void SingleBattery::doMissions()
{
	//遍历任务
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
直线度计算
vecPoints:被测对象
straightness:计算结果,直线度
n:取n个点计算
*/
void SingleBattery::cal_Straightness(const ObjectOfMission obj, double &straightness,int n)
{
	//点到直线距离:设直线 L 的方程为Ax + By + C = 0，点 P 的坐标为（X0，Y0），则点 P 到直线 L 的距离为 : | AX0 + BY0 + C | / sqrt(A ^ 2 + B ^ 2)
	vector<Point2d> vecPoints_tmp(obj.VecEdgePoint);//复制一份边缘点
	Vec3f line_std(obj.line_stds);//复制一份拟合出的直线参数
	vector<double>vecDis;//所有点到拟合出的直线的距离
	int a = 0, b = 1, c = 2;
	const double Den = sqrt(line_std[a] * line_std[a] + line_std[b] * line_std[b]);//计算距离时的分母
	for (auto it_Ptmp : vecPoints_tmp)
	{
		double dis;//各个点到拟合出的直线的距离	
		dis = (line_std[a] * it_Ptmp.x + line_std[b] * it_Ptmp.y + line_std[c])/Den;//为区分点的位置，距离有正负
		vecDis.push_back(dis);
	}
	sort(vecDis.begin(), vecDis.end());//默认从小到大排序
	/*计算到直线的最大和最小距离*/
	double a_max = 0,b_min = 0;
	const size_t sizeOfDis= vecDis.size();
	for (int i = 0; i < n; i++)//取n个点取平均
	{
		a_max += vecDis[i];//最大距离
		b_min += vecDis[sizeOfDis - 1 - i];//最小距离
	}
	a_max /= n;//取平均
	b_min /= n;//取平均

	/*得到直线度*/
	straightness = a_max - b_min;
}








//
///*
//多幅平均滤波
//输入参数:int imgNum图像张数
//输出:Mat类型平均后图像
//*/
//Mat SingleBattery::ImageAverage(int imgNum)
//{
//	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".png", IMREAD_UNCHANGED);//读取图像，不改变通道数
//	cvtColor(temp, temp, COLOR_RGB2GRAY);   //转变为灰度图
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", temp);//保存多幅平均滤波后的图像
//	cout << "channels:" << temp.channels() << endl;	//打印图像通道数
//	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC1);                                       //初始化平均图像Mat，格式为CV_32FC
//	for (int i = 1; i <= imgNum; i++)                                                                 //依次打开3张图片
//	{
//		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg", IMREAD_UNCHANGED);//载入第i张图片		                                                       
//		accumulate(temp, AverageImage);                                                         //将临时图像与平均图像相加
//	}
//	AverageImage /= imgNum;                                                                     //取平均	
//	AverageImage.convertTo(AverageImage, CV_8UC1);                                              //为显示需要将数据转换为8UC1
//	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//保存多幅平均滤波后的图像
//	return AverageImage;	
//}
//
//
//Mat SingleBattery::getEdgeVal(Mat srcImg)
//{
//	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
//
//	//cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //转变为灰度图
//
//	Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);    //对x方向使用Sobel()函数
//	convertScaleAbs(grad_x, abs_grad_x);   //边缘与梯度方向垂直，所以输出出来的话呢，边缘是和我们所计算的某一方向的梯度是垂直的
//
//	           
//	Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);
//	convertScaleAbs(grad_y, abs_grad_y);	
//
//	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, srcImg);    //图像的线性混合，每张图0.5的权重
//	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//保存多幅平均滤波后的图像		
//	return dstimage;
//}
//
///*
//根据在子线程中接收的参数列表创建ROI
//*/
//void SingleBattery::createROI(Mat srcImg)
//{
//	m_rois.reserve(0);//清空roi列表，为创建roi做准备
//	//遍历参数列表
//	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
//	{
//		roi_parameters *pars = *it;//类型转换
//		Mat *RoiImgs = new Mat;//为新的roi开辟内存	
//		*RoiImgs = srcImg(Rect(pars->x, pars->y, pars->width, pars->height));//创建roi
//		m_rois.push_back(RoiImgs);//将新创建的roi加入roi列表	
//	}
//}
//
///*
//用二值化的方法提取边缘
//*/
//void SingleBattery::edge(Mat Input)
//{
//
//	threshold(Input, Input, 170, 255, 3);
//
//}
//
///*
//测量一块电池
//*/
//void SingleBattery::getObjs()
//{
//	//Mat src;//输入图像	
//	//batImg = ImageAverage(1);//多幅平均
//	batImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数
//	cout << "channels:" << batImg.channels() << endl;	//打印图像通道数//cout << "channels:" << temp.channels() << endl;	//打印图像通道数
//	createROI(batImg);//创建roi	
//	//subpixeltest(batImg);
//	//print_px_value(IGrad);
//	//int i= imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\1(new).jpg", roughEdge);//保存多幅平均滤波后的图像	
//	//cout << i << endl;
//	//遍历所有roi区域
//	for (int i = 0; i != m_rois.size(); ++i)
//	{
//		/*获得粗边缘位置vecEdgePoint*/
//		vector<Point2i> vecEdgePoint;//粗边缘坐标		
//		getRoughEdge(*m_rois[i], vecEdgePoint);//提取粗略边缘坐标
//
//		/*创建粗边缘点的7*7邻域*/		
//		int neiborNum;//邻域的数量，即边缘点的数量
//		Mat AllNeibor;//粗边缘点的7*7邻域
//		neiborNum = vecEdgePoint.size();
//		//AllNeibor = new Mat[neiborNum];		
//		//getNeibor(vecEdgePoint, *m_rois[i], AllNeibor);
//		getNewROI(vecEdgePoint, *m_rois[i], AllNeibor);
//
//		///*对邻域进行插值并且计算边缘参数*/
//		//Mat* matResizeNeibor;//插值后得到的邻域
//		//matResizeNeibor = new Mat[neiborNum];
//		//resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);
//		
//
//		/*亚像素精确边缘位置*/
//		vector<Vec4d> vecPara;
//		vector<Point2d> subPixelRela;
//		m_calEdgePara(AllNeibor, vecPara, subPixelRela);	
//		//subpixeltest(AllNeibor);
//
//
//		/*直线拟合*/
//		Vec4f line_para;//拟合出直线的参数
//		fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
//		int j = INT_MAX;
//	}
//	
//
//}
//
//
///*获得粗边缘位置vecEdgePoint*/
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
//				//image.at<>(x,y)方法获得的点x和y是反过来的
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
//获得边缘7 * 7邻域
//EdgePoint:要处理的边缘点(y,x)
//matIn:输入矩阵
//matNeibor:输出的邻域矩阵
//nbsize:邻域大小
//*/
//void SingleBattery::getNeibor(vector<Point2i>& EdgePoint, Mat& matIn, Mat* matNeibor, int nbsize)
//{
//	Mat matInRoi, matNewRoi;
//	int halfN = (nbsize - 1) / 2;
//	//遍历所有储存的边缘点
//	for (int i = 0; i < EdgePoint.size(); i++)
//	{
//		matInRoi = matIn(Rect(EdgePoint[i].y, EdgePoint[i].x, 1, 1));//在输入图像上选取roi
//		matInRoi.adjustROI(halfN, halfN, halfN, halfN);//将roi调整为7*7
//		matNeibor[i] = matInRoi;
//		/*print_px_value(matInRoi);
//		imshow("roi",matInRoi);
//		waitKey(0);*/
//	}
//}
//
//
///*
//获取边缘梯度
//matNeibor:输入矩阵
//neiborNum:要处理的邻域数量
//vecDxdy:计算后输出的梯度
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
//通过梯度(dx,dy)确定邻域插值方向(比例)
//vecDxdy:输入的梯度(dx,dy)
//neiborNum:邻域数量
//vecResizeXY:输出的计算得到的插值的比例
//VHtime:预设的水平和垂直方向插值的比例
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
//		/*处理水平边缘和垂直边缘*/
//		if (diff > thresholdHori)
//		{
//			resizeXYtime.x = VHtime.x;
//			resizeXYtime.y = VHtime.y;
//			vecResizeXY.push_back(resizeXYtime);
//		}
//		/*处理其他边缘*/
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
//对邻域进行插值
//matNeibor:输入的待插值邻域
//matResizeNeibor:输出的插值后的邻域
//vecResizeXY:输入的插值的比例
//neiborNum:邻域数量
//*/
//void SingleBattery::resizeNeibor(Mat* matNeibor, Mat* matResizeNeibor, vector<Point2i>& vecResizeXY, int neiborNum)
//{
//	for (int i = 0; i < neiborNum; i++)
//	{
//		resize(matNeibor[i], matResizeNeibor[i], Size(7 * vecResizeXY[i].x, 7 * vecResizeXY[i].y));		
//	}
//}
//
////计算边缘参数 L,K
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
//	//卷积
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
//	//使用7个的7*7的Zernike模板（其本质是个矩阵）M00、M11R、M11I、M20、M31R、M31I、M40，分别与图像进行卷积，得到每个像素点的七个Zernike矩Z00、Z11R、Z11I、Z20、Z31R、Z31I、Z40
//
//	//对于每个点，根据它的七个Zernike矩，求得距离参数l和灰度差参数k，当l和k都满足设定的条件时，则判读该点为边缘点，并进一步利用上述7个Zernike矩求出该点的亚像素级坐标
//
//	//如果l或k不满足设定的条件，则该点不是边缘点，转到下一个点求解距离参数l和灰度差参数k
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
//			//计算Z11'和Z31'为计算L1,L2做准备,rotated_z11=Z11',rotated_z31=Z31'
//
//			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
//			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));
//
//			//计算L1，L2,
//			cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
//			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
//			cout << " " << endl;
//			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
//			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
//			para[L] = (l_method1 + l_method2) / 2;
//			//l = l - 0.207107;//减去修正值k
//
//			//计算k和h 
//			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
//			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;
//
//			vecPara.push_back(para);
//			/*阈值过滤*/
//			if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH)
//			{
//				/*边缘尺度恢复*/
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
//	//使用7个的7*7的Zernike模板（其本质是个矩阵）M00、M11R、M11I、M20、M31R、M31I、M40，分别与图像进行卷积，得到每个像素点的七个Zernike矩Z00、Z11R、Z11I、Z20、Z31R、Z31I、Z40
//
//	//对于每个点，根据它的七个Zernike矩，求得距离参数l和灰度差参数k，当l和k都满足设定的条件时，则判读该点为边缘点，并进一步利用上述7个Zernike矩求出该点的亚像素级坐标
//
//	//如果l或k不满足设定的条件，则该点不是边缘点，转到下一个点求解距离参数l和灰度差参数k
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
//	//显示所检测到的亚像素边缘
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
//	imshow("亚像素边缘", OriginalImage);
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\亚像素边缘.jpg" , OriginalImage);//保存多幅平均滤波后的图像	
//
//	waitKey(0);
//}
//
//
///*
//形态学边缘提取
//input:输入图像
//output:输出图像
//element:模板
//*/
//void  SingleBattery::getIGrad(const Mat input, Mat& output, Mat &element)
//{
//	//IGrad(f) = (f open g)	dilate g - (f close g) erode g
//
//	Mat erode_ouput, dilate_output, open_output, close_output;
//
//	morphologyEx(input, open_output, MORPH_OPEN, element);//开操作
//	morphologyEx(input, close_output, MORPH_CLOSE, element);//闭操作
//
//	dilate(open_output, dilate_output, element); //膨胀开操作后的图像
//	erode(close_output, erode_ouput, element); //腐蚀闭操作后的图像
//
//	absdiff(dilate_output, erode_ouput, output);
//}
//
//
//
///*
//形态学边缘提取
//input:输入图像
//vecEdgePoint:记录的边缘点
//*/
//void SingleBattery::getRoughEdge(Mat& input, vector<Point2i>& vecEdgePoint)
//{	
//	// 创建自定义结构元素
//	Mat element_1 = (Mat_<uchar>(3, 3) <<   //十字结构元素
//		0, 1, 0,
//		1, 1, 1,
//		0, 1, 0);	
//
//	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x形结构元素
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
//	addWeighted(output_1, 0.5, output_2, 0.5, 0, output);    //图像的线性混合，每张图0.5的权重
//
//	
//	convertScaleAbs(output, output, 3.0, 10);	//图像增强
//	threshold(output, output, 130, 255, THRESH_BINARY); //阈值化
//
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", output);//保存多幅平均滤波后的图像	
//	
//    //记录所有粗边缘点的坐标
//	Point2i  pointTemp;
//	for (int i = 0; i < output.rows; i++)
//	{
//		for (int j = 0; j < output.cols; j++)
//		{
//			if (output.at<uchar>(i, j) == 255)
//			{
//				//image.at<>(x,y)方法获得的点x和y是反过来的
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
////打印mat中所有的像素值，调试用
//void SingleBattery::print_px_value(Mat& im)
//{
//	int rowNumber = im.rows;  //行数
//	int colNumber = im.cols * im.channels();  //列数 x 通道数=每一行元素的个数
//
//	 //双重循环，遍历所有的像素值
//	for (int i = 0; i < rowNumber; i++)  //行循环
//	{
//		uchar* data = im.ptr<uchar>(i);  //获取第i行的首地址
//		for (int j = 0; j < colNumber; j++)   //列循环
//		{
//			//data[j] = data[j] / div * div + div / 2;
//			cout << (int)data[j]<<" " ;
//		}  //行处理结束
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
//	//卷积
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
//	//使用7个的7*7的Zernike模板（其本质是个矩阵）M00、M11R、M11I、M20、M31R、M31I、M40，分别与图像进行卷积，得到每个像素点的七个Zernike矩Z00、Z11R、Z11I、Z20、Z31R、Z31I、Z40
//
//	//对于每个点，根据它的七个Zernike矩，求得距离参数l和灰度差参数k，当l和k都满足设定的条件时，则判读该点为边缘点，并进一步利用上述7个Zernike矩求出该点的亚像素级坐标
//
//	//如果l或k不满足设定的条件，则该点不是边缘点，转到下一个点求解距离参数l和灰度差参数k
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
//			//计算Z11'和Z31'为计算L1,L2做准备,rotated_z11=Z11',rotated_z31=Z31'
//
//			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
//			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));
//
//			//计算L1，L2,
//		/*	cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
//			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
//			cout << " " << endl;*/
//			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
//			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
//			para[L] = (l_method1 + l_method2) / 2;
//			//l = l - 0.207107;//减去修正值k
//
//			//计算k和h 
//			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
//			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;
//
//			vecPara.push_back(para);
//			/*阈值过滤*/
//			//if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH) 
//			if (abs(l_method1 - l_method2) <= (sqrt(2) / (2.00*7.00)) && para[L]<l_t2 && para[K]>ZerBgrL && para[H] <50)
//			//if (1)
//			{
//				/*边缘尺度恢复*/
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
//	//显示所检测到的亚像素边缘
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
//	//imshow("亚像素边缘", matSingleResizeNeibor);
//	////imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\亚像素边缘.jpg", matSingleResizeNeibor);//保存多幅平均滤波后的图像	
//
//	//waitKey(0);
//}
//
//
//
///*
//获得边缘7 * 7邻域
//EdgePoint:要处理的边缘点(y,x)
//matIn:输入矩阵
//matNeibor:输出的邻域矩阵
//nbsize:邻域大小
//*/
//void SingleBattery::getNewROI(vector<Point2i>& EdgePoint, Mat& matIn, Mat& matNeibor, int nbsize)
//{
//	Mat matInRoi, matNewRoi;
//	int halfN = (nbsize - 1) / 2;
//	int x_MAX = 0;
//	int x_MIN = INT_MAX;
//	int y_MAX = 0;
//	int y_MIN = INT_MAX;
//	//遍历所有储存的边缘点
//	for (int i = 0; i < EdgePoint.size(); i++)
//	{
//		if (x_MAX < EdgePoint[i].x) x_MAX = EdgePoint[i].x;
//		if (x_MIN > EdgePoint[i].x) x_MIN = EdgePoint[i].x;
//		if (y_MAX < EdgePoint[i].y) y_MAX = EdgePoint[i].y;
//		if (y_MIN > EdgePoint[i].y) y_MIN = EdgePoint[i].y;
//		//matInRoi = matIn(Rect(EdgePoint[i].y, EdgePoint[i].x, 1, 1));//在输入图像上选取roi
//		//matInRoi.adjustROI(halfN, halfN, halfN, halfN);//将roi调整为7*7
//		//matNeibor[i] = matInRoi;
//		/*print_px_value(matInRoi);
//		imshow("roi",matInRoi);
//		waitKey(0);*/
//	}
//	matInRoi = matIn(Range(x_MIN, x_MAX),Range(y_MIN, y_MAX));//在输入图像上选取roi
//	matInRoi.adjustROI(halfN, halfN, halfN, halfN);//将roi调整为7*7
//	matNeibor = matInRoi;
//	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\亚像素边缘.jpg", matInRoi);//保存多幅平均滤波后的图像	
//	/*imshow("roi",matNeibor);
//	waitKey(0);*/
//}