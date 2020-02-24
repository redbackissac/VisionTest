#pragma once
#pragma execution_character_set("utf-8")
#ifndef MYTHREAD_H
#define MYTHREAD_H

//#include <QObject>
#include <QThread>
#include "singlebattery.h"
#include "calibration.h"

//#include <QFiledialog>
//#include <QTextStream>
//#include <QFile>
//#include <QString>
//#include "iostream"


using namespace std;

/*���ڿ���������*/
class MyThread : public QObject
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = 0);

	
	void setFlag(bool flag = true);
	
	ROI_pars m_roipars;
	SingleBattery *bat; //ͼ�������
	Calibration *m_calibration; //�궨�����

public slots:
	void MyWork();     //�̴߳���������
	void acceptROIS(ROI_pars m_pars);//�������̴߳�������roi����

signals:
	void singal_back();   //�����������ź�

private:
	//int x, y, width, height;
	bool isStop;	//���̽�����־	
};
#endif