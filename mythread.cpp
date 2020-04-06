#pragma execution_character_set("utf-8")
#include "mythread.h"
#include "MainWindow.h"
#include "configdatabase.h"

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
	
	//m_imgalgorithm->vec_roipars.clear();//����ղ����б�Ϊ���ղ�������׼��
	bat->vec_roipars.clear();
	bat->vecMissions.clear();
	ConfigDataBase db;
	//db.read_roi(m_imgalgorithm->vec_roipars);//��ȡroi����
	db.read_roi(bat->vec_roipars);
	db.read_mission(bat->vecMissions);
	bat->getObjs();
	//Calibration *m_calibration = new Calibration;
	//m_calibration->getObjs();
	//m_calibration->getK();
	m_imgalgorithm->test();
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
	//���������б�
	//C++11�����Ĺؼ��� auto���Ͽ��ˣ�������ֻ����,auto&�ǿ�д��
	for (auto it : m_pars)
	{
		bat->vec_roipars.push_back(it);
		m_calibration->vec_roipars.push_back(it);
	}		
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


 