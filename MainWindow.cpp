#include "MainWindow.h"

#pragma execution_character_set("utf-8")
/*
主界面实现函数
*/
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	/*界面初始化*/
	
	ui.setupUi(this);
	this->resize(1920,1080);	
	/*定时器初始化*/
	Timer_Init();  
	/*下方统计数据*/
	Count_Bottom();	
	/*标题栏统计数据*/
	Count_Top();
	/*系统状态*/
	Test_Inf();
	System_Condition();
	mymovie = new MyMovie(this);
	mymovie->Init(400,400,2,0x0f);
	mymovie->move(150, 450);
	sence = new QGraphicsScene;              //创建显示电池图像的图形场景

	subthread = new QThread(this);           //创建一个子线程
	m_thread = new MyThread();               //创建一个新的目标自定义线程
	m_thread->moveToThread(subthread);       //将新的目标自定义线程移入子线程中
  
	
	connect(this,&MainWindow::StartThread,m_thread,&MyThread::MyWork);
	connect(m_thread, &MyThread::singal_back, this, &MainWindow::slot_handle_finish);
	qRegisterMetaType<ROI_pars >("ROI_pars");    //注册参数类型
	connect(this, SIGNAL(sendparameterstomythread(ROI_pars)),m_thread, SLOT(acceptROIS(ROI_pars)));

}

/*
定时器初始化
*/
void MainWindow::Timer_Init()
{
	/*************用于控制统计数据显示，每10ms刷新********************/
	Timer_Control = new QTimer();
	Timer_Control->setInterval(10);       //设置定时周期，单位：毫秒
	Timer_Control->start();
	connect(Timer_Control, SIGNAL(timeout()), this, SLOT(on_Display_Timer_timeout())); //连接槽函数on_Display_Timer_timeout()
}

/*
定时器中断函数，显示统计数据
*/
void MainWindow::on_Display_Timer_timeout()
{
	i++;
	/*右下方统计显示内容*/
	Count_Bottom_Update();
	/*上方显示内容*/
	Count_Top_Update();
	/*系统状态栏*/
	System_Condition_Update();
	/*测试用*/
	if (i >= 200)
	{
		if (SysCond_Queue_Left->isFull())
			SysCond_Queue_Left->DeQueue();	
		if (SysCond_Queue_Right->isFull())
			SysCond_Queue_Right->DeQueue();		
		sys_Test(j);
		Count_Bottom_Data.Total++;
		i = 0;
		j++;		
		mymovie->Play(true,1);
	}
}

/*
Reset按钮点击后
*/
void MainWindow::on_Reset_clicked()
{	
	Count_Bottom_Data.Since_Start = Time_Current->currentTime().toString("hh:mm:ss"); //开始时间设为当前时间
	Count_Bottom_Data.Total = 0;                                                      //统计数据清零
	Count_Bottom_Data.Pass = 0;                                                       //统计数据清零
	Count_Bottom_Data.Fail = 0;                                                       //统计数据清零		
}

/*
测试内容
*/
void MainWindow::sys_Test(int i)
{
	switch (i % 13)
	{
	case 0:
		SysCond_belt_Left = "传送带状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_belt_Left);
		SysCond_belt_Right = QString("%1 清料界面").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_belt_Right);
		break;
	case 1:
		SysCond_turntable_Left = "转盘状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_turntable_Left);
		SysCond_turntable_Right = QString("%1 发送测量命令").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_turntable_Right);
		break;
	case 2:		
		SysCond_load_Left = "上料轴状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_load_Left);
		SysCond_load_Right = QString("%1 拍照结束").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_load_Right);
		break;
	case 3:
		SysCond_ST1_Left = "ST1状态";				
		SysCond_Queue_Left->EnQueue(&SysCond_ST1_Left);
		SysCond_ST1_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST1_Right);
		break;
	case 4:
		SysCond_ST2_Left = "ST2状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST2_Left);
		SysCond_ST2_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST2_Right);
		break;
	case 5:
		SysCond_ST3_Left = "ST3状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST3_Left);
		SysCond_ST3_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST3_Right);
		break;
	case 6:
		SysCond_ST4_Left = "ST4状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST4_Left);
		SysCond_ST4_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST4_Right);
		break;
	case 7:
		SysCond_ST5_Left = "ST5状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST5_Left);
		SysCond_ST5_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST5_Right);
		break;
	case 8:
		SysCond_ST6_Left = "ST6状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST6_Left);
		SysCond_ST6_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST6_Right);
		break;
	case 9:
		SysCond_ST7_Left = "ST7状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST7_Left);
		SysCond_ST7_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST7_Right);		
		break;
	case 10:
		SysCond_ST8_Left = "ST8状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST8_Left);
		SysCond_ST8_Right = QString("%1 测量完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST8_Right);
		break;
	case 11:
		SysCond_blank_Left = "下料轴状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_blank_Left);
		SysCond_blank_Right = QString("%1 下料线程完成").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_blank_Right);
		break;
	case 12:
		SysCond_sys_Left = "系统状态";		
		SysCond_Queue_Left->EnQueue(&SysCond_sys_Left);
		SysCond_sys_Right = QString("%1 系统停止,停止工作").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_sys_Right);
		break;
	default:
		break;
	}
}

/*
下方统计数据
*/
void MainWindow::Count_Bottom()
{ 
	/********************************************表格****************************/
	//表格对象实例化	
	Count_Bottom_Model = new QStandardItemModel();	
	//表格数据初始化
	Count_Bottom_Data.Since_Start = Time_Current->currentTime().toString("hh:mm:ss");
	Count_Bottom_Data.Total = 1000;
	Count_Bottom_Data.Pass = 800;
	Count_Bottom_Data.Fail = 200;
	//表格固定显示内容
	Count_Bottom_Model->setItem(0, 0, new QStandardItem("Since"));
	Count_Bottom_Model->setItem(0, 1, new QStandardItem("Total"));
	Count_Bottom_Model->setItem(0, 2, new QStandardItem("Pass"));
	Count_Bottom_Model->setItem(0, 3, new QStandardItem("Fail"));	
	//数据模型设置
	for (int i = 0; i < 4; i++)
	{
		Count_Bottom_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);                    //水平居中
		Count_Bottom_Model->item(0, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);  //不可选中，不可编辑
	}
	//将数据模型应用于表格
	ui.Count_Bottom->setModel(Count_Bottom_Model);
	//设置列宽	
	ui.Count_Bottom->setColumnWidth(0, 202);
	ui.Count_Bottom->setColumnWidth(1, 66);
	ui.Count_Bottom->setColumnWidth(2, 66);
	ui.Count_Bottom->setColumnWidth(3, 66);
}

/*
下方统计数据更新
*/
void MainWindow::Count_Bottom_Update()
{
	//获取时间
	Count_Bottom_Data.Since_End = Time_Current->currentTime().toString("hh:mm:ss");
	Count_Bottom_Data.Since = QString("%1 - %2 ").arg(Count_Bottom_Data.Since_Start).arg(Count_Bottom_Data.Since_End);
	//更改数据模型中数据
	Count_Bottom_Model->setItem(1, 0, new QStandardItem(Count_Bottom_Data.Since));
	Count_Bottom_Model->setItem(1, 1, new QStandardItem(QString::number(Count_Bottom_Data.Total, 10)));
	Count_Bottom_Model->setItem(1, 2, new QStandardItem(QString::number(Count_Bottom_Data.Pass, 10)));
	Count_Bottom_Model->setItem(1, 3, new QStandardItem(QString::number(Count_Bottom_Data.Fail, 10)));
	//数据模型设置
	for (int i = 0; i < 4; i++)
	{
		Count_Bottom_Model->item(1, i)->setTextAlignment(Qt::AlignCenter);                      //水平居中
		Count_Bottom_Model->item(1, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);    //不可选中，不可编辑
	}
}

/*
标题栏统计数据
*/
void MainWindow::Count_Top()
{
	
	/****************************表格***********************************/
	//实例化表格对象	
	Count_Top_Model = new QStandardItemModel(this);	
	//数据初始化
	Count_Top_Data.Total = 0;
	Count_Top_Data.Pass = 0;
	Count_Top_Data.Fail = 0;
	Count_Top_Data.Persent = 0;
	Count_Top_Data.CT = 4;
	
	//固定显示内容
	Count_Top_Model->setItem(0, 0, new QStandardItem("总数"));
	Count_Top_Model->setItem(0, 2, new QStandardItem("合格数"));
	Count_Top_Model->setItem(0, 4, new QStandardItem("不合格数"));
	Count_Top_Model->setItem(0, 6, new QStandardItem("合格率"));
	Count_Top_Model->setItem(0, 8, new QStandardItem("CT"));
	Count_Top_Model->setItem(0, 1, new QStandardItem(QString::number(Count_Top_Data.Total, 10)));
	Count_Top_Model->setItem(0, 3, new QStandardItem(QString::number(Count_Top_Data.Pass, 10)));
	Count_Top_Model->setItem(0, 5, new QStandardItem(QString::number(Count_Top_Data.Fail, 10)));
	Count_Top_Model->setItem(0, 7, new QStandardItem(QString("%1%").arg(QString("%1").arg(Count_Top_Data.Persent))));
	Count_Top_Model->setItem(0, 9, new QStandardItem(QString::number(Count_Top_Data.CT, 10)));
	//数据模型设置
	for (int i = 0; i < 10; i++)
	{
		Count_Top_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);                   //水平居中
		Count_Top_Model->item(0, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable); //不可选中，不可编辑
	}	
	//将数据模型应用于表格	
	ui.Count_Top->setModel(Count_Top_Model);
	//设置列宽
	for (int i = 0; i < 10; i++)
	{		
		ui.Count_Top->setColumnWidth(i, 80);
	}
		
}

/*
标题栏统计数据更新
*/
void MainWindow::Count_Top_Update()
{
	//获取数据，测试用
	Count_Top_Data.Total = Count_Bottom_Data.Total;
	Count_Top_Data.Pass = Count_Bottom_Data.Pass;
	//计算合格率
	if (Count_Top_Data.Total != 0)
	{
		Count_Top_Data.Persent = Count_Top_Data.Pass * 100 / Count_Top_Data.Total;
	}
	else Count_Top_Data.Persent = 0;
	//更改数据模型中数据
	Count_Top_Model->setItem(0, 1, new QStandardItem(QString::number(Count_Top_Data.Total, 10)));
	Count_Top_Model->setItem(0, 3, new QStandardItem(QString::number(Count_Top_Data.Pass, 10)));
	Count_Top_Model->setItem(0, 5, new QStandardItem(QString::number(Count_Top_Data.Fail, 10)));
	Count_Top_Model->setItem(0, 7, new QStandardItem(QString("%1%").arg(QString("%1").arg(Count_Top_Data.Persent))));
	Count_Top_Model->setItem(0, 9, new QStandardItem(QString::number(Count_Top_Data.CT, 10)));
	//数据模型设置
	for (int i = 0; i < 10; i++)
	{
		Count_Top_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);                   //水平居中
		Count_Top_Model->item(0, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable); //不可选中，不可编辑
	}
}

/*
检测信息，包括正在检测和检测不合格
*/
void MainWindow::Test_Inf()
{	
	//对象实例化
	//Test_Inf_Widget = new QWidget(this);
	//Test_Inf_Tab = new QTabWidget(Test_Inf_Widget);
	Test_Inf_Tab = new QTabWidget(this);
	Test_Inf_Testing = new QWidget();
	Test_Inf_Failed = new QWidget();
	Sys_Tab_Widget = new QWidget();
	//窗口设置
	//Test_Inf_Widget->setGeometry(QRect(50, 850, 1820, 201));
	//Test_Inf_Widget->setStyleSheet("background-color: rgb(50,50, 50);"
	//    "border-radius:0px;");
	//标签页
	//Test_Inf_Tab->setGeometry(QRect(50, 850, 1820, 201));
	Test_Inf_Tab->addTab(Sys_Tab_Widget, "系统状态");
	Test_Inf_Tab->addTab(Test_Inf_Testing, "正在检测");
	Test_Inf_Tab->addTab(Test_Inf_Failed, "检测未通过");
	Test_Inf_Tab->setGeometry(QRect(0, 0, 1820, 201));
	Test_Inf_Tab->setStyleSheet("QTabBar::tab{"
		"height:20;"
		"width:90;"
		"background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
			"stop : 0 #808080, stop: 0.4 #858585,"
			"stop: 0.5 #3A3A3A, stop: 1.0 #505050);"
		"color:rgba(255,255,255,150);"
		"border: 1px solid #C4C4C3;"
		"border-bottom: 0px;"
		"border-radius:0px;"
		"}"
		"QTabBar::tab:hover{"
	     "background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
			"stop : 0 #fafafa, stop: 0.4 #f4f4f4,"
			"stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);}"
		"QTabBar::tab:selected{"
		"color:rgba(0,0,255,150);"
		"background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
		"stop : 0 #9A9A9A, stop: 0.4 #9F9F9F,"
		"stop: 0.5 #5B5B5B, stop: 1.0 #6A6A6A);"
	    "}");		
	/****************************************************系统状态**************************************************************/
	Sys_ScrollArea = new QScrollArea(Sys_Tab_Widget);
	Sys_ScrollArea->setGeometry(0, 0, 1820, 180);
	Sys_ScrollArea->setStyleSheet("background-color: rgb(50,50, 50);"
		"border-radius:0px;");
	Sys_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	Sys_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QWidget *Sys_Widget = new QWidget(Sys_ScrollArea);
	Sys_ScrollArea->setWidget(Sys_Widget);
	Sys_Widget->setGeometry(0, 0, 1850, 300);

	Sys_Table = new QTableView(Sys_Widget);
	Sys_Model = new QStandardItemModel();
	//Sys_Table->setGeometry(QRect(50, 500, 1820, 240));
	Sys_Table->setGeometry(QRect(0, 0, 1805, 240));
	
	/*************************************************************检测不合格***************************************************/	
	//滚动条
	Test_Inf_Failed_ScrollArea = new QScrollArea(Test_Inf_Failed);
	Test_Inf_Failed_ScrollArea->setGeometry(0, 0,1820, 180);
	Test_Inf_Failed_ScrollArea->setStyleSheet("background-color: rgb(50,50, 50);"
		"border-radius:0px;");
	Test_Inf_Failed_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	Test_Inf_Failed_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//标题栏
	Test_Inf_Failed_Title_TableView = new QTableView(Test_Inf_Failed_ScrollArea);
	Test_Inf_Failed_Title_Model = new QStandardItemModel();
	Test_Inf_Failed_Title_TableView->setGeometry(QRect(0, 0, 1805, 30));
	Test_Inf_Failed_Title_Model->setItem(0, 0, new QStandardItem("Failed Barcode"));
	Test_Inf_Failed_Title_Model->setItem(0, 1, new QStandardItem("Failed Item"));
	Test_Inf_Failed_Title_Model->item(0, 0)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Failed_Title_Model->item(0, 1)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Failed_Title_TableView->setLineWidth(0);
	Test_Inf_Failed_Title_TableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Test_Inf_Failed_Title_TableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Test_Inf_Failed_Title_TableView->setSelectionMode(QAbstractItemView::NoSelection);
	Test_Inf_Failed_Title_TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
	Test_Inf_Failed_Title_TableView->horizontalHeader()->setVisible(false);
	Test_Inf_Failed_Title_TableView->verticalHeader()->setVisible(false);
	Test_Inf_Failed_Title_TableView->verticalHeader()->setEditTriggers(QAbstractItemView::NoEditTriggers);
	Test_Inf_Failed_Title_TableView->verticalHeader()->setDefaultSectionSize(30);
	Test_Inf_Failed_Title_TableView->setModel(Test_Inf_Failed_Title_Model);
	Test_Inf_Failed_Title_TableView->setColumnWidth(0, 300);   //设置列宽
	Test_Inf_Failed_Title_TableView->setColumnWidth(1, 1505);
	//设置滚动区域
	QWidget *Test_Inf_Failed_Widget = new QWidget(Test_Inf_Failed_ScrollArea);
	Test_Inf_Failed_ScrollArea->setWidget(Test_Inf_Failed_Widget);
	Test_Inf_Failed_Widget->setGeometry(0, 0,1850, 330);	

	//数据模型初始化
	Test_Inf_Failed_Model = new QStandardItemModel();
	Test_Inf_Failed_Model->setItem(0, 0, new QStandardItem("Testing Barcode"));
	Test_Inf_Failed_Model->setItem(9, 0, new QStandardItem("Failed Barcode"));
	Test_Inf_Failed_Model->setItem(0, 1, new QStandardItem("Testing Item"));
	Test_Inf_Failed_Model->setItem(9, 1, new QStandardItem("Failed Item"));

	Test_Inf_Failed_Model->item(0, 0)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Failed_Model->item(0, 1)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Failed_Model->item(9, 1)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Failed_Model->item(9, 0)->setForeground((QBrush(QColor(255, 0, 0))));

	Test_Inf_Failed_Model->item(0, 0)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
	Test_Inf_Failed_Model->item(0, 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
	Test_Inf_Failed_Model->item(9, 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
	Test_Inf_Failed_Model->item(9, 0)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);	

	ui.Test_Inf_Failed_TableView->setModel(Test_Inf_Failed_Model);

	ui.Test_Inf_Failed_TableView->setColumnWidth(0, 300);   //设置列宽
	ui.Test_Inf_Failed_TableView->setColumnWidth(1, 1550);

    /********************************************************正在检测****************************************************/
	//滚动条
	Test_Inf_Testing_ScrollArea = new QScrollArea(Test_Inf_Testing);
	//Test_Inf_Testing_ScrollArea = new QScrollArea(ui.Testing);
	Test_Inf_Testing_ScrollArea->setGeometry(0, 0, 1820, 180);
	Test_Inf_Testing_ScrollArea->setStyleSheet("background-color: rgb(50,50, 50);"
		"border-radius:0px;");
	Test_Inf_Testing_ScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	Test_Inf_Testing_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//标题栏	
	Test_Inf_Testing_Title_Model = new QStandardItemModel();
	Test_Inf_Testing_Title_Model->setItem(0, 0, new QStandardItem("Testing Barcode"));
	Test_Inf_Testing_Title_Model->setItem(0, 1, new QStandardItem("Testing Item"));
	Test_Inf_Testing_Title_Model->item(0, 0)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Testing_Title_Model->item(0, 1)->setForeground((QBrush(QColor(0, 255, 0))));
	
	ui.Test_Inf_Testing_Title_TableView->setModel(Test_Inf_Testing_Title_Model);
	ui.Test_Inf_Testing_Title_TableView->setColumnWidth(0, 300);   //设置列宽
	ui.Test_Inf_Testing_Title_TableView->setColumnWidth(1, 1505);
	
	
	//数据模型初始化
	Test_Inf_Testing_Model = new QStandardItemModel();
	Test_Inf_Testing_Model->setItem(0, 0, new QStandardItem("Testing Barcode"));
	Test_Inf_Testing_Model->setItem(9, 0, new QStandardItem("Failed Barcode"));
	Test_Inf_Testing_Model->setItem(0, 1, new QStandardItem("Testing Item"));
	Test_Inf_Testing_Model->setItem(9, 1, new QStandardItem("Failed Item"));

	Test_Inf_Testing_Model->item(0, 0)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Testing_Model->item(0, 1)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Testing_Model->item(9, 1)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Testing_Model->item(9, 0)->setForeground((QBrush(QColor(255, 0, 0))));	

	ui.Test_Inf_Testing_TableView->setModel(Test_Inf_Testing_Model);

	ui.Test_Inf_Testing_TableView->setColumnWidth(0, 300);   //设置列宽
	ui.Test_Inf_Testing_TableView->setColumnWidth(1, 1500);
	
}

/*
系统状态初始化0
*/
void MainWindow::System_Condition()
{	
	/*********************左栏初始化*********************/
	//字符初始化为空白	
	Sys_Cond.line_1_Left = " ";
	Sys_Cond.line_2_Left = " ";
	Sys_Cond.line_3_Left = " ";
	Sys_Cond.line_4_Left = " ";
	Sys_Cond.line_5_Left = " ";
	Sys_Cond.line_6_Left = " ";
	Sys_Cond.line_7_Left = " ";
	Sys_Cond.line_8_Left = " ";

	/*******************************右栏初始化***********************************/
	//字符初始化为空白	
	Sys_Cond.line_1_Right = " ";
	Sys_Cond.line_2_Right = " ";
	Sys_Cond.line_3_Right = " ";
	Sys_Cond.line_4_Right = " ";
	Sys_Cond.line_5_Right = " ";
	Sys_Cond.line_6_Right = " ";
	Sys_Cond.line_7_Right = " ";
	Sys_Cond.line_8_Right = " ";

	/*********************数据模型获取各行字符**************************/
	//左栏
	Sys_Model->setItem(0, 0, new QStandardItem(Sys_Cond.line_1_Left));
	Sys_Model->setItem(1, 0, new QStandardItem(Sys_Cond.line_2_Left));
	Sys_Model->setItem(2, 0, new QStandardItem(Sys_Cond.line_3_Left));
	Sys_Model->setItem(3, 0, new QStandardItem(Sys_Cond.line_4_Left));
	Sys_Model->setItem(4, 0, new QStandardItem(Sys_Cond.line_5_Left));
	Sys_Model->setItem(5, 0, new QStandardItem(Sys_Cond.line_6_Left));
	Sys_Model->setItem(6, 0, new QStandardItem(Sys_Cond.line_7_Left));
	Sys_Model->setItem(7, 0, new QStandardItem(Sys_Cond.line_8_Left));
	//右栏
	Sys_Model->setItem(0, 1, new QStandardItem(Sys_Cond.line_1_Right));
	Sys_Model->setItem(1, 1, new QStandardItem(Sys_Cond.line_2_Right));
	Sys_Model->setItem(2, 1, new QStandardItem(Sys_Cond.line_3_Right));
	Sys_Model->setItem(3, 1, new QStandardItem(Sys_Cond.line_4_Right));
	Sys_Model->setItem(4, 1, new QStandardItem(Sys_Cond.line_5_Right));
	Sys_Model->setItem(5, 1, new QStandardItem(Sys_Cond.line_6_Right));
	Sys_Model->setItem(6, 1, new QStandardItem(Sys_Cond.line_7_Right));
	Sys_Model->setItem(7, 1, new QStandardItem(Sys_Cond.line_8_Right));

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
		{
			Sys_Model->item(i, j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
		}

	/*设置字体*/
	QFont font_SysCondition;
	font_SysCondition.setPointSize(11);
	font_SysCondition.setBold(true);
	font_SysCondition.setWeight(50);
	Sys_Table->setFont(font_SysCondition);

	Sys_Table->setStyleSheet("QTableView{\n"
		"background-color:rgba(255, 255, 255,0);\n"
		"color:rgb(255,255,255);\n"
		"gridline-color: rgb(255, 255,255);\n"
		"border-radius:0px;\n"
		"}");

	Sys_Table->setLineWidth(0);
	Sys_Table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Sys_Table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	Sys_Table->setSelectionMode(QAbstractItemView::NoSelection);    //不可选中
	Sys_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);  //不可编辑
	Sys_Table->horizontalHeader()->setVisible(false);               //隐藏水平表头
	Sys_Table->verticalHeader()->setVisible(false);                 //隐藏垂直表头
	Sys_Table->verticalHeader()->setDefaultSectionSize(30);         //设置行高

	Sys_Table->setModel(Sys_Model);
	ui.Sys_Table->setModel(Sys_Model);

	Sys_Table->setColumnWidth(0, 500);   //设置列宽
	Sys_Table->setColumnWidth(1, 1305);

	ui.Sys_Table->setColumnWidth(0, 500);   //设置列宽
	ui.Sys_Table->setColumnWidth(1, 1305);
}

/*
系统状态显示内容更新
*/
void MainWindow::System_Condition_Update()
{
	/*******************队列更新*************************/
	//左栏
	//队不满时
	if (!SysCond_Queue_Left->isFull())
	{
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front)
			Sys_Cond.line_1_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front);
		else Sys_Cond.line_1_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 1)
			Sys_Cond.line_2_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 1);
		else Sys_Cond.line_2_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 2)
			Sys_Cond.line_3_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 2);
		else Sys_Cond.line_3_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 3)
			Sys_Cond.line_4_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 3);
		else Sys_Cond.line_4_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 4)
			Sys_Cond.line_5_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 4);
		else Sys_Cond.line_5_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 5)
			Sys_Cond.line_6_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 5);
		else Sys_Cond.line_6_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 6)
			Sys_Cond.line_7_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 6);
		else Sys_Cond.line_7_Left = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 7)
			Sys_Cond.line_8_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 7);
		else Sys_Cond.line_8_Left = " ";

	}
	//队满时
	else
	{
		Sys_Cond.line_1_Left = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front);
		Sys_Cond.line_2_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 1 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
		Sys_Cond.line_3_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 2 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
		Sys_Cond.line_4_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 3 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
		Sys_Cond.line_5_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 4 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
		Sys_Cond.line_6_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 5 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
		Sys_Cond.line_7_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 6 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
		Sys_Cond.line_8_Left = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + 7 + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
	}
	//右栏
	//队不满时
	if (!SysCond_Queue_Right->isFull())
	{
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front)
			Sys_Cond.line_1_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front);
		else Sys_Cond.line_1_Left = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 1)
			Sys_Cond.line_2_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 1);
		else Sys_Cond.line_2_Right = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 2)
			Sys_Cond.line_3_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 2);
		else Sys_Cond.line_3_Right = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 3)
			Sys_Cond.line_4_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 3);
		else Sys_Cond.line_4_Right = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 4)
			Sys_Cond.line_5_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 4);
		else Sys_Cond.line_5_Right = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 5)
			Sys_Cond.line_6_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 5);
		else Sys_Cond.line_6_Right = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 6)
			Sys_Cond.line_7_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 6);
		else Sys_Cond.line_7_Right = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 7)
			Sys_Cond.line_8_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 7);
		else Sys_Cond.line_8_Right = " ";
	}
	//队满时
	else
	{
		Sys_Cond.line_1_Right = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front);
		Sys_Cond.line_2_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 1 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
		Sys_Cond.line_3_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 2 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
		Sys_Cond.line_4_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 3 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
		Sys_Cond.line_5_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 4 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
		Sys_Cond.line_6_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 5 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
		Sys_Cond.line_7_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 6 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
		Sys_Cond.line_8_Right = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + 7 + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
	}
	/*********************Item更新**********************/
	//左栏
	Sys_Model->setItem(0, 0, new QStandardItem(Sys_Cond.line_1_Left));
	Sys_Model->setItem(1, 0, new QStandardItem(Sys_Cond.line_2_Left));
	Sys_Model->setItem(2, 0, new QStandardItem(Sys_Cond.line_3_Left));
	Sys_Model->setItem(3, 0, new QStandardItem(Sys_Cond.line_4_Left));
	Sys_Model->setItem(4, 0, new QStandardItem(Sys_Cond.line_5_Left));
	Sys_Model->setItem(5, 0, new QStandardItem(Sys_Cond.line_6_Left));
	Sys_Model->setItem(6, 0, new QStandardItem(Sys_Cond.line_7_Left));
	Sys_Model->setItem(7, 0, new QStandardItem(Sys_Cond.line_8_Left));
	//右栏
	Sys_Model->setItem(0, 1, new QStandardItem(Sys_Cond.line_1_Right));
	Sys_Model->setItem(1, 1, new QStandardItem(Sys_Cond.line_2_Right));
	Sys_Model->setItem(2, 1, new QStandardItem(Sys_Cond.line_3_Right));
	Sys_Model->setItem(3, 1, new QStandardItem(Sys_Cond.line_4_Right));
	Sys_Model->setItem(4, 1, new QStandardItem(Sys_Cond.line_5_Right));
	Sys_Model->setItem(5, 1, new QStandardItem(Sys_Cond.line_6_Right));
	Sys_Model->setItem(6, 1, new QStandardItem(Sys_Cond.line_7_Right));
	Sys_Model->setItem(7, 1, new QStandardItem(Sys_Cond.line_8_Right));

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
		{
			Sys_Model->item(i, j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
		}
	Sys_Table->setColumnWidth(0, 500);   //设置列宽
	Sys_Table->setColumnWidth(1, 1305);
	ui.Sys_Table->setColumnWidth(0, 500);   //设置列宽
	ui.Sys_Table->setColumnWidth(1, 1305);
}

/*
Mat类转为QImage类
*/
QImage MainWindow::Mat2QImage(Mat &mat)
{	
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		return QImage();
	}
}

/*
打开一张图片
*/
void MainWindow::on_Open_clicked()
{	

	if (subthread->isRunning() == true) {}
	else
	{		
		m_thread->setFlag(false);
		subthread->start();
		emit(sendparameterstomythread(m_roipars));//向子线程传递参数
		//启动了线程，但是并没有进入子线程
		//必须通过信号/槽的方式进入子线程
		//直接通过m_thread->Mywork()是不行的，这样Mywork()中的线程就是主线程
		emit StartThread();	
	}		
}

/*
加载ROI参数
*/
void MainWindow::on_Import_clicked()
{
	QString  csvFileName = QFileDialog::getOpenFileName(this, "加载配置文件", ".", "csv files(*.csv)");  //配置文件路径	
	QFile file(csvFileName);
	if (csvFileName.isEmpty())		return; //未选择文件   
	else
	{
		//打开文件
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
		QStringList list;//用于记录加载文件中的数据
		list.clear();//清空列表
		QTextStream in(&file);
		//逐行读取，直到最后一行
		int i = 0;
		m_roipars.reserve(0);//先清空参数列表，为读取参数做好准备
		while (!in.atEnd())
		{
			QString fileLine = in.readLine();//逐行读取
			list = fileLine.split(",", QString::SkipEmptyParts);//将每行的数据以","分割	
																//读取表中内容
			if (i == 2)
			{
				roi_parameters *m_roi_parameters = new roi_parameters;//为用于读取数据的临时结构体分配内存
																	  //读取表中的数据
				m_roi_parameters->x = list.at(0).toInt();
				m_roi_parameters->y = list.at(1).toInt();
				m_roi_parameters->width = list.at(2).toInt();
				m_roi_parameters->height = list.at(3).toInt();
				m_roipars.push_back(m_roi_parameters);//将新读取的参数存入参数列表中													 
			}
			i++;
		}

	}

	file.close();//读取完毕，关闭文件
}

/*
图像处理结束后槽函数
在主界面中显示处理后的图像
*/
void MainWindow::slot_handle_finish()
{
	m_thread->setFlag(); //设置进程标志位
	subthread->quit();//退出子进程
	subthread->wait();//等待子进程结束
	
	dstImg.load("C:\\Users\\16935\\Desktop\\BatteryImg\\1(new).jpg");//载入要显示的图像	
	
	sence->clear(); //清空场景
	sence->addPixmap(QPixmap::fromImage(dstImg));   //向场景中加载图像
    ui.graphicsView->setScene(sence);	            //向界面的图像口添加场景
	
}


/*
关闭界面
*/
void MainWindow::on_Stop_clicked()
{
	m_thread->setFlag();
	subthread->quit();
	subthread->wait();
	delete m_thread;	
	//sss.close();
	
	this->close();
	
}

/*
打开设置界面
*/
void MainWindow::on_Setting_clicked()
{	
	sss.show();
}
