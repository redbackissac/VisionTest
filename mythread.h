#pragma once
#pragma execution_character_set("utf-8")
#ifndef MYTHREAD_H
#define MYTHREAD_H

//#include <QObject>
#include <QThread>
#include "singlebattery.h"
#include "calibration.h"
#include "imgAlgorithm.h"
#include "configdatabase.h"
#include "stdboard.h"

//#include <QFiledialog>
//#include <QTextStream>
//#include <QFile>
//#include <QString>
//#include "iostream"


using namespace std;

/*用于开启检测进程*/
class MyThread : public QObject
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = 0);

	
	void setFlag(bool flag = true);
	
	//ROI_pars m_roipars;	
	SingleBattery *bat; //图像处理对象
	Calibration *m_calibration; //标定板对象
	ImgAlgorithm *m_imgalgorithm;//电池和标定板的父类，此文件中仅作调试用
	StdBoard *m_stdboard;//标准板
public slots:
	void MyWork();     //线程处理函数定义
	//void acceptROIS(ROI_pars m_pars);//接收主线程传递来的roi参数
	void acceptROIS(VecRoiParas);//接收主线程传递来的roi参数,并赋给被测对象

signals:
	void singal_back();   //处理结果返回信号

private:
	//int x, y, width, height;
	bool isStop;	//进程结束标志	
};
#endif