#include "imgAlgorithm.h"



//打印mat中所有的像素值，调试用
void print_px_value(Mat& im)
{
	int rowNumber = im.rows;  //行数
	int colNumber = im.cols * im.channels();  //列数 x 通道数=每一行元素的个数

											  //双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)  //行循环
	{
		uchar* data = im.ptr<uchar>(i);  //获取第i行的首地址
		for (int j = 0; j < colNumber; j++)   //列循环
		{
			//data[j] = data[j] / div * div + div / 2;
			cout << (int)data[j] << " ";
		}  //行处理结束
		cout << endl;
	}
	cout << "" << endl;
}

void ImgAlgorithm::test()//用于测试
{
	openImg(srcImg);//打开图像
	createROI(srcImg, vec_rois);//创建roi
	for (auto it_roi : vec_rois)
	{
		///*获得粗边缘位置vecEdgePoint*/
		//vector<Point2i> vecEdgePoint;//粗边缘坐标		
		//getRoughEdge_All(it_roi, vecEdgePoint);//提取粗略边缘坐标

		///*为每个粗边缘点提取单独的7*7邻域*/
		//vector<Mat> AllNeibors;
		//getNeiborOfPoints(vecEdgePoint,it_roi, AllNeibors);



	 //   /*创建粗边缘点的7*7邻域*/
		//int neiborNum;//邻域的数量，即边缘点的数量
		//Mat AllNeibor;//粗边缘点的7*7邻域
		//neiborNum = vecEdgePoint.size();
	
		//getNeiborROI(vecEdgePoint, it_roi, AllNeibor);
		//


		///*亚像素精确边缘位置*/
		//vector<Vec4d> vecPara;
		//vector<Point2d> VecSubPixelEdgePoint;
		//getSubPixEdge(AllNeibor, vecPara, VecSubPixelEdgePoint);
		//int i = 1;
	}
	
	
}


/*
打开待处理图像
srcImg:打开的图像，后续处理的都是这张图
*/
void ImgAlgorithm::openImg(Mat &srcImg)
{
	srcImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数
}


/*
根据在子线程中接收的参数列表创建ROI
不改变原图像
srcImg:输入图像
vec_rois：创建的roi向量
*/
void ImgAlgorithm::createROI(const Mat srcImg, vector<Mat> &vec_rois)
{	
	vec_rois.clear();//清空roi列表，为创建roi做准备
	//遍历参数列表
	for (auto it_roipar : vec_roipars)
	{
		Mat RoiImgs = srcImg(Rect(it_roipar[0], it_roipar[1], it_roipar[2], it_roipar[3]));//创建roi		
		vec_rois.push_back(RoiImgs);//将新创建的roi加入roi列表	
	}	
}

void ImgAlgorithm::createROI(const Mat srcImg, vector<struct_roi>& vec_strrois)
{	
	//遍历参数列表
	for (auto &it_roi : vec_strrois)
	{
		it_roi.roi = srcImg(Rect(it_roi.roipar[0], it_roi.roipar[1], it_roi.roipar[2], it_roi.roipar[3]));//创建roi		
		//vec_rois.push_back(RoiImgs);//将新创建的roi加入roi列表	
	}
}

/*
改进形态学梯度边缘提取
IGrad(f) = (f open g)	dilate g - (f close g) erode g
input:输入图像
output:输出图像
element:模板
*/
void  ImgAlgorithm::getIGrad(const Mat input, Mat& output, Mat &element)
{
	Mat erode_ouput, dilate_output, open_output, close_output;

	morphologyEx(input, open_output, MORPH_OPEN, element);//开操作
	morphologyEx(input, close_output, MORPH_CLOSE, element);//闭操作

	dilate(open_output, dilate_output, element); //膨胀开操作后的图像
	erode(close_output, erode_ouput, element); //腐蚀闭操作后的图像

	absdiff(dilate_output, erode_ouput, output);
}



/*
获取所有的粗边缘点坐标
用形态学的方法，自带滤波，牛不牛逼
input:输入图像
vecEdgePoint:记录的边缘点
*/
void ImgAlgorithm::getRoughEdge_All(const Mat input, vector<Point2i>& vecEdgePoint)
{
	// 创建自定义结构元素
	Mat element_1 = (Mat_<uchar>(3, 3) <<   //十字结构元素
		0, 1, 0,
		1, 1, 1,
		0, 1, 0);

	Mat element_2 = (Mat_<uchar>(3, 3) <<  //x形结构元素
		1, 0, 1,
		0, -1, 0,
		1, 0, 1);

	Mat output_1, output_2;

	getIGrad(input, output_1, element_1);//形态学边缘提取->十字结构元素
	getIGrad(input, output_2, element_2);//形态学边缘提取->x形结构元素

	Mat output;
	addWeighted(output_1, 0.5, output_2, 0.5, 0, output);    //图像的线性混合，每张图0.5的权重

	//增强图像使边缘更加明显
	convertScaleAbs(output, output, 3.0, 10);	//图像增强
	threshold(output, output, 130, 255, THRESH_BINARY); //阈值化

    //记录所有粗边缘点的坐标
	Point2i  pointTemp;
	for (int i = 0; i < output.rows; i++)
		for (int j = 0; j < output.cols; j++)
			if (output.at<uchar>(i, j) == 255)
			{
				//image.at<>(x,y)方法获得的点x和y是反过来的
				pointTemp.x = i;
				pointTemp.y = j;
				vecEdgePoint.push_back(pointTemp);
			}
}

///*
//正交边缘轮廓排序比较规则
//*/
//bool cmp(const Rect& a, const Rect& b)
//{
//	if (a.x < b.x)
//		return true;
//	else
//		return false;
//}

/*
获取正交粗边缘点坐标
Input:输入图像
Output：输出图像
vecEdgeOutline:正交粗边缘点的矩形轮廓
*/
void ImgAlgorithm::getRoughEdge_Normal(const Mat Input, Mat &Output, vector<Rect> &vecEdgeOutline)
{
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
	Mat Edge_X, Edge_Y, Edge_XY;//只包含X方向的边缘、只包含Y方向的边缘、只包含X和Y方向的边缘

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
		vecEdgeOutline.push_back(boundingRect(Mat(contours_out[i])));// 转换为矩形轮廓
	}
	//sort(vecEdgeOutline.begin(), vecEdgeOutline.end(), cmp); // 重排轮廓信息	
}


/*
获取以粗边缘为中心的邻域作为roi
获得边缘7 * 7邻域
EdgePoint:要处理的边缘点(y,x)
matIn:输入矩阵
matNeibor:输出的邻域矩阵
nbsize:邻域大小
*/
void ImgAlgorithm::getNeiborROI(const Line_Type type, const vector<Point2i> EdgePoint, const Mat matIn, Mat& matNeibor, Point2d &point,int nbsize)
{
	Mat matInRoi, matNewRoi;
	int halfN = (nbsize - 1) / 2;
	int x_MAX = 0;
	int x_MIN = INT_MAX;
	int y_MAX = 0;
	int y_MIN = INT_MAX;

	//遍历所有储存的边缘点
	for (auto it_EdgePoint : EdgePoint)
	{
		if (x_MAX < it_EdgePoint.x) x_MAX = it_EdgePoint.x;
		if (x_MIN > it_EdgePoint.x) x_MIN = it_EdgePoint.x;
		if (y_MAX < it_EdgePoint.y) y_MAX = it_EdgePoint.y;
		if (y_MIN > it_EdgePoint.y) y_MIN = it_EdgePoint.y;
	}
	point.y = x_MIN;
	point.x = y_MIN;
	matInRoi = matIn(Range(x_MIN, x_MAX), Range(y_MIN, y_MAX));//在输入图像上选取roi
	/*imshow("sex", matInRoi);
	waitKey(0);*/
	if (type == HORIZONTAL)//水平线
		matInRoi.adjustROI(halfN, halfN, 0, 0);//将roi调整为7*7
	else
		matInRoi.adjustROI(0, 0, halfN, halfN);//将roi调整为7*7
	
	matNeibor = matInRoi;
}


/*
将拟合的直线转换为ax + by + c = 0的标准形式
y0=(m/n)x0+b  -> mx-ny+(-mx0+ny0)=0
m=InputLine[1]
n=InputLine[0]
x0=InputLine[2]
y0=InputLine[3]
*/
void ImgAlgorithm::changeLine2std(const Vec4f InputLine, Vec3f &OutputLine)
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
获得边缘7 * 7邻域
EdgePoint:要处理的边缘点(y,x)
matIn:要取邻域的图像
matNeibor:输出,得到的邻域
nbsize:邻域大小
*/
void ImgAlgorithm::getNeiborOfPoints(const vector<Point2i> EdgePoint, const Mat matIn, vector<Mat> &matNeibor, int nbsize)
{
	Mat matInRoi, matNewRoi;
	int halfN = (nbsize - 1) / 2;
	//遍历所有储存的边缘点
	for (auto it_edgepoint : EdgePoint)
	{
		matInRoi = matIn(Rect(it_edgepoint.y, it_edgepoint.x, 1, 1));//在输入图像上选取roi
		matInRoi.adjustROI(halfN, halfN, halfN, halfN);//将roi调整为7*7
		matNeibor.push_back(matInRoi);
		//matNeibor[i] = matInRoi;
	}
	//for (auto it_roi : matNeibor)
		//print_px_value(it_roi);
}




/*
获取亚像素边缘
InputNeibor:输入图像,待提取亚像素边缘的邻域
vecPara:亚像素边缘的参数,L,θ,H,K
nbsize:邻域大小
*/
void ImgAlgorithm::getSubPixEdge(const Mat InputNeibor, vector<Vec4d>& vecPara, vector<Point2d>& VecSubPixelEdgePoint, int nbsize, int ZerBgrL, int ZerBgrH)
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

	//卷积
	filter2D(InputNeibor, mZerImageM00, CV_64F, ZERPOLY00);
	filter2D(InputNeibor, mZerImageM11R, CV_64F, ZERPOLY11R);
	filter2D(InputNeibor, mZerImageM11I, CV_64F, ZERPOLY11I);
	filter2D(InputNeibor, mZerImageM20, CV_64F, ZERPOLY20);
	filter2D(InputNeibor, mZerImageM31R, CV_64F, ZERPOLY31R);
	filter2D(InputNeibor, mZerImageM31I, CV_64F, ZERPOLY31I);
	filter2D(InputNeibor, mZerImageM40, CV_64F, ZERPOLY40);

	double rotated_z11 = 0.0;
	double rotated_z31 = 0.0;
	double l_method1 = 0.0;
	double l_method2 = 0.0;

	double l_t1 = sqrt(2) / (2.00 * nbsize);
	double l_t2 = sqrt(2) / 2.00;

	int row_number = InputNeibor.rows;
	int col_number = InputNeibor.cols;
	//使用7个的7*7的Zernike模板（其本质是个矩阵）M00、M11R、M11I、M20、M31R、M31I、M40，分别与图像进行卷积，得到每个像素点的七个Zernike矩Z00、Z11R、Z11I、Z20、Z31R、Z31I、Z40

	//对于每个点，根据它的七个Zernike矩，求得距离参数l和灰度差参数k，当l和k都满足设定的条件时，则判读该点为边缘点，并进一步利用上述7个Zernike矩求出该点的亚像素级坐标

	//如果l或k不满足设定的条件，则该点不是边缘点，转到下一个点求解距离参数l和灰度差参数k
	for (int i = 0; i < row_number; i++)
		for (int j = 0; j < col_number; j++)
		{
			if (mZerImageM00.at<double>(i, j) == 0)
				continue;

			para[THETA] = atan2(mZerImageM31I.at<double>(i, j), mZerImageM31R.at<double>(i, j));

			//计算Z11'和Z31'为计算L1,L2做准备,rotated_z11=Z11',rotated_z31=Z31'

			rotated_z11 = sin(para[THETA])*(mZerImageM11I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM11R.at<double>(i, j));
			rotated_z31 = sin(para[THETA])*(mZerImageM31I.at<double>(i, j)) + cos(para[THETA])*(mZerImageM31R.at<double>(i, j));

			//计算L1，L2,
			/*	cout << "mZerImageM40.at<double>(i, j)" << mZerImageM40.at<double>(i, j) << endl;
			cout << "mZerImageM20.at<double>(i, j)" << mZerImageM20.at<double>(i, j) << endl;
			cout << " " << endl;*/
			l_method1 = sqrt((5 * mZerImageM40.at<double>(i, j) + 3 * mZerImageM20.at<double>(i, j)) / (8 * mZerImageM20.at<double>(i, j)));
			l_method2 = sqrt((5 * rotated_z31 + rotated_z11) / (6 * rotated_z11));
			para[L] = (l_method1 + l_method2) / 2;
			//l = l - 0.207107;//减去修正值k

			//计算k和h 
			para[K] = 3 * rotated_z11 / 2 / pow((1 - l_method2*l_method2), 1.5);
			para[H] = (mZerImageM00.at<double>(i, j) - para[K] * PI / 2 + para[K] * asin(l_method2) + para[K] * l_method2*sqrt(1 - l_method2*l_method2)) / PI;

			vecPara.push_back(para);
			/*阈值过滤*/
			//if (para[L]>l_t1 &&  para[L]<l_t2 &&  para[K]>ZerBgrL && para[H]>ZerBgrH) 
			if (abs(l_method1 - l_method2) <= (sqrt(2) / (2.00*7.00)) && para[L]<l_t2 && para[K]>ZerBgrL && para[H] <50)			
			{
				/*边缘尺度恢复*/
				point.x = (j + para[L] * nbsize*cos(para[THETA]) / 2.00);
				point.y = (i + para[L] * nbsize*sin(para[THETA]) / 2.00);
				VecSubPixelEdgePoint.push_back(point);
			}
			else
				continue;

		}

	//显示所检测到的亚像素边缘

	//	for (size_t i = 0; i < subPixelRela.size(); i++)

	//{

	//	Point center_forshow(cvRound(subPixelRela[i].x), cvRound(subPixelRela[i].y));

	//	circle(matSingleResizeNeibor, center_forshow, 1, 255, 1, 8, 0);

	//}
	//int i = 0;
	//imshow("亚像素边缘", matSingleResizeNeibor);
	////imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\亚像素边缘.jpg", matSingleResizeNeibor);//保存多幅平均滤波后的图像	

	//waitKey(0);
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
//																								//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//保存多幅平均滤波后的图像
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
//																 //imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//保存多幅平均滤波后的图像		
//	return dstimage;
//}
//
