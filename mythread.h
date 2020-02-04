#pragma once
#pragma execution_character_set("utf-8")
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QFiledialog>

struct roi_parameters             //roi����Ĳ���
{
	int16_t x;
	int16_t y;
	int16_t width;
	int16_t height;
};
typedef QList<roi_parameters*> ROI_pars;//��������ROI���������QList

/*���ڿ���������*/
class MyThread : public QObject
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = 0);

	
	void setFlag(bool flag = true);
	
	ROI_pars m_roipars;

public slots:
	void MyWork();     //�̴߳���������
	void acceptROIS(ROI_pars m_pars);//�������̴߳�������roi����

signals:
	void singal_back();   //�����������ź�

private:
	int x, y, width, height;
	bool isStop;	//���̽�����־
	void getEdgeVal(); //��Ե��ȡ
	
};
#endif