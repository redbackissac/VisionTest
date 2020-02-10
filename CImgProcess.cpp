#include "CImgProcess.h"

/*
多幅平均滤波
输入参数:int imgNum图像张数
输出:Mat类型平均后图像
*/
Mat SingleBattery::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".jpg");//初始化临时Mat
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC3);                                       //初始化平均图像Mat，格式为CV_32FC
	for (int i = 1; i <= imgNum; i++)                                                                 //依次打开3张图片
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg");//载入第i张图片		                                                       
		accumulate(temp, AverageImage);                                                         //将临时图像与平均图像相加
	}
	AverageImage /= imgNum;                                                                     //取平均	
	AverageImage.convertTo(AverageImage, CV_8UC3);                                              //为显示需要将数据转换为8UC3	
	return AverageImage;
}


Mat SingleBattery::getEdgeVal(Mat srcImg)
{
	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;

	cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //转变为灰度图

	Sobel(gray_scrimage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);    //对x方向使用Sobel()函数
	convertScaleAbs(grad_x, abs_grad_x);   //边缘与梯度方向垂直，所以输出出来的话呢，边缘是和我们所计算的某一方向的梯度是垂直的

	           
	Sobel(gray_scrimage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);	

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstimage);    //图像的线性混合，每张图0.5的权重
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//保存多幅平均滤波后的图像		
	return dstimage;
}

/*
根据在子线程中接收的参数列表创建ROI
*/
void SingleBattery::createROI(Mat srcImg)
{
	m_rois.reserve(0);//清空roi列表，为创建roi做准备
	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	{
		roi_parameters *pars = *it;
		Mat *RoiImgs = new Mat;		
		*RoiImgs = srcImg(Rect(srcImg.cols * pars->x / 100, srcImg.rows * pars->y / 100, srcImg.cols * pars->width / 100, srcImg.rows * pars->height / 100));
		//threshold(RoiImgs, RoiImgs, 170, 255, 3);
		m_rois.push_back(RoiImgs);
	}
}

/*
用二值化的方法提取边缘
*/
void SingleBattery::edge()
{
	//遍历所有roi区域
	for (int i = 0; i != m_rois.size(); ++i)
	{
		//Mat RoiImgs = it;
		threshold(*m_rois[i], *m_rois[i], 170, 255, 3);
	}
	//for (ROIS::iterator it = m_rois.begin(); it != m_rois.end(); ++it)
	//{
	//	Mat RoiImgs = it;		
	//	//threshold(*RoiImgs, *RoiImgs, 170, 255, 3);
	//}
}

