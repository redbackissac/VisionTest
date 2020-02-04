#pragma once
#pragma execution_character_set("utf-8")
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QFiledialog>

struct roi_parameters             //roi区域的参数
{
	int16_t x;
	int16_t y;
	int16_t width;
	int16_t height;
};
typedef QList<roi_parameters*> ROI_pars;//存贮所有ROI区域参数的QList

/*用于开启检测进程*/
class MyThread : public QObject
{
	Q_OBJECT
public:
	explicit MyThread(QObject *parent = 0);

	
	void setFlag(bool flag = true);
	
	ROI_pars m_roipars;

public slots:
	void MyWork();     //线程处理函数定义
	void acceptROIS(ROI_pars m_pars);//接收主线程传递来的roi参数

signals:
	void singal_back();   //处理结果返回信号

private:
	int x, y, width, height;
	bool isStop;	//进程结束标志
	void getEdgeVal(); //边缘提取
	
};
#endif