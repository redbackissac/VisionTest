#include "singlebattery.h"

/*
多幅平均滤波
输入参数:int imgNum图像张数
输出:Mat类型平均后图像
*/
Mat SingleBattery::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数	
	//cout << "channels:" << temp.channels() << endl;	//打印图像通道数
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC1);                                       //初始化平均图像Mat，格式为CV_32FC
	for (int i = 1; i <= imgNum; i++)                                                                 //依次打开3张图片
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg", IMREAD_UNCHANGED);//载入第i张图片		                                                       
		accumulate(temp, AverageImage);                                                         //将临时图像与平均图像相加
	}
	AverageImage /= imgNum;                                                                     //取平均	
	AverageImage.convertTo(AverageImage, CV_8UC1);                                              //为显示需要将数据转换为8UC1
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//保存多幅平均滤波后的图像
	return AverageImage;
}


Mat SingleBattery::getEdgeVal(Mat srcImg)
{
	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;

	//cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //转变为灰度图

	Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);    //对x方向使用Sobel()函数
	convertScaleAbs(grad_x, abs_grad_x);   //边缘与梯度方向垂直，所以输出出来的话呢，边缘是和我们所计算的某一方向的梯度是垂直的

	           
	Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);	

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, srcImg);    //图像的线性混合，每张图0.5的权重
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//保存多幅平均滤波后的图像		
	return dstimage;
}

/*
根据在子线程中接收的参数列表创建ROI
*/
void SingleBattery::createROI(Mat srcImg)
{
	m_rois.reserve(0);//清空roi列表，为创建roi做准备
	//遍历参数列表
	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	{
		roi_parameters *pars = *it;//类型转换
		Mat *RoiImgs = new Mat;//为新的roi开辟内存	
		*RoiImgs = srcImg(Rect(pars->x, pars->y, pars->width, pars->height));//创建roi
		m_rois.push_back(RoiImgs);//将新创建的roi加入roi列表	
	}
}

/*
用二值化的方法提取边缘
*/
void SingleBattery::edge(Mat Input)
{

	threshold(Input, Input, 170, 255, 3);

}

/*
测量一块电池
*/
void SingleBattery::MeasureOneBattery()
{
	//Mat src;//输入图像	
	batImg = ImageAverage(3);//多幅平均
	createROI(batImg);//创建roi

	//遍历所有roi区域
	//for (int i = 0; i != m_rois.size(); ++i)
	//{		
	//	//edge(*m_rois[i]);//提取边缘
	//	getEdgeVal(*m_rois[i]);
	//}
	getEdgeVal(batImg);
	
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", batImg);//保存多幅平均滤波后的图像	
}

