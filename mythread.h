#pragma once
#pragma execution_character_set("utf-8")
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QFiledialog>
#include <QThread>
#include <QTextStream>
#include <QFile>
#include <QString>
#include "CImgProcess.h"



/*���ڿ���������*/
class MyThread : public QObject
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = 0);

	
	void setFlag(bool flag = true);
	
	ROI_pars m_roipars;
	SingleBattery *imgPro; //ͼ�������

public slots:
	void MyWork();     //�̴߳���������
	void acceptROIS(ROI_pars m_pars);//�������̴߳�������roi����

signals:
	void singal_back();   //�����������ź�

private:
	int x, y, width, height;
	bool isStop;	//���̽�����־
	void getEdgeVal(); //��Ե��ȡ
	void test();
	
};
#endif