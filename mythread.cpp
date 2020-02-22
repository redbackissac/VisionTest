#pragma execution_character_set("utf-8")
#include "mythread.h"
#include "calibration.h"
#include "MainWindow.h"

MyThread::MyThread(QObject* parent) : QObject(parent)
{
	isStop = false;
	bat = new SingleBattery;
}
/*
���߳��еĹ��������д������ݷ��ڴ˺�����
*/
void MyThread::MyWork()
{
	bat->MeasureOneBattery();
	//Mat scrimage, dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
	//Mat ROI_top;
	//
	//scrimage = imgPro->ImageAverage(3);                        //���ƽ��	
	////cout << "-------------------- ��ӡͼ����� ----------------------" << endl;	//��־λ	
	////cout << "flags:" << scrimage.flags << endl;	//ͼ��ߴ�	
	////cout << "size:" << scrimage.size << endl;	//�п�	
	////cout << "clos:" << scrimage.cols<<endl;	//�и�	
	////cout << "rows:" << scrimage.rows << endl;	//ά��	
	////cout << "dims:" << scrimage.dims << endl;

	//
	//////���������б�
	////for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	////{
	////	roi_parameters *pars = *it;
	////	ROI_top = scrimage(Rect(scrimage.cols * pars->x / 100, scrimage.rows * pars->y / 100, scrimage.cols * pars->width / 100, scrimage.rows * pars->height / 100));
	////	
	////}
	//
	////threshold(ROI_top, ROI_top, 170, 255, 3);
	//imgPro->createROI(scrimage);
	//imgPro->edge();
	//imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", scrimage);//������ƽ���˲����ͼ��	
	////imgPro->~CImgProcess();                         //ͼ�����ѽ������������������ͷ��ڴ�
	////delete imgPro;
	////test();
	emit singal_back();
}


void MyThread::setFlag(bool flag)
{
	isStop = flag;
}

/*
�����߳̽���roi����
*/
void MyThread::acceptROIS(ROI_pars m_pars)
{
	m_roipars.reserve(0);//����ղ����б�Ϊ���ղ�������׼��
	//���������б�
	for (ROI_pars::iterator it = m_pars.begin(); it != m_pars.end(); ++it)
	{
		roi_parameters *pars = *it;
		m_roipars.push_back(pars);//���½��ܵĲ�����������б���
		bat->m_roipars.push_back(pars);//���½��ܵĲ�����������б���		
	}
}


 