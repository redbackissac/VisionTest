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
	m_stdboard = new StdBoard;
}
/*
子线程中的工作，所有处理内容放在此函数中
*/
void MyThread::MyWork()
{
	//读取参数
	//m_imgalgorithm->vec_roipars.clear();//先清空参数列表，为接收参数做好准备
	bat->vec_roipars.clear();
	bat->vecMissions.clear();
	bat->vec_strrois.clear();

	m_stdboard->vec_roipars.clear();
	m_stdboard->vec_strrois.clear();

	ConfigDataBase db;
	//db.read_roi(m_imgalgorithm->vec_roipars);//读取roi参数
	/*db.read_roi(bat->vec_roipars);
	db.read_lines(bat->vec_linetype,bat->vec_stdLines);*/
	db.read_mission(bat->vecMissions);
	db.read_structroi(bat->vec_strrois);


	db.read_structroi(m_stdboard->vec_strrois);

	m_stdboard->get_stdPoint();
	db.save_stdpoints(m_stdboard->vec_strrois);
	//真正的任务
	bat->getObjs();
	//Calibration *m_calibration = new Calibration;
	//m_calibration->getObjs();
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
	//遍历参数列表
	//C++11新增的关键字 auto，老快了，但是是只读的,auto&是可写的
	for (auto it : m_pars)
	{
		bat->vec_roipars.push_back(it);
		m_calibration->vec_roipars.push_back(it);
	}		
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


 