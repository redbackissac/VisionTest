#include "singlebattery.h"

/*
���ƽ���˲�
�������:int imgNumͼ������
���:Mat����ƽ����ͼ��
*/
Mat SingleBattery::ImageAverage(int imgNum)
{
	Mat temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + ".jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����	
	//cout << "channels:" << temp.channels() << endl;	//��ӡͼ��ͨ����
	Mat AverageImage = Mat::zeros(temp.size(), CV_32FC1);                                       //��ʼ��ƽ��ͼ��Mat����ʽΪCV_32FC
	for (int i = 1; i <= imgNum; i++)                                                                 //���δ�3��ͼƬ
	{
		temp = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(i) + ".jpg", IMREAD_UNCHANGED);//�����i��ͼƬ		                                                       
		accumulate(temp, AverageImage);                                                         //����ʱͼ����ƽ��ͼ�����
	}
	AverageImage /= imgNum;                                                                     //ȡƽ��	
	AverageImage.convertTo(AverageImage, CV_8UC1);                                              //Ϊ��ʾ��Ҫ������ת��Ϊ8UC1
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", AverageImage);//������ƽ���˲����ͼ��
	return AverageImage;
}


Mat SingleBattery::getEdgeVal(Mat srcImg)
{
	Mat dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;

	//cvtColor(srcImg, gray_scrimage, COLOR_RGB2GRAY);   //ת��Ϊ�Ҷ�ͼ

	Sobel(srcImg, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);    //��x����ʹ��Sobel()����
	convertScaleAbs(grad_x, abs_grad_x);   //��Ե���ݶȷ���ֱ��������������Ļ��أ���Ե�Ǻ������������ĳһ������ݶ��Ǵ�ֱ��

	           
	Sobel(srcImg, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);	

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, srcImg);    //ͼ������Ի�ϣ�ÿ��ͼ0.5��Ȩ��
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//������ƽ���˲����ͼ��		
	return dstimage;
}

/*
���������߳��н��յĲ����б���ROI
*/
void SingleBattery::createROI(Mat srcImg)
{
	m_rois.reserve(0);//���roi�б�Ϊ����roi��׼��
	//���������б�
	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	{
		roi_parameters *pars = *it;//����ת��
		Mat *RoiImgs = new Mat;//Ϊ�µ�roi�����ڴ�	
		*RoiImgs = srcImg(Rect(pars->x, pars->y, pars->width, pars->height));//����roi
		m_rois.push_back(RoiImgs);//���´�����roi����roi�б�	
	}
}

/*
�ö�ֵ���ķ�����ȡ��Ե
*/
void SingleBattery::edge(Mat Input)
{

	threshold(Input, Input, 170, 255, 3);

}

/*
����һ����
*/
void SingleBattery::MeasureOneBattery()
{
	//Mat src;//����ͼ��	
	batImg = ImageAverage(3);//���ƽ��
	createROI(batImg);//����roi

	//��������roi����
	//for (int i = 0; i != m_rois.size(); ++i)
	//{		
	//	//edge(*m_rois[i]);//��ȡ��Ե
	//	getEdgeVal(*m_rois[i]);
	//}
	getEdgeVal(batImg);
	
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", batImg);//������ƽ���˲����ͼ��	
}

