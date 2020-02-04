#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisionTest.h"
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include<qtimer.h>
#include<qdatetime.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CQueue.h"
#include "CQueue.cpp"
#include <iostream>



class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);		
	struct Display_Count       //右下方统计数据
	{
		QString Since_Start;
		QString Since_End;
		QString Since;
		int16_t Total;
		int16_t Pass;
		int16_t Fail;
	}Display_Count_Data;

	struct Display_Count_Top   //上方统计数据
	{
		int16_t Total;
		int16_t Pass;
		int16_t Fail;
		int16_t Persent;
		int16_t CT;
	}Display_Count_Data_Top;

	struct Display_SysCondition  //系统状态
	{
		QString line_1_Left;
		QString line_2_Left;
		QString line_3_Left;
		QString line_4_Left;
		QString line_5_Left;
		QString line_6_Left;

		QString line_1_Right;
		QString line_2_Right;
		QString line_3_Right;
		QString line_4_Right;
		QString line_5_Right;
		QString line_6_Right;

	}Display_SysCond;
	
	/*typedef struct node    //定义队列链表节点
	{  
		char data;
		struct node *next;
	}node;

	//定义队列（保存队首和队尾指针）
	typedef struct queue_link
	{
		node *front;
		node *rear;
	}que;

	//判断队列是否为空
	int EmptyQueue(que *q)
	{
		return q->front == NULL;
	}

	//入列
	void InsertQueue(que *q, char data)
	{
		node *n = (node*)malloc(sizeof(node));
		if (n == NULL)//内存分配失败
			return;		
		n->data = data;
		n->next = NULL;//尾插法，插入元素指向空
		if (q->rear == NULL)
		{
			q->front = n;
			q->rear = n;
		}
		else
		{
			q->rear->next = n;  //让n成为当前的尾部结点下一结点
			q->rear = n;        //尾部指针指向n
		}
	}

	//出队
	void DeleteQueue(que *q)
	{
		node *n = q->front;
		if (q->front == NULL)  //判断队列是否为空
			return;
		if (q->front == q->rear)  //判断是否只有一个元素
		{
			q->front = NULL;
			q->rear = NULL;
		}
		else
		{
			q->front = q->front->next;
			free(n);
		}
	}*/
	

	QString SysCond_belt_Left = "传送带状态";
	QString SysCond_turntable_Left = "转盘状态";
	QString SysCond_load_Left = "上料轴状态";
	QString SysCond_ST1_Left = "ST1状态";
	QString SysCond_ST2_Left = "ST2状态";
	QString SysCond_ST3_Left = "ST3状态";
	QString SysCond_ST4_Left = "ST4状态";
	QString SysCond_ST5_Left = "ST5状态";
	QString SysCond_ST6_Left = "ST6状态";
	QString SysCond_ST7_Left = "ST7状态";
	QString SysCond_ST8_Left = "ST8状态";
	QString SysCond_blank_Left = "下料轴状态";
	QString SysCond_sys_Left = "系统状态";

	QString SysCond_belt_Right = "清料界面";
	QString SysCond_turntable_Right = "发送测量命令";
	QString SysCond_load_Right = "拍照结束";
	QString SysCond_ST1_Right = "测量完成";
	QString SysCond_ST2_Right = "测量完成";
	QString SysCond_ST3_Right = "测量完成";
	QString SysCond_ST4_Right = "测量完成";
	QString SysCond_ST5_Right = "测量完成";
	QString SysCond_ST6_Right = "测量完成";
	QString SysCond_ST7_Right = "测量完成";
	QString SysCond_ST8_Right = "测量完成";
	QString SysCond_blank_Right = "下料线程完成";
	QString SysCond_sys_Right = "系统停止,停止工作";


	void sys_Test(int i);   //测试用
	

	int i = 0;
	int j = 0;
private slots:
	void on_Reset_clicked();
	void on_Display_Timer_timeout();


private:
	QPushButton *Reset;
	QGroupBox *Display_GroupBox;	
	QTableView *Display_WidgetView;
	QStandardItemModel *Display_Model;
	QTableView *Display_WidgetView_Top;
	QStandardItemModel *Display_Model_Top;
	QTableView *Display_SysCondition;
	QStandardItemModel *Display_Model_SysCondition ;
	QTimer *Display_Timer;
	QTime *Display_Time;
    CQueue<QString> *Display_Queue_Left = new CQueue<QString>(6);
	CQueue<QString> *Display_Queue_Right = new CQueue<QString>(6);
	void Display_Total();
	void Timer_Init();
	Ui::VisionTestClass ui;
};
