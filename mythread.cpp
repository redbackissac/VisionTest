#pragma execution_character_set("utf-8")
#include "mythread.h"
#include "CImgProcess.h"
#include <QThread>
#include <QTextStream>
#include <QFile>
#include <QString>
#include "MainWindow.h"

MyThread::MyThread(QObject* parent) : QObject(parent)
{
	isStop = false;
}
/*
���߳��еĹ��������д������ݷ��ڴ˺�����
*/
void MyThread::MyWork()
{
	Mat scrimage, dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
	Mat ROI_top;
	CImgProcess *imgPro = new CImgProcess;	
	scrimage = imgPro->ImageAverage(3);                        //���ƽ��	
	//���������б�
	for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	{
		roi_parameters *pars = *it;
		ROI_top = imgPro->createROI(scrimage, scrimage.cols * pars->x / 100, scrimage.rows * pars->y / 100, scrimage.cols * pars->width / 100, scrimage.rows * pars->height / 100);
	}
	
	cvtColor(ROI_top, ROI_top, COLOR_RGB2GRAY);                //תΪ�Ҷ�ͼ
	//dstimage = imgPro->getEdgeVal(ROI_top);
	threshold(ROI_top,dstimage,170,255,3);
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", dstimage);//������ƽ���˲����ͼ��	
	imgPro->~CImgProcess();                         //ͼ�����ѽ������������������ͷ��ڴ�
	//delete imgPro;
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
	}
}

 