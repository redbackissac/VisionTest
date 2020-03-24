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
子线程中的工作，所有处理内容放在此函数中
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
从主线程接收roi参数
*/
void MyThread::acceptROIS(VecRoiParas m_pars)
{
	m_imgalgorithm->vec_roipars.clear();//先清空参数列表，为接收参数做好准备
	//遍历参数列表
	//C++11新增的关键字 auto，老快了，但是是只读的,auto&是可写的
	for (auto it : m_pars)
	{
		bat->vec_roipars.push_back(it);
		m_calibration->vec_roipars.push_back(it);
	}		
		//m_imgalgorithm->vec_roipars.push_back(it);
		//bat->vec_roipars.push_back(it);
		
}




///*
//从主线程接收roi参数
//*/
//void MyThread::acceptROIS(ROI_pars m_pars)
//{
//	m_roipars.reserve(0);//先清空参数列表，为接收参数做好准备
//	//遍历参数列表
//	for (ROI_pars::iterator it = m_pars.begin(); it != m_pars.end(); ++it)
//	{
//		roi_parameters *pars = *it;
//		m_roipars.push_back(pars);//将新接受的参数存入参数列表中
//		//bat->m_roipars.push_back(pars);//将新接受的参数存入参数列表中
//		m_calibration->m_roipars.push_back(pars);
//	}
//}


 