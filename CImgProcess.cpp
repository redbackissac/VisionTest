#include "CImgProcess.h"

/*
���ƽ���˲�
�������:int imgNumͼ������
���:Mat����ƽ����ͼ��
*/
Mat SingleBattery::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".jpg");//��ʼ����ʱMat
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC3);                                       //��ʼ��ƽ��ͼ��Mat����ʽΪCV_32FC
	for (int i = 1; i <= imgNum; i++)                                                                 //���δ�3��ͼƬ
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg");//�����i��ͼƬ		                                                       
		accumulate(temp, AverageImage);                                                         //����ʱͼ����ƽ��ͼ�����
	}
	AverageImage /= imgNum;                                                                     //ȡƽ��	
	AverageImage.convertTo(AverageImage, CV_8UC3);                                              //Ϊ��ʾ��Ҫ������ת��Ϊ8UC3	
	return AverageImage;
}


Mat SingleBattery::getEdgeVal(Mat srcImg)
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

/*
���������߳��н��յĲ����б���ROI
*/
void SingleBattery::createROI(Mat srcImg)
{
	m_rois.reserve(0);//���roi�б�Ϊ����roi��׼��
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
�ö�ֵ���ķ�����ȡ��Ե
*/
void SingleBattery::edge()
{
	//��������roi����
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

