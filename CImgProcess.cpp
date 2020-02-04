#include "CImgProcess.h"

/*
���ƽ���˲�
�������:int imgNumͼ������
���:Mat����ƽ����ͼ��
*/
Mat CImgProcess::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".jpg");//��ʼ����ʱMat
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC3);                                       //��ʼ��ƽ��ͼ��Mat����ʽΪCV_32FC
	for (int i = 1; i < imgNum+1; i++)                                                                 //���δ�3��ͼƬ
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg");//�����i��ͼƬ		                                                       
		accumulate(temp, AverageImage);                                                         //����ʱͼ����ƽ��ͼ�����
	}
	AverageImage /= imgNum;                                                                     //ȡƽ��	
	AverageImage.convertTo(AverageImage, CV_8UC3);                                              //Ϊ��ʾ��Ҫ������ת��Ϊ8UC3
	//imwrite("C:\\Users\\szsduwh\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//������ƽ���˲����ͼ��		
	return AverageImage;
}


Mat CImgProcess::getEdgeVal(Mat srcImg)
{
	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;

	cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ

	Sobel(gray_scrimage, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);    //��x����ʹ��Sobel()����
	convertScaleAbs(grad_x, abs_grad_x);   //��Ե���ݶȷ���ֱ��������������Ļ��أ���Ե�Ǻ������������ĳһ������ݶ��Ǵ�ֱ��

	           
	Sobel(gray_scrimage, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);	

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstimage);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//������ƽ���˲����ͼ��		
	return dstimage;
}

Mat CImgProcess::createROI(Mat srcImg,int x, int y, int width, int height)
{
	Mat temp, dstImg;
	//dstImg = srcImg.clone();
	temp = srcImg(Rect(x, y, width, height));
	dstImg = temp.clone();
	//imshow("ROI����ͼ", dstImg);//ROI����ͼ��
	return dstImg;
}

