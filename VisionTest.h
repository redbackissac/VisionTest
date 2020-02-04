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
	struct Display_Count       //���·�ͳ������
	{
		QString Since_Start;
		QString Since_End;
		QString Since;
		int16_t Total;
		int16_t Pass;
		int16_t Fail;
	}Display_Count_Data;

	struct Display_Count_Top   //�Ϸ�ͳ������
	{
		int16_t Total;
		int16_t Pass;
		int16_t Fail;
		int16_t Persent;
		int16_t CT;
	}Display_Count_Data_Top;

	struct Display_SysCondition  //ϵͳ״̬
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
	
	/*typedef struct node    //�����������ڵ�
	{  
		char data;
		struct node *next;
	}node;

	//������У�������׺Ͷ�βָ�룩
	typedef struct queue_link
	{
		node *front;
		node *rear;
	}que;

	//�ж϶����Ƿ�Ϊ��
	int EmptyQueue(que *q)
	{
		return q->front == NULL;
	}

	//����
	void InsertQueue(que *q, char data)
	{
		node *n = (node*)malloc(sizeof(node));
		if (n == NULL)//�ڴ����ʧ��
			return;		
		n->data = data;
		n->next = NULL;//β�巨������Ԫ��ָ���
		if (q->rear == NULL)
		{
			q->front = n;
			q->rear = n;
		}
		else
		{
			q->rear->next = n;  //��n��Ϊ��ǰ��β�������һ���
			q->rear = n;        //β��ָ��ָ��n
		}
	}

	//����
	void DeleteQueue(que *q)
	{
		node *n = q->front;
		if (q->front == NULL)  //�ж϶����Ƿ�Ϊ��
			return;
		if (q->front == q->rear)  //�ж��Ƿ�ֻ��һ��Ԫ��
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
	

	QString SysCond_belt_Left = "���ʹ�״̬";
	QString SysCond_turntable_Left = "ת��״̬";
	QString SysCond_load_Left = "������״̬";
	QString SysCond_ST1_Left = "ST1״̬";
	QString SysCond_ST2_Left = "ST2״̬";
	QString SysCond_ST3_Left = "ST3״̬";
	QString SysCond_ST4_Left = "ST4״̬";
	QString SysCond_ST5_Left = "ST5״̬";
	QString SysCond_ST6_Left = "ST6״̬";
	QString SysCond_ST7_Left = "ST7״̬";
	QString SysCond_ST8_Left = "ST8״̬";
	QString SysCond_blank_Left = "������״̬";
	QString SysCond_sys_Left = "ϵͳ״̬";

	QString SysCond_belt_Right = "���Ͻ���";
	QString SysCond_turntable_Right = "���Ͳ�������";
	QString SysCond_load_Right = "���ս���";
	QString SysCond_ST1_Right = "�������";
	QString SysCond_ST2_Right = "�������";
	QString SysCond_ST3_Right = "�������";
	QString SysCond_ST4_Right = "�������";
	QString SysCond_ST5_Right = "�������";
	QString SysCond_ST6_Right = "�������";
	QString SysCond_ST7_Right = "�������";
	QString SysCond_ST8_Right = "�������";
	QString SysCond_blank_Right = "�����߳����";
	QString SysCond_sys_Right = "ϵͳֹͣ,ֹͣ����";


	void sys_Test(int i);   //������
	

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
