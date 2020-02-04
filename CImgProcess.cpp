#include "CImgProcess.h"

/*
多幅平均滤波
输入参数:int imgNum图像张数
输出:Mat类型平均后图像
*/
Mat CImgProcess::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".jpg");//初始化临时Mat
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC3);                                       //初始化平均图像Mat，格式为CV_32FC
	for (int i = 1; i < imgNum+1; i++)                                                                 //依次打开3张图片
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg");//载入第i张图片		                                                       
		accumulate(temp, AverageImage);                                                         //将临时图像与平均图像相加
	}
	AverageImage /= imgNum;                                                                     //取平均	
	AverageImage.convertTo(AverageImage, CV_8UC3);                                              //为显示需要将数据转换为8UC3
	//imwrite("C:\\Users\\szsduwh\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//保存多幅平均滤波后的图像		
	return AverageImage;
}


Mat CImgProcess::getEdgeVal(Mat srcImg)
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

Mat CImgProcess::createROI(Mat srcImg,int x, int y, int width, int height)
{
	Mat temp, dstImg;
	//dstImg = srcImg.clone();
	temp = srcImg(Rect(x, y, width, height));
	dstImg = temp.clone();
	//imshow("ROI区域图", dstImg);//ROI区域图像
	return dstImg;
}

