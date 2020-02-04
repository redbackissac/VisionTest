#pragma once

#include <stdlib.h>
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <qtimer.h>
#include <qdatetime.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QScrollArea>
#include "CQueue.h"
#include "CQueue.cpp"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTextBrowser>
#include <QTextStream>
#include <QThread>
#include <QMetaType>
#include <iostream>
#include <string>
#include <QFiledialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <opencv2\opencv.hpp>
#include "mythread.h"
#include "MyMovie.h"
#include "CImgProcess.h"
#include "Setting.h"

using namespace cv;

namespace Ui {
	class MainWindow;
}
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	Mat src, dst;
	QImage dstImg;	
	ROI_pars m_roipars;	

	int TurnTable_ZeroPos = 0;
	MainWindow(QWidget *parent = Q_NULLPTR);		
	struct Count_Bottom          //���·�ͳ������
	{
		QString Since_Start;     //��ʼʱ��
		QString Since_End;       //����ʱ��
		QString Since;           //ʱ������,[Since_Start,Since_End]
		int16_t Total;           //ʱ������Since�ڲ�������
		int16_t Pass;            //ʱ������Since�ڲ����ϸ���Ŀ
		int16_t Fail;            //ʱ������Since�ڲ������ϸ���Ŀ
	}Count_Bottom_Data;

	struct Count_Top             //�Ϸ�ͳ������
	{
		int16_t Total;           //ϵͳ�����ڼ��������
		int16_t Pass;            //ϵͳ�����ڼ�����ϸ���Ŀ
		int16_t Fail;            //ϵͳ�����ڼ�������ϸ���Ŀ
		int16_t Persent;         //ϵͳ�����ڼ�����ϸ���
		int16_t CT;              //��Ҳ��֪����ɶ����
	}Count_Top_Data;

	struct Sys_Condition         //ϵͳ״̬
	{
		QString line_1_Left;
		QString line_2_Left;
		QString line_3_Left;
		QString line_4_Left;
		QString line_5_Left;
		QString line_6_Left;
		QString line_7_Left;
		QString line_8_Left;

		QString line_1_Right;
		QString line_2_Right;
		QString line_3_Right;
		QString line_4_Right;
		QString line_5_Right;
		QString line_6_Right;
		QString line_7_Right;
		QString line_8_Right;

	}Sys_Cond;

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


	void sys_Test(int i);                           //������
	void Count_Bottom();                            //�·�ͳ�����ݳ�ʼ��
	void Count_Bottom_Update();                     //�·�ͳ�����ݸ���
	void Count_Top();                               //������ͳ�����ݳ�ʼ��
	void Count_Top_Update();                        //������ͳ�����ݸ���
	void System_Condition();                        //���ϵͳ״̬��ʼ��
	void System_Condition_Update();                 //ϵͳ״̬����
	void Test_Inf();                                //�����Ϣ
	
	QImage Mat2QImage(Mat &mat);                    //��Mat����ת��ΪQImage����
	void slot_handle_finish();                      //������߳̽���
	int i = 0;
	int j = 0;

signals:
	void StartThread();                             //���߳̿�ʼ�ź�
	void sendparameterstomythread(ROI_pars pars);        //��roi�����������߳�

//˽�вۺ���
private slots:
	void on_Reset_clicked();                        //reset��ť����    
	void on_Open_clicked();                         //��ͼƬ��ť
	void on_Stop_clicked();                         //ֹͣ��ť
	void on_Display_Timer_timeout();                //��ʱ���жϷ�����
	void on_Setting_clicked();                      //���ڴ����ý���
	void on_Import_clicked();                       //����ROI����
	

private:
	
	Setting sss;
	MyThread *m_thread;                                          //�Զ����߳�
	QThread *subthread;                                          //���߳�����

	MyMovie *mymovie;                                            //ת�̶���

	QTimer *Timer_Control;                                        //���ڿ������ݸ��µĶ�ʱ��
	QTime *Time_Current;                                          //��ǰʱ��		
	QStandardItemModel *Count_Bottom_Model;                       //�·�ͳ�����ݱ�׼����ģ��	
	QStandardItemModel *Count_Top_Model;                          //�Ϸ�ͳ�����ݱ�׼����ģ��
	QTabWidget *Test_Inf_Tab;
	QWidget *Sys_Tab_Widget;
	QScrollArea *Sys_ScrollArea;                                 //ϵͳ״̬������
	QWidget *Sys_Widget;                                         //ϵͳ״̬�������ڲ�����
	QTableView *Sys_Table;                                        //ϵͳ״̬���
	QStandardItemModel *Sys_Model ;                               //ϵͳ״̬��׼����ģ��	
    CQueue<QString> *SysCond_Queue_Left = new CQueue<QString>(8); //ϵͳ״̬����������
	CQueue<QString> *SysCond_Queue_Right = new CQueue<QString>(8);//ϵͳ״̬����������
	
	QWidget *Test_Inf_Widget;	
	QWidget *Test_Inf_Testing;
	QWidget *Test_Inf_Failed;




	QScrollArea *Test_Inf_Failed_ScrollArea;                     //��ⲻ�ϸ������
	QWidget *Test_Inf_Failed_Widget;                             //��ⲻ�ϸ�������ڲ�����
	QTableView *Test_Inf_Failed_TableView;                       //��ⲻ�ϸ���
	QStandardItemModel *Test_Inf_Failed_Model;                   //��ⲻ�ϸ��׼����ģ��
	QTableView *Test_Inf_Failed_Title_TableView;                 //��ⲻ�ϸ���������
	QStandardItemModel *Test_Inf_Failed_Title_Model;             //��ⲻ�ϸ��������׼����ģ��

	QScrollArea *Test_Inf_Testing_ScrollArea;                     //���ڼ�������
	QWidget *Test_Inf_Testing_Widget;                             //���ڼ��������ڲ�����
	QTableView *Test_Inf_Testing_TableView;                       //���ڼ����
	QStandardItemModel *Test_Inf_Testing_Model;                   //���ڼ���׼����ģ��
	QTableView *Test_Inf_Testing_Title_TableView;                 //��ⲻ�ϸ���������
	QStandardItemModel *Test_Inf_Testing_Title_Model;             //��ⲻ�ϸ��������׼����ģ��	


	QGraphicsScene *sence;     //������ʾ���ͼ���ͼ�γ���

	void Timer_Init();
	Ui::MainWindowClass ui;
};
