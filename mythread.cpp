#pragma execution_character_set("utf-8")
#include "mythread.h"
#include "MainWindow.h"

MyThread::MyThread(QObject* parent) : QObject(parent)
{
	isStop = false;
	bat = new SingleBattery;
	m_calibration = new Calibration;
	m_imgalgorithm = new ImgAlgorithm;
}
/*
���߳��еĹ��������д������ݷ��ڴ˺�����
*/
void MyThread::MyWork()
{
	bat->MeasureOneBattery();
	//Calibration *m_calibration = new Calibration;
	//m_calibration->MeasureOneBattery();
	//m_calibration->getK();
	//m_imgalgorithm->test();
	emit singal_back();
}


void MyThread::setFlag(bool flag)
{
	isStop = flag;
}



/*
�����߳̽���roi����
*/
void MyThread::acceptROIS(VecRoiParas m_pars)
{
	m_imgalgorithm->vec_roipars.clear();//����ղ����б�Ϊ���ղ�������׼��
	//���������б�
	//C++11�����Ĺؼ��� auto���Ͽ��ˣ�������ֻ����,auto&�ǿ�д��
	for (auto it : m_pars)
	{
		bat->vec_roipars.push_back(it);
		m_calibration->vec_roipars.push_back(it);
	}		
		//m_imgalgorithm->vec_roipars.push_back(it);
		//bat->vec_roipars.push_back(it);
		
}




///*
//�����߳̽���roi����
//*/
//void MyThread::acceptROIS(ROI_pars m_pars)
//{
//	m_roipars.reserve(0);//����ղ����б�Ϊ���ղ�������׼��
//	//���������б�
//	for (ROI_pars::iterator it = m_pars.begin(); it != m_pars.end(); ++it)
//	{
//		roi_parameters *pars = *it;
//		m_roipars.push_back(pars);//���½��ܵĲ�����������б���
//		//bat->m_roipars.push_back(pars);//���½��ܵĲ�����������б���
//		m_calibration->m_roipars.push_back(pars);
//	}
//}


 