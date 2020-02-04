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
	/****************************************************系统状态**************************************************************/
	Sys_Model = new QStandardItemModel();
	
	/*************************************************************检测不合格***************************************************/	
	//标题栏	
	Test_Inf_Failed_Title_Model = new QStandardItemModel();
	Test_Inf_Failed_Title_Model->setItem(0, 0, new QStandardItem("Failed Barcode"));
	Test_Inf_Failed_Title_Model->setItem(0, 1, new QStandardItem("Failed Item"));
	Test_Inf_Failed_Title_Model->item(0, 0)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Failed_Title_Model->item(0, 1)->setForeground((QBrush(QColor(255, 0, 0))));
	
	ui.Test_Inf_Failed_Title_TableView->setModel(Test_Inf_Failed_Title_Model);
	ui.Test_Inf_Failed_Title_TableView->setColumnWidth(0, 300);   //设置列宽
	ui.Test_Inf_Failed_Title_TableView->setColumnWidth(1, 1505);
	
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

	ui.Test_Inf_Testing_TableView->setModel(Test_Inf_Testing_Model);//数据模型应用于表格

	ui.Test_Inf_Testing_TableView->setColumnWidth(0, 300);   //设置列宽
	ui.Test_Inf_Testing_TableView->setColumnWidth(1, 1500);
	
}

/*
系统状态初始化
*/
void MainWindow::System_Condition()
{	
	/*********************左栏初始化*********************/
	//字符初始化为空白		
	Sys_Cond_Left << " " << " " << " " << " " << " " << " " << " " << " ";

	/********************右栏初始化********************/
	//字符初始化为空白

	Sys_Cond_Right << " " << " " << " " << " " << " " << " " << " " << " ";
	/*********************数据模型获取各行字符**************************/
	//左栏	
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 0, new QStandardItem(Sys_Cond_Left[i]));
	
	//右栏	
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 1, new QStandardItem(Sys_Cond_Right[i]));
	
    //设置item为不可编辑不可选中
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
			Sys_Model->item(i, j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);		

	ui.Sys_Table->setModel(Sys_Model);//数据模型应用于表格

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
			Sys_Cond_Left[0] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front);
		else Sys_Cond_Left[0] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 1)
			Sys_Cond_Left[1] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 1);
		else Sys_Cond_Left[1] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 2)
			Sys_Cond_Left[2] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 2);
		else Sys_Cond_Left[2] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 3)
			Sys_Cond_Left[3] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 3);
		else Sys_Cond_Left[3] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 4)
			Sys_Cond_Left[4] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 4);
		else Sys_Cond_Left[4] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 5)
			Sys_Cond_Left[5] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 5);
		else Sys_Cond_Left[5] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 6)
			Sys_Cond_Left[6] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 6);
		else Sys_Cond_Left[6] = " ";
		if (SysCond_Queue_Left->rear > SysCond_Queue_Left->front + 7)
			Sys_Cond_Left[7] = **(SysCond_Queue_Left->base + SysCond_Queue_Left->front + 7);
		else Sys_Cond_Left[7] = " ";

	}
	//队满时
	else
		for (int i = 0; i < 8; i++)
			Sys_Cond_Left[i] = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + i + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
	
	//右栏
	//队不满时
	if (!SysCond_Queue_Right->isFull())
	{		
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front)
			Sys_Cond_Right[0] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front);
		else Sys_Cond_Right[0] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 1)
			Sys_Cond_Right[1] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 1);
		else Sys_Cond_Right[1] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 2)
			Sys_Cond_Right[2] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 2);
		else Sys_Cond_Right[2] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 3)
			Sys_Cond_Right[3] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 3);
		else Sys_Cond_Right[3] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 4)
			Sys_Cond_Right[4] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 4);
		else Sys_Cond_Right[4] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 5)
			Sys_Cond_Right[5] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 5);
		else Sys_Cond_Right[5] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 6)
			Sys_Cond_Right[6] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 6);
		else Sys_Cond_Right[6] = " ";
		if (SysCond_Queue_Right->rear > SysCond_Queue_Right->front + 7)
			Sys_Cond_Right[7] = **(SysCond_Queue_Right->base + SysCond_Queue_Right->front + 7);
		else Sys_Cond_Right[7] = " ";
	}
	//队满时
	else
		for (int i = 0; i < 8; i++)
			Sys_Cond_Right[i] = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + i + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
	
	/*********************Item更新**********************/
	//左栏	
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 0, new QStandardItem(Sys_Cond_Left[i]));

	//右栏
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 1, new QStandardItem(Sys_Cond_Right[i]));	

	//设置item不可编辑，不可选中
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
		{
			Sys_Model->item(i, j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
		}

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
统计数据复位
*/
void MainWindow::on_Reset_clicked()
{
	Count_Bottom_Data.Since_Start = Time_Current->currentTime().toString("hh:mm:ss"); //开始时间设为当前时间
	Count_Bottom_Data.Total = 0;                                                      //统计数据清零
	Count_Bottom_Data.Pass = 0;                                                       //统计数据清零
	Count_Bottom_Data.Fail = 0;                                                       //统计数据清零		
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
