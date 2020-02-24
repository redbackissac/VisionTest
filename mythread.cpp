#pragma execution_character_set("utf-8")
#include "mythread.h"
#include "MainWindow.h"

MyThread::MyThread(QObject* parent) : QObject(parent)
{
	isStop = false;
	bat = new SingleBattery;
	m_calibration = new Calibration;
}
/*
���߳��еĹ��������д������ݷ��ڴ˺�����
*/
void MyThread::MyWork()
{
	//bat->MeasureOneBattery();
	//Calibration *m_calibration = new Calibration;
	//m_calibration->MeasureOneBattery();
	m_calibration->getK();
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
		//bat->m_roipars.push_back(pars);//���½��ܵĲ�����������б���
		m_calibration->m_roipars.push_back(pars);
	}
}


 