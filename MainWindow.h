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
#include "singlebattery.h"
#include "Setting.h"

using namespace cv;

#define LINES_OF_SYSCOND 8 //系统信息显示的行数

namespace Ui {
	class MainWindow;
}
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	Mat src, dst;
	QImage dstImg;	
	ROI_pars m_roipars;	//存储从配置文件中读取的ROI参数

	int TurnTable_ZeroPos = 0;
	MainWindow(QWidget *parent = Q_NULLPTR);	//主界面构造函数	
	struct Count_Bottom          //右下方统计数据
	{
		QString Since_Start;     //起始时间
		QString Since_End;       //结束时间
		QString Since;           //时间区间,[Since_Start,Since_End]
		int16_t Total;           //时间区间Since内测量总数
		int16_t Pass;            //时间区间Since内测量合格数目
		int16_t Fail;            //时间区间Since内测量不合格数目
	}Count_Bottom_Data;

	struct Count_Top             //上方统计数据
	{
		int16_t Total;           //系统运行期间测量总数
		int16_t Pass;            //系统运行期间测量合格数目
		int16_t Fail;            //系统运行期间测量不合格数目
		int16_t Persent;         //系统运行期间测量合格率
		int16_t CT;              //我也不知道是啥玩意
	}Count_Top_Data;

	QList<QString>  Sys_Cond_Left;  //系统状态左栏
	QList<QString>  Sys_Cond_Right; //系统状态右栏

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
	
	QImage Mat2QImage(Mat &mat);                    //将Mat类型转换为QImage类型
	void slot_handle_finish();                      //处理多线程结束
	int i = 0;
	int j = 0;

signals:
	void StartThread();                             //多线程开始信号
	void sendparameterstomythread(ROI_pars pars);        //将roi参数传入子线程

//私有槽函数
private slots:
	void on_Reset_clicked();                        //统计信息复位
	void on_Open_clicked();                         //打开图片按钮
	void on_Stop_clicked();                         //停止按钮
	void on_Display_Timer_timeout();                //定时器中断服务函数
	void on_Setting_clicked();                      //用于打开设置界面
	void on_Import_clicked();                       //加载ROI参数	

private:
	
	Setting sss;
	QThread *subthread;                                          //子线程容器
	MyThread *m_thread;                                          //自定义线程	

	MyMovie *mymovie;                                            //转盘动画

	QTimer *Timer_Control;                                        //用于控制数据更新的定时器
	QTime *Time_Current;                                          //当前时间	

	QStandardItemModel *Count_Bottom_Model;                       //下方统计数据标准数据模型	
	QStandardItemModel *Count_Top_Model;                          //上方统计数据标准数据模型

	QStandardItemModel *Sys_Model ;                               //系统状态标准数据模型	
    CQueue<QString> *SysCond_Queue_Left = new CQueue<QString>(LINES_OF_SYSCOND); //系统状态栏左栏队列
	CQueue<QString> *SysCond_Queue_Right = new CQueue<QString>(LINES_OF_SYSCOND);//系统状态栏右栏队列

	QStandardItemModel *Test_Inf_Failed_Model;                   //检测不合格标准数据模型
	QStandardItemModel *Test_Inf_Failed_Title_Model;             //检测不合格标题栏标准数据模型

	QStandardItemModel *Test_Inf_Testing_Model;                   //正在检测标准数据模型
	QStandardItemModel *Test_Inf_Testing_Title_Model;             //检测不合格标题栏标准数据模型

	QGraphicsScene *sence;     //创建显示电池图像的图形场景

	void Timer_Init();
	void sys_Test(int i);                           //测试用
	void Count_Bottom();                            //下方统计数据初始化
	void Count_Bottom_Update();                     //下方统计数据更新
	void Count_Top();                               //标题栏统计数据初始化
	void Count_Top_Update();                        //标题栏统计数据更新
	void System_Condition();                        //系统状态初始化
	void System_Condition_Update();                 //系统状态更新
	void Test_Inf();                                //检测信息

	Ui::MainWindowClass ui;
};
