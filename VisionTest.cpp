#include "VisionTest.h"
#pragma execution_character_set("utf-8")

/*
主界面实现函数
*/
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Timer_Init();       //定时器初始化
	Display_Total();    //统计数据显示

}

/*
定时器初始化
*/
void MainWindow::Timer_Init()
{
	/***********************************用于控制统计数据显示，每10ms刷新*********************************/
	Display_Timer = new QTimer();
	Display_Timer->setInterval(10);       //设置定时周期，单位：毫秒
	Display_Timer->start();
	connect(Display_Timer, SIGNAL(timeout()), this, SLOT(on_Display_Timer_timeout()));
}

/*
统计数据
*/
void MainWindow::Display_Total()
{
	/**************************************右下方统计容器************************************************/
	Display_GroupBox = new QGroupBox(this);
	Display_GroupBox->setObjectName(QString::fromUtf8("Display_GroupBox"));
	Display_GroupBox->setGeometry(QRect(1340, 740, 530, 80));	
	Display_GroupBox->setStyleSheet("QGroupBox{\n"
		"\n"
		"border: 0px solid;\n"
		"}");

	/******************************************Reset 按钮************************************************/
	Reset = new QPushButton(Display_GroupBox);
	Reset->setGeometry(QRect(0, 20, 110, 40));
	Reset->setText("Reset");
	QFont font_Reset;
	font_Reset.setFamily(QString::fromUtf8("AcadEref"));
	font_Reset.setPointSize(15);
	font_Reset.setBold(true);
	font_Reset.setWeight(75);
	Reset->setFont(font_Reset);
	Reset->setAutoFillBackground(false);
	Reset->setStyleSheet("QPushButton{\n"
		"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(134, 198, 233, 255), stop:0.5 rgba(175, 215, 234, 255));\n"
		"border: 1px solid rgb(124, 124, 124);\n"
		"border-radius:8px;\n"
		"}\n"
		"QPushButton:hover{\n"
		"background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(181, 225, 250, 255), stop:0.5 rgba(222, 242, 251, 255));\n"
		"  border-radius:8px;\n"
		"  border: 1px solid #3C80B1;\n"
		"}\n"
		"QPushButton:pressed{\n"
		" background-color: qconicalgradient(cx:0.5, cy:0.522909, angle:179.9, stop:0.494318 rgba(214, 214, 214, 255), stop:0.5 rgba(236, 236, 236, 255));\n"
		"  border-radius:8px;\n"
		"  border: 1px solid #5F92B2;\n"
		"}");
	connect(Reset, SIGNAL(clicked()), this, SLOT(on_Reset_clicked()));     //连接槽函数on_Reset_clicked()
	/*************************************************右下方表格*************************************************/
	Display_Count_Data.Since_Start=Display_Time->currentTime().toString("hh:mm:ss");
	Display_Count_Data.Total = 1000;
	Display_Count_Data.Pass = 800;
	Display_Count_Data.Fail = 200;

	Display_WidgetView = new QTableView(Display_GroupBox);
	Display_Model = new QStandardItemModel(Display_GroupBox);
	Display_WidgetView->setGeometry(QRect(130, 0, 400, 80));

	Display_Model->setItem(0, 0, new QStandardItem("Since"));	
	Display_Model->setItem(0, 1, new QStandardItem("Total"));
	Display_Model->setItem(0, 2, new QStandardItem("Pass"));
	Display_Model->setItem(0, 3, new QStandardItem("Fail"));	
	for (int i = 0; i < 4; i++)
	{
		Display_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);
		Display_Model->item(0, i)->setFlags(Qt::ItemIsEditable & Qt::ItemIsSelectable);
	}
	QFont font_WidgetView;
	font_WidgetView.setPointSize(11);
	font_WidgetView.setBold(false);
	font_WidgetView.setWeight(50);
	Display_WidgetView->setFont(font_WidgetView);
	Display_WidgetView->setStyleSheet("QTableView{\n"
		"background-color:rgba(255, 255, 255,0);\n"
		"color:rgb(255,255,255);\n"
		"gridline-color: rgb(255, 255,255);\n"
		"border-radius:0\n"
		"px;\n"
		"}\n"
		"");

    Display_WidgetView->setLineWidth(0);
	Display_WidgetView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Display_WidgetView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Display_WidgetView->setAutoScroll(false);
	Display_WidgetView->setAutoScrollMargin(10);
	Display_WidgetView->setSelectionMode(QAbstractItemView::NoSelection);
	Display_WidgetView->setTextElideMode(Qt::ElideLeft);
	Display_WidgetView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑

	Display_WidgetView->horizontalHeader()->setVisible(false);
	Display_WidgetView->horizontalHeader()->setMinimumSectionSize(15);
	Display_WidgetView->verticalHeader()->setVisible(false);
	Display_WidgetView->verticalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	Display_WidgetView->verticalHeader()->setDefaultSectionSize(40);
	Display_WidgetView->verticalHeader()->setMinimumSectionSize(5);

	Display_WidgetView->setModel(Display_Model);

	Display_WidgetView->setColumnWidth(0, 202);
	Display_WidgetView->setColumnWidth(1, 66);
	Display_WidgetView->setColumnWidth(2, 66);
	Display_WidgetView->setColumnWidth(3, 66);

	/****************************************标题栏表格*******************************/

	Display_Count_Data_Top.Total = 0;
	Display_Count_Data_Top.Pass = 0;
	Display_Count_Data_Top.Fail = 0;
	Display_Count_Data_Top.Persent = 0;
	Display_Count_Data_Top.CT = 4;

	Display_WidgetView_Top = new QTableView(this);
	Display_Model_Top = new QStandardItemModel(this);
	Display_WidgetView_Top->setGeometry(QRect(560, 60, 800, 40));

	Display_Model_Top->setItem(0, 0, new QStandardItem("总数"));
	Display_Model_Top->setItem(0, 2, new QStandardItem("合格数"));
	Display_Model_Top->setItem(0, 4, new QStandardItem("不合格数"));
	Display_Model_Top->setItem(0, 6, new QStandardItem("合格率"));
	Display_Model_Top->setItem(0, 8, new QStandardItem("CT"));
	Display_Model_Top->setItem(0, 1, new QStandardItem(QString::number(Display_Count_Data_Top.Total, 10)));
	Display_Model_Top->setItem(0, 3, new QStandardItem(QString::number(Display_Count_Data_Top.Pass, 10)));
	Display_Model_Top->setItem(0, 5, new QStandardItem(QString::number(Display_Count_Data_Top.Fail, 10)));
	Display_Model_Top->setItem(0, 7, new QStandardItem(QString("%1%").arg(QString("%1").arg(Display_Count_Data_Top.Persent))));
	Display_Model_Top->setItem(0, 9, new QStandardItem(QString::number(Display_Count_Data_Top.CT, 10)));

	for (int i = 0; i < 10; i++)
	{
		Display_Model_Top->item(0, i)->setTextAlignment(Qt::AlignCenter);
		Display_Model_Top->item(0, i)->setFlags(Qt::ItemIsEditable & Qt::ItemIsSelectable);
	}

	QFont font_WidgetView_Top;
	font_WidgetView_Top.setPointSize(11);
	font_WidgetView_Top.setBold(true);
	font_WidgetView_Top.setWeight(50);
	Display_WidgetView_Top->setFont(font_WidgetView_Top);
	Display_WidgetView_Top->setStyleSheet("QTableView{\n"
		"background-color:rgba(255, 255, 255,0);\n"
		"color:rgb(0,0,0);\n"
		"border-color:rgba(0,0,0,0);\n"
		"border-radius:0px;\n"		
		"}");
	Display_WidgetView_Top->setShowGrid(false);    //隐藏边框

	Display_WidgetView_Top->setLineWidth(0);
	Display_WidgetView_Top->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Display_WidgetView_Top->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Display_WidgetView_Top->setAutoScroll(false);
	Display_WidgetView_Top->setAutoScrollMargin(10);
	Display_WidgetView_Top->setSelectionMode(QAbstractItemView::NoSelection);
	Display_WidgetView_Top->setTextElideMode(Qt::ElideLeft);
	Display_WidgetView_Top->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑

	Display_WidgetView_Top->horizontalHeader()->setVisible(false);
	Display_WidgetView_Top->horizontalHeader()->setMinimumSectionSize(15);
	Display_WidgetView_Top->verticalHeader()->setVisible(false);
	Display_WidgetView_Top->verticalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	Display_WidgetView_Top->verticalHeader()->setDefaultSectionSize(40);
	Display_WidgetView_Top->verticalHeader()->setMinimumSectionSize(5);

	Display_WidgetView_Top->setModel(Display_Model_Top);

	for (int i = 0; i<10; i++)                             //设置列宽
		Display_WidgetView_Top->setColumnWidth(i, 80);	
	


	/*****************************************系统状态***********************************/
	//左栏
    SysCond_belt_Left = " ";
    SysCond_turntable_Left = " ";
	SysCond_load_Left = " ";
    SysCond_ST1_Left = " ";
	SysCond_ST2_Left = " ";
	SysCond_ST3_Left = " ";
	SysCond_ST4_Left = " ";
	SysCond_ST5_Left = " ";
	SysCond_ST6_Left = " ";
	SysCond_ST7_Left = " ";
	SysCond_ST8_Left = " ";
	SysCond_blank_Left = " ";
	SysCond_sys_Left = " ";

	Display_Queue_Left->EnQueue(&SysCond_belt_Left);
	Display_Queue_Left->EnQueue(&SysCond_turntable_Left);
	Display_Queue_Left->EnQueue(&SysCond_load_Left);
	Display_Queue_Left->EnQueue(&SysCond_ST1_Left);
	Display_Queue_Left->EnQueue(&SysCond_ST2_Left);
	Display_Queue_Left->EnQueue(&SysCond_ST3_Left);

	Display_SysCond.line_1_Left = **(Display_Queue_Left->base + Display_Queue_Left->front);
	Display_SysCond.line_2_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 1 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_3_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 2 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_4_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 3 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_5_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 4 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_6_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 5 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);

	//右栏

		SysCond_belt_Right = " ";
		SysCond_turntable_Right = " ";
		SysCond_load_Right = " ";
		SysCond_ST1_Right = " ";
		SysCond_ST2_Right = " ";
		SysCond_ST3_Right = " ";
		SysCond_ST4_Right = " ";
		SysCond_ST5_Right = " ";
		SysCond_ST6_Right = " ";
		SysCond_ST7_Right = " ";
		SysCond_ST8_Right = " ";
		SysCond_blank_Right = " ";
		SysCond_sys_Right = " ";
;

	Display_Queue_Right->EnQueue(&SysCond_belt_Right);
	Display_Queue_Right->EnQueue(&SysCond_turntable_Right);
	Display_Queue_Right->EnQueue(&SysCond_load_Right);
	Display_Queue_Right->EnQueue(&SysCond_ST1_Right);
	Display_Queue_Right->EnQueue(&SysCond_ST2_Right);
	Display_Queue_Right->EnQueue(&SysCond_ST3_Right);

	Display_SysCond.line_1_Right = **(Display_Queue_Right->base + Display_Queue_Right->front);
	Display_SysCond.line_2_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 1 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_3_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 2 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_4_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 3 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_5_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 4 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_6_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 5 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);

	//系统整体显示表格
	Display_SysCondition = new QTableView(this);
	Display_Model_SysCondition = new QStandardItemModel(this);
	Display_SysCondition->setGeometry(QRect(50, 550, 460, 390));

	Display_Model_SysCondition->setItem(0, 0, new QStandardItem(Display_SysCond.line_1_Left));
	Display_Model_SysCondition->setItem(1, 0, new QStandardItem(Display_SysCond.line_2_Left));
	Display_Model_SysCondition->setItem(2, 0, new QStandardItem(Display_SysCond.line_3_Left));
	Display_Model_SysCondition->setItem(3, 0, new QStandardItem(Display_SysCond.line_4_Left));
	Display_Model_SysCondition->setItem(4, 0, new QStandardItem(Display_SysCond.line_5_Left));
	Display_Model_SysCondition->setItem(5, 0, new QStandardItem(Display_SysCond.line_6_Left));

	Display_Model_SysCondition->setItem(0, 1, new QStandardItem(Display_SysCond.line_1_Right));
	Display_Model_SysCondition->setItem(1, 1, new QStandardItem(Display_SysCond.line_2_Right));
	Display_Model_SysCondition->setItem(2, 1, new QStandardItem(Display_SysCond.line_3_Right));
	Display_Model_SysCondition->setItem(3, 1, new QStandardItem(Display_SysCond.line_4_Right));
	Display_Model_SysCondition->setItem(4, 1, new QStandardItem(Display_SysCond.line_5_Right));
	Display_Model_SysCondition->setItem(5, 1, new QStandardItem(Display_SysCond.line_6_Right));
	
	for (int i = 0; i < 6; i++)
		for(int j = 0;j < 2;j++)
		{
			//Display_Model_SysCondition->item(i, j)->setTextAlignment(Qt::AlignCenter);
			Display_Model_SysCondition->item(i, j)->setFlags(Qt::ItemIsEditable & Qt::ItemIsSelectable);
		}
	


	QFont font_SysCondition;
	font_SysCondition.setPointSize(11);
	font_SysCondition.setBold(true);
	font_SysCondition.setWeight(50);
	Display_SysCondition->setFont(font_SysCondition);
	Display_SysCondition->setStyleSheet("QTableView{\n"
		"background-color:rgba(255, 255, 255,0);\n"
		"color:rgb(255,255,255);\n"		
		"gridline-color: rgb(255, 255,255);\n"
		"border-radius:0px;\n"
		"}");

	Display_SysCondition->setLineWidth(0);
	Display_SysCondition->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Display_SysCondition->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Display_SysCondition->setAutoScroll(false);
	Display_SysCondition->setAutoScrollMargin(10);
	Display_SysCondition->setSelectionMode(QAbstractItemView::NoSelection);
	Display_SysCondition->setTextElideMode(Qt::ElideLeft);
	Display_SysCondition->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑

	Display_SysCondition->horizontalHeader()->setVisible(false);
	Display_SysCondition->horizontalHeader()->setMinimumSectionSize(15);
	Display_SysCondition->verticalHeader()->setVisible(false);
	Display_SysCondition->verticalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	Display_SysCondition->verticalHeader()->setDefaultSectionSize(40);
	Display_SysCondition->verticalHeader()->setMinimumSectionSize(5);

	Display_SysCondition->setModel(Display_Model_SysCondition);


	Display_SysCondition->setColumnWidth(0, 100);   //设置列宽
	Display_SysCondition->setColumnWidth(1, 250);

}

void MainWindow::on_Reset_clicked()
{
	
	Display_Count_Data.Since_Start = Display_Time->currentTime().toString("hh:mm:ss");
	Display_Count_Data.Total = 0;
	Display_Count_Data.Pass = 0;
	Display_Count_Data.Fail = 0;
}
/*
定时器中断函数，显示统计数据
*/
void MainWindow::on_Display_Timer_timeout()
{
	i++;
	/************************************************右下方统计显示内容************************************************/
	Display_Count_Data.Since_End = Display_Time->currentTime().toString("hh:mm:ss");
	Display_Count_Data.Since = QString("%1 - %2 ").arg(Display_Count_Data.Since_Start).arg(Display_Count_Data.Since_End);
	Display_Model->setItem(1, 0, new QStandardItem(Display_Count_Data.Since));
	Display_Model->setItem(1, 1, new QStandardItem(QString::number(Display_Count_Data.Total, 10)));
	Display_Model->setItem(1, 2, new QStandardItem(QString::number(Display_Count_Data.Pass, 10)));
	Display_Model->setItem(1, 3, new QStandardItem(QString::number(Display_Count_Data.Fail, 10)));

	for (int i = 0; i < 4; i++)
	{
		Display_Model->item(1, i)->setTextAlignment(Qt::AlignCenter);
		Display_Model->item(0, i)->setFlags(Qt::ItemIsEditable & Qt::ItemIsSelectable);
	}


	/****************************************************上方显示内容************************************************/	

	Display_Count_Data_Top.Total = 500;
	Display_Count_Data_Top.Pass = 431;
	if(Display_Count_Data_Top.Total !=0 )
	{ 
		Display_Count_Data_Top.Persent = Display_Count_Data_Top.Pass * 100 / Display_Count_Data_Top.Total;
	}
	else Display_Count_Data_Top.Persent = 0;


	for (int i=0;i<10;i=i+2)                                //清空原来表格内容
		Display_Model_Top->takeItem(0, i+1);	

	Display_Model_Top->setItem(0, 1, new QStandardItem(QString::number(Display_Count_Data_Top.Total, 10)));
	Display_Model_Top->setItem(0, 3, new QStandardItem(QString::number(Display_Count_Data_Top.Pass, 10)));
	Display_Model_Top->setItem(0, 5, new QStandardItem(QString::number(Display_Count_Data_Top.Fail, 10)));
	Display_Model_Top->setItem(0, 7, new QStandardItem(QString("%1%").arg(QString("%1").arg(Display_Count_Data_Top.Persent))));
	Display_Model_Top->setItem(0, 9, new QStandardItem(QString::number(Display_Count_Data_Top.CT, 10)));
	
	for (int i = 0; i < 10; i++)
	{
		Display_Model_Top->item(0, i)->setTextAlignment(Qt::AlignCenter);
		Display_Model_Top->item(0, i)->setFlags(Qt::ItemIsEditable & Qt::ItemIsSelectable);
	}

	/*********************系统状态栏******************************************/
	//左栏
	Display_SysCond.line_1_Left = **(Display_Queue_Left->base + Display_Queue_Left->front);
	Display_SysCond.line_2_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 1 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_3_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 2 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_4_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 3 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_5_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 4 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	Display_SysCond.line_6_Left = **(Display_Queue_Left->base + (Display_Queue_Left->front + 5 + Display_Queue_Left->QueueSize) % Display_Queue_Left->QueueSize);
	//右栏
	Display_SysCond.line_1_Right = **(Display_Queue_Right->base + Display_Queue_Right->front);
	Display_SysCond.line_2_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 1 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_3_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 2 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_4_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 3 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_5_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 4 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);
	Display_SysCond.line_6_Right = **(Display_Queue_Right->base + (Display_Queue_Right->front + 5 + Display_Queue_Right->QueueSize) % Display_Queue_Right->QueueSize);

	
	for (int i = 0; i<6; i++)                                //清空原来表格内容
		Display_Model_SysCondition->takeItem(i, 0);
	for (int i = 0; i<6; i++)                                //清空原来表格内容
		Display_Model_SysCondition->takeItem(i, 1);

	//左栏
	Display_Model_SysCondition->setItem(0, 0, new QStandardItem(Display_SysCond.line_1_Left));
	Display_Model_SysCondition->setItem(1, 0, new QStandardItem(Display_SysCond.line_2_Left));
	Display_Model_SysCondition->setItem(2, 0, new QStandardItem(Display_SysCond.line_3_Left));
	Display_Model_SysCondition->setItem(3, 0, new QStandardItem(Display_SysCond.line_4_Left));
	Display_Model_SysCondition->setItem(4, 0, new QStandardItem(Display_SysCond.line_5_Left));
	Display_Model_SysCondition->setItem(5, 0, new QStandardItem(Display_SysCond.line_6_Left));
	//右栏
	Display_Model_SysCondition->setItem(0, 1, new QStandardItem(Display_SysCond.line_1_Right));
	Display_Model_SysCondition->setItem(1, 1, new QStandardItem(Display_SysCond.line_2_Right));
	Display_Model_SysCondition->setItem(2, 1, new QStandardItem(Display_SysCond.line_3_Right));
	Display_Model_SysCondition->setItem(3, 1, new QStandardItem(Display_SysCond.line_4_Right));
	Display_Model_SysCondition->setItem(4, 1, new QStandardItem(Display_SysCond.line_5_Right));
	Display_Model_SysCondition->setItem(5, 1, new QStandardItem(Display_SysCond.line_6_Right));





	/**************************************测试用*************************************/
	if (i >= 100)
	{		
		Display_Queue_Left->DeQueue();
		Display_Queue_Right->DeQueue();
		sys_Test(j);
		Display_Count_Data.Total++;
		i = 0;
		j++;
	}

	
}

void MainWindow::sys_Test(int i)
{
	switch (i % 13)
	{
	case 0:
		SysCond_belt_Left = "传送带状态";
		Display_Queue_Left->EnQueue(&SysCond_belt_Left);
		SysCond_belt_Right = QString("%1 清料界面").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_belt_Right);
		break;
	case 1:
		SysCond_turntable_Left = "转盘状态";
		Display_Queue_Left->EnQueue(&SysCond_turntable_Left);
		SysCond_turntable_Right = QString("%1 发送测量命令").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_turntable_Right);
		break;
	case 2:		
		SysCond_load_Left = "上料轴状态";
		Display_Queue_Left->EnQueue(&SysCond_load_Left);
		SysCond_load_Right = QString("%1 拍照结束").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_load_Right);
		break;
	case 3:
		SysCond_ST1_Left = "ST1状态";		
		Display_Queue_Left->EnQueue(&SysCond_ST1_Left);
		SysCond_ST1_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST1_Right);
		break;
	case 4:
		SysCond_ST2_Left = "ST2状态";
		Display_Queue_Left->EnQueue(&SysCond_ST2_Left);
		SysCond_ST2_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST2_Right);
		break;
	case 5:
		SysCond_ST3_Left = "ST3状态";
		Display_Queue_Left->EnQueue(&SysCond_ST3_Left);
		SysCond_ST3_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST3_Right);
		break;
	case 6:
		SysCond_ST4_Left = "ST4状态";
		Display_Queue_Left->EnQueue(&SysCond_ST4_Left);
		SysCond_ST4_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST4_Right);
		break;
	case 7:
		SysCond_ST5_Left = "ST5状态";
		Display_Queue_Left->EnQueue(&SysCond_ST5_Left);
		SysCond_ST5_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST5_Right);
		break;
	case 8:
		SysCond_ST6_Left = "ST6状态";
		Display_Queue_Left->EnQueue(&SysCond_ST6_Left);
		SysCond_ST6_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST6_Right);
		break;
	case 9:
		SysCond_ST7_Left = "ST7状态";
		Display_Queue_Left->EnQueue(&SysCond_ST7_Left);
		SysCond_ST7_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST7_Right);		
		break;
	case 10:
		SysCond_ST8_Left = "ST8状态";
		Display_Queue_Left->EnQueue(&SysCond_ST8_Left);
		SysCond_ST8_Right = QString("%1 测量完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_ST8_Right);
		break;
	case 11:
		SysCond_blank_Left = "下料轴状态";
		Display_Queue_Left->EnQueue(&SysCond_blank_Left);
		SysCond_blank_Right = QString("%1 下料线程完成").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_blank_Right);
		break;
	case 12:
		SysCond_sys_Left = "系统状态";
		Display_Queue_Left->EnQueue(&SysCond_sys_Left);
		SysCond_sys_Right = QString("%1 系统停止,停止工作").arg(Display_Time->currentTime().toString("hh:mm:ss"));
		Display_Queue_Right->EnQueue(&SysCond_sys_Right);
		break;
	default:
		break;
	}
}