#include "calibration.h"

/*排序比较规则*/
bool cmp(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}


/*
计算标定值k
*/
void Calibration::getK()
{
	calImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数
	//cvtColor(calImg, calImg, COLOR_RGB2GRAY);   //转变为灰度图
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(ttt).jpg", calImg);//保存多幅平均滤波后的图像
	cout << "channels:" << calImg.channels() << endl;	//打印图像通道数//cout << "channels:" << temp.channels() << endl;	//打印图像通道数
	createROI(calImg);//创建roi						 
	//遍历所有roi区域
	for (int i = 0; i != m_rois.size(); ++i)
	{
		/*获得粗边缘位置vecEdgePoint*/
		vector<Point2i> vecEdgePoint;//粗边缘坐标	
		getSmallEdgePoint(*m_rois[i], *m_rois[i], vecEdgePoint);//只保留水平及垂直方向的边缘点
	

	    /*创建粗边缘点的7*7邻域*/
		int neiborNum;//邻域的数量，即边缘点的数量
		Mat AllNeibor;//粗边缘点的7*7邻域
		neiborNum = vecEdgePoint.size();
	

		


		//AllNeibor = new Mat[neiborNum];		
		//getNeibor(vecEdgePoint, *m_rois[i], AllNeibor);

		/*在原图中显示出提取出的边缘，用于测试*/
		Mat test;
		test = m_rois[i]->clone();
		cvtColor(test, test, COLOR_GRAY2RGB);   //转变为rgb图
		cout << "channels:" << test.channels() << endl;
		Point center_forshow;
		for (int j = 0; j < vecEdgePoint.size(); j++)
		{
				center_forshow.x = cvRound(vecEdgePoint[j].y);
				center_forshow.y = cvRound(vecEdgePoint[j].x);
				circle(test, center_forshow, 1, Scalar(0,0,255), -1);//按照(x, y)画
			
		}

		imshow("test",test);
		waitKey(0);
		getNewROI(vecEdgePoint, *m_rois[i], AllNeibor);

		///*对邻域进行插值并且计算边缘参数*/
		//Mat* matResizeNeibor;//插值后得到的邻域
		//matResizeNeibor = new Mat[neiborNum];
		//resizeNeibor(matAllNeibor, matResizeNeibor, vecResizeXY, neiborNum);


		/*亚像素精确边缘位置*/
		vector<Vec4d> vecPara;
		vector<Point2d> subPixelRela;
		m_calEdgePara(AllNeibor, vecPara, subPixelRela);
		//subpixeltest(AllNeibor);


		/*直线拟合*/
		Vec4f line_para;//拟合出直线的参数
		fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
		int j = INT_MAX;
	}
}






/*
Input:输入图像
Output:输出图像
EdgePoint:提取的锯齿状模板的水平或竖直边的边缘点
*/
void Calibration::getSmallEdgePoint(Mat &Input,Mat Output, vector<Point2i> EdgePoint)
{
	///*获得粗边缘位置vecEdgePoint*/
	//vector<Point2i> vecEdgePoint;//粗边缘坐标	

	/* 形态学边缘提取*/
	//创建自定义结构元素
	Mat element_1 = (Mat_<uchar>(3, 3) <<   //十字结构元素
		0, 1, 0,
		1, 1, 1,
		0, 1, 0);

	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x形结构元素
		1, 0, 1,
		0, -1, 0,
		1, 0, 1);

	Mat IGrad_1, IGrad_2;

	getIGrad(Input, IGrad_1, element_1);
	getIGrad(Input, IGrad_2, element_2);

	Mat AllEdge;//包含所有边缘点的图像
	addWeighted(IGrad_1, 0.5, IGrad_2, 0.5, 0, AllEdge);   //图像的线性混合，每张图0.5的权重
	convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//图像增强
	threshold(AllEdge, AllEdge, 130, 255, THRESH_BINARY); //阈值化

	/*去除模板的斜边，先腐蚀，再膨胀*/
	Mat kernel;//膨胀腐蚀模板
	Mat Edge_X,Edge_Y,Edge_XY;//只包含X方向的边缘、只包含Y方向的边缘、只包含X和Y方向的边缘
	
    //水平线
	kernel = getStructuringElement(MORPH_RECT, Size(12, 1), Point(-1, -1));//腐蚀模板
	erode(AllEdge, Edge_X, kernel);//腐蚀
    kernel = getStructuringElement(MORPH_RECT, Size(9, 1), Point(-1, -1));//膨胀模板，比腐蚀模板小一点，为后面创建邻域做准备		
	dilate(Edge_X, Edge_X, kernel);//膨胀


	//竖直线
	kernel = getStructuringElement(MORPH_RECT, Size(1, 12), Point(-1, -1));//腐蚀模板
	erode(AllEdge, Edge_Y, kernel);//腐蚀	
	kernel = getStructuringElement(MORPH_RECT, Size(1, 9), Point(-1, -1));//膨胀模板，比腐蚀模板小一点，为后面创建邻域做准备
	dilate(Edge_Y, Edge_Y, kernel);//膨胀

	addWeighted(Edge_X, 0.5, Edge_Y, 0.5, 0, Edge_XY);   //图像的线性混合，每张图0.5的权重
	//convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//图像增强
	threshold(Edge_XY, Edge_XY, 100, 255, THRESH_BINARY); //阈值化
	imshow("Edge_X", Edge_X);
	imshow("Edge_Y", Edge_Y);
	imshow("Edge_XY", Edge_XY);
	waitKey(0);



	vector<vector<Point> > contours_out;
	vector<Vec4i> hierarchy;
	findContours(Edge_XY, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	// re-arrange location according to the real position in the original image 
	const size_t size = contours_out.size();
	vector<Rect> num_location;
	for (int i = 0; i < contours_out.size(); i++)
	{
		num_location.push_back(boundingRect(Mat(contours_out[i])));// 转换为矩形轮廓
	}
	sort(num_location.begin(), num_location.end(), cmp); // 重排轮廓信息

	Point2i  pointTemp;
	for (int i = 0; i < AllEdge.rows; i++)
	{
		for (int j = 0; j < AllEdge.cols; j++)
		{
			if (AllEdge.at<uchar>(i, j) == 255)
			{
				//image.at<>(x,y)方法获得的点x和y是反过来的
				pointTemp.x = i;
				pointTemp.y = j;
				EdgePoint.push_back(pointTemp);
			}
		}
	}
}



