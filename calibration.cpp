#include "calibration.h"
#define HIGH 0
#define MIDDLE 1
#define LOW 2

/*排序比较规则*/
bool cmp(const Rect& a, const Rect& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}

bool cmpLines(const Vec2f& a, const Vec2f& b)
{
	if (a[0] < b[0])
		return true;
	else
		return false;
}

bool cmpDecisions(const Vec2i& a, const Vec2i& b)
{
	if (a[0] < b[0])
		return true;
	else
		return false;
}

bool cmpSubPix(const Point2d& a, const Point2d& b)
{
	if (a.x < b.x)
		return true;
	else
		return false;
}

/*
计算粗边缘轮廓分类标准
Input:输入图像
Sequence:分类标准
*/
void Calibration::getStdPixel(const Mat Input, Vec3i &Sequence)
{
	//霍夫变换检测直线
	vector<Vec2f> lines;//检测到的直线(ρ是离坐标原点((0,0)（也就是图像的左上角）的距离;θ是弧度线条旋转角度（0~垂直线，π/2~水平线）。)	
	//'1'生成极坐标时候的像素扫描步长，'CV_PI/180'生成极坐标时候的角度步长，'10'最小直线长度，'0'最大间隔（能构成一条直线） 	
	HoughLines(Input, lines, 1, CV_PI / 180, 100, 0, 0);

	sort(lines.begin(), lines.end(), cmpLines); // 以到原点距离重排直线信息
	
	Sequence[HIGH] = lines[0][0];//高
	Sequence[MIDDLE] = lines[1][0];//中
	Sequence[LOW] = lines[2][0];//低
}


/*
粗边缘轮廓分类器
num_location:输入边缘轮廓
Sequence[3]:判别标准
Classification:轮廓所属类别
*/
int Calibration::Classify(const Rect num_location, const Vec3i Sequence)
{
	vector<Vec2i> decisions; //用于判断高中低的判别函数,(判别函数值,类别标签)
	for (int i = HIGH; i <= LOW; i++)//分别求出每一类的判别函数值
	{
		Vec2i decision;		
		decision[0] = abs(num_location.y - Sequence[i]);
		decision[1] = i;
		decisions.push_back(decision);
	}

	//排序求出最小的判别函数
	sort(decisions.begin(), decisions.end(), cmpDecisions); // 根据判别函数值重排判别信息
	return decisions[0][1];//返回分类结果
}

/*
校准ROI，去除两端无法计算标定值的部分
InputROI:输入roi
num_location:所有的轮廓
Sequence:判别标准
*/
void Calibration::resetROI(Mat &InputROI, vector<Rect> num_location, const Vec3i Sequence)
{
	const int max = num_location.size();
	if(Classify(num_location[0], Sequence) == 1)//掐头
		InputROI.adjustROI(0, 0, -num_location[1].x, 0);
	if(Classify(num_location[max - 1], Sequence) == 1)//去尾
		InputROI.adjustROI(0, 0, 0, -num_location[max - 1].x);
}

/*
将拟合的直线转换为ax + by + c = 0的标准形式
y0=(m/n)x0+b  -> mx-ny+(-mx0+ny0)=0
m=InputLine[1]
n=InputLine[0]
x0=InputLine[2]
y0=InputLine[3]
*/
void Calibration::changeLine2std(const Vec4f InputLine, Vec3f &OutputLine)
{
	float a, b, c;
	a = InputLine[1];
	b = -InputLine[0];
	c = -InputLine[1] * InputLine[2] + InputLine[0] * InputLine[3];
	OutputLine[0] = a;
	OutputLine[1] = b;
	OutputLine[2] = c;
}


/*
计算两条直线距离
设直线 L 的方程为Ax+By+C=0，点 P 的坐标为（X0，Y0），则点 P 到直线 L 的距离为:|AX0+BY0+C|/sqrt(A^2+B^2)
*/
double Calibration::calDist(const Vec3f Line_1, const Vec2d EndPoint_1, const Vec3f Line_2, const Vec2d EndPoint_2)
{
	int a = 0, b = 1, c = 2;
	int left = 0, right = 1;
	double x1 = EndPoint_1[left], x2 = EndPoint_2[right];//Line_1使用左端点,Line_2使用右端点
	double y1,y2,distance, distance_1, distance_2;
	//计算y1,y2
	//y = -(ax+c)/b
	y1 = -(Line_1[a] * x1 + Line_1[c]) / Line_1[b];
	y2 = -(Line_2[a] * x2 + Line_2[c]) / Line_2[b];

	//计算端点到另一条直线的距离
	distance_1 = abs(Line_2[a] * x1 + Line_2[b] * y1 + Line_2[c]) / sqrtl(Line_2[a] * Line_2[a] + Line_2[b] * Line_2[b]);
	distance_2 = abs(Line_1[a] * x2 + Line_1[b] * y2 + Line_1[c]) / sqrtl(Line_1[a] * Line_1[a] + Line_1[b] * Line_1[b]);

	//取平均
	distance = (distance_1 + distance_2) / 2;
	return distance;
}

/*
计算标定值k
*/
void Calibration::getK()
{
	calImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数
	//cvtColor(calImg, calImg, COLOR_RGB2GRAY);   //转变为灰度图
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(ttt).jpg", calImg);//保存多幅平均滤波后的图像
	//cout << "channels:" << calImg.channels() << endl;	//打印图像通道数//cout << "channels:" << temp.channels() << endl;	//打印图像通道数
	createROI(calImg);//创建roi						 
	//遍历所有roi区域
	for (int i = 0; i != m_rois.size(); ++i)
	{
		/*获得粗边缘位置vecEdgePoint*/
		//vector<Point2i> vecEdgePoint;//粗边缘坐标
		vector<Rect> num_location;//粗边缘轮廓
		Mat BinImg = m_rois[i]->clone();//克隆一份roi用于存放处理后的二值图
		getSmallEdgePoint(*m_rois[i], BinImg, num_location);//只保留水平及垂直方向的边缘点

	/*	imshow("BinImg", BinImg);
		waitKey(0);*/

		/*建立粗边缘轮廓分类标准*/
		Vec3i Sequence;//粗边缘轮廓分类标准
		getStdPixel(BinImg, Sequence);
		
		/*校正ROI,去除两端无法计算标定值的部分*/		
		if (Classify(num_location[0], Sequence) == MIDDLE)//掐头
		{
			m_rois[i]->adjustROI(0, 0, - num_location[1].x, 0);
			//BinImg.adjustROI(0, 0, - num_location[1].x, 0);
			//num_location.erase(num_location.begin());//将第一个粗边缘轮廓删除
		}
		const int max = num_location.size();
		if (Classify(num_location[max - 1], Sequence) == MIDDLE)//去尾
		{			
			m_rois[i]->adjustROI(0, 0, 0, - num_location[max - 2].x);
			//BinImg.adjustROI(0, 0, 0, - num_location[max - 2].x);
			//num_location.erase(num_location.end());
		}	


		//重新提取粗边缘轮廓
		num_location.clear();
		BinImg = m_rois[i]->clone();//克隆一份roi用于存放处理后的二值图
		getSmallEdgePoint(*m_rois[i], BinImg, num_location);//只保留水平及垂直方向的边缘点
	/*	imshow("BinImg", BinImg);
		waitKey(0);*/


		vector<vector<double> > Ks(m_rois[i]->rows, vector<double>(m_rois[i]->cols));;//计算出的K值,> >中间空格不能省略
		for (int m = 0; m < m_rois[i]->rows; m++) //初始化为0
			for (int n = 0; n < m_rois[i]->cols; n++)
				Ks[m][n] = 0.0;


		//遍历所有粗边缘轮廓
		for (int m = 0; m < num_location.size(); m++)
		{
			if (Classify(num_location[m], Sequence) != MIDDLE)//中间的不用
			{

				Mat* smallROI;//为一组锯齿创建3个ROI
				smallROI = new Mat[3];
				for (int n = 0; n < 3; n++)
				{
					Mat matNewRoi;
					matNewRoi = (*m_rois[i])(Rect(num_location[m + n].x, num_location[m + n].y, num_location[m + n].width, num_location[m + n].height));//在输入图像上选取roi
					//cout << num_location[i].x << " " << num_location[i].y << endl;
					matNewRoi.adjustROI(3, 3, 0, 0);//将roi调整为7*7	
					smallROI[n] = matNewRoi;
				/*	print_px_value(smallROI[n]);
					cout << " " << endl;*/
				}		
				
				/*拟合直线*/			
				vector<Vec3f> line_stds;//拟合出标准形式直线的参数
				vector<Vec2d> endpoints;//线段端点	 
				//for (int n = 0; n < 3; n++)
				for (int n = 0; n < 3; n++)
				{
					/*亚像素精确边缘位置*/
					vector<Vec4d> vecPara;
					vector<Point2d> subPixelRela;
					/*print_px_value(smallROI[n]);
					cout << " " << endl;*/

					m_calEdgePara(smallROI[n], vecPara, subPixelRela);//亚像素边缘计算
					sort(subPixelRela.begin(), subPixelRela.end(), cmpSubPix); // 重排亚像素边缘
					//print_px_value(smallROI[n]);
					//cout << " " << endl;
					//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(n) + "(ttt).jpg", smallROI[n]);//保存多幅平均滤波后的图像
					
					for (int k = 0; k < subPixelRela.size(); k++)//转换为在大ROI中的坐标
					{
						subPixelRela[k].x += num_location[m + n ].x;
						subPixelRela[k].y += num_location[m + n ].y;
					}
					//记录线段端点
					Vec2d Endpoint;//[左端点.x,右端点.x]
					const size_t size = subPixelRela.size();
					Endpoint[0] = subPixelRela[0].x;					
					Endpoint[1] = subPixelRela[size - 1].x;
					endpoints.push_back(Endpoint);


					/*直线拟合*/
					Vec4f line_para;//拟合出直线的参数
					Vec3f line_std;//拟合出标准形式直线的参数	 
					fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
					changeLine2std(line_para, line_std);//转换为标准形式				
					line_stds.push_back(line_std);
				}	


				double distance_1 = calDist(line_stds[0], endpoints[0], line_stds[1], endpoints[1]);//计算距离1
				double distance_2;


											   //vector<Vec4f> line_paras;
											   ////对每个小roi特征提取
											   //for (int i = 0; i < num_location.size(); i++)
											   //{		
											   //	/*亚像素精确边缘位置*/
											   //	vector<Vec4d> vecPara;
											   //	vector<Point2d> subPixelRela;
											   //	m_calEdgePara(smallROI[i], vecPara, subPixelRela);
											   //	for (int j = 0; j < subPixelRela.size(); j++)
											   //	{
											   //		subPixelRela[j].x += num_location[i].x;
											   //		subPixelRela[j].y += num_location[i].y;
											   //	}
											   //	
											   //	/*直线拟合*/
											   //	Vec4f line_para;//拟合出直线的参数
											   //	fitLine(subPixelRela, line_para, DIST_HUBER, 0, 0.000001, 0.000001);
											   //	line_paras.push_back(line_para);		
											   //}	
				//print_px_value(smallROI);
				//imshow("SmallROI", smallROI);				
				//waitKey(0); 


				//Mat* smallROI;//为每一小段线段创建ROI
				//smallROI = new Mat[num_location.size()];
				//for (int i = 0; i < num_location.size(); i++)
				//{
				//	Mat matNewRoi;
				//	matNewRoi = Input(Rect(num_location[i].x, num_location[i].y, num_location[i].width, num_location[i].height));//在输入图像上选取roi
				//	//cout << num_location[i].x << " " << num_location[i].y << endl;
				//	matNewRoi.adjustROI(3, 3, 0, 0);//将roi调整为7*7	
				//	smallROI[i] = matNewRoi;		
				//}

			}
		}
	}
}






/*
Input:输入图像
Output:输出图像
EdgePoint:提取的锯齿状模板的水平或竖直边的边缘点
*/
void Calibration::getSmallEdgePoint(const Mat Input,Mat &Output, vector<Rect> &num_location)
{
	//*获得粗边缘位置vecEdgePoint*/
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
	convertScaleAbs(AllEdge, AllEdge, 3.0, 10);	//图像增强
	threshold(Edge_XY, Output, 100, 255, THRESH_BINARY); //阈值化	

	//粗边缘轮廓提取
	vector<vector<Point> > contours_out;
	vector<Vec4i> hierarchy;
	findContours(Edge_XY, contours_out, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	// re-arrange location according to the real position in the original image 
	const size_t size = contours_out.size();

	for (int i = 0; i < size; i++)
	{
		num_location.push_back(boundingRect(Mat(contours_out[i])));// 转换为矩形轮廓
	}
	sort(num_location.begin(), num_location.end(), cmp); // 重排轮廓信息	
}





