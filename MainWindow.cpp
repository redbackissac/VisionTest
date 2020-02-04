#include "MainWindow.h"

#pragma execution_character_set("utf-8")
/*
������ʵ�ֺ���
*/
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	/*�����ʼ��*/
	
	ui.setupUi(this);
	this->resize(1920,1080);	
	/*��ʱ����ʼ��*/
	Timer_Init();  
	/*�·�ͳ������*/
	Count_Bottom();	
	/*������ͳ������*/
	Count_Top();
	/*ϵͳ״̬*/
	Test_Inf();
	System_Condition();
	mymovie = new MyMovie(this);
	mymovie->Init(400,400,2,0x0f);
	mymovie->move(150, 450);
	sence = new QGraphicsScene;              //������ʾ���ͼ���ͼ�γ���

	subthread = new QThread(this);           //����һ�����߳�
	m_thread = new MyThread();               //����һ���µ�Ŀ���Զ����߳�
	m_thread->moveToThread(subthread);       //���µ�Ŀ���Զ����߳��������߳���
  
	
	connect(this,&MainWindow::StartThread,m_thread,&MyThread::MyWork);
	connect(m_thread, &MyThread::singal_back, this, &MainWindow::slot_handle_finish);
	qRegisterMetaType<ROI_pars >("ROI_pars");    //ע���������
	connect(this, SIGNAL(sendparameterstomythread(ROI_pars)),m_thread, SLOT(acceptROIS(ROI_pars)));

}

/*
��ʱ����ʼ��
*/
void MainWindow::Timer_Init()
{
	/*************���ڿ���ͳ��������ʾ��ÿ10msˢ��********************/
	Timer_Control = new QTimer();
	Timer_Control->setInterval(10);       //���ö�ʱ���ڣ���λ������
	Timer_Control->start();
	connect(Timer_Control, SIGNAL(timeout()), this, SLOT(on_Display_Timer_timeout())); //���Ӳۺ���on_Display_Timer_timeout()
}

/*
��ʱ���жϺ�������ʾͳ������
*/
void MainWindow::on_Display_Timer_timeout()
{
	i++;
	/*���·�ͳ����ʾ����*/
	Count_Bottom_Update();
	/*�Ϸ���ʾ����*/
	Count_Top_Update();
	/*ϵͳ״̬��*/
	System_Condition_Update();
	/*������*/
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
��������
*/
void MainWindow::sys_Test(int i)
{
	switch (i % 13)
	{
	case 0:
		SysCond_belt_Left = "���ʹ�״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_belt_Left);
		SysCond_belt_Right = QString("%1 ���Ͻ���").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_belt_Right);
		break;
	case 1:
		SysCond_turntable_Left = "ת��״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_turntable_Left);
		SysCond_turntable_Right = QString("%1 ���Ͳ�������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_turntable_Right);
		break;
	case 2:		
		SysCond_load_Left = "������״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_load_Left);
		SysCond_load_Right = QString("%1 ���ս���").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_load_Right);
		break;
	case 3:
		SysCond_ST1_Left = "ST1״̬";				
		SysCond_Queue_Left->EnQueue(&SysCond_ST1_Left);
		SysCond_ST1_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST1_Right);
		break;
	case 4:
		SysCond_ST2_Left = "ST2״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST2_Left);
		SysCond_ST2_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST2_Right);
		break;
	case 5:
		SysCond_ST3_Left = "ST3״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST3_Left);
		SysCond_ST3_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST3_Right);
		break;
	case 6:
		SysCond_ST4_Left = "ST4״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST4_Left);
		SysCond_ST4_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST4_Right);
		break;
	case 7:
		SysCond_ST5_Left = "ST5״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST5_Left);
		SysCond_ST5_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST5_Right);
		break;
	case 8:
		SysCond_ST6_Left = "ST6״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST6_Left);
		SysCond_ST6_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST6_Right);
		break;
	case 9:
		SysCond_ST7_Left = "ST7״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST7_Left);
		SysCond_ST7_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST7_Right);		
		break;
	case 10:
		SysCond_ST8_Left = "ST8״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_ST8_Left);
		SysCond_ST8_Right = QString("%1 �������").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_ST8_Right);
		break;
	case 11:
		SysCond_blank_Left = "������״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_blank_Left);
		SysCond_blank_Right = QString("%1 �����߳����").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_blank_Right);
		break;
	case 12:
		SysCond_sys_Left = "ϵͳ״̬";		
		SysCond_Queue_Left->EnQueue(&SysCond_sys_Left);
		SysCond_sys_Right = QString("%1 ϵͳֹͣ,ֹͣ����").arg(Time_Current->currentTime().toString("hh:mm:ss"));
		SysCond_Queue_Right->EnQueue(&SysCond_sys_Right);
		break;
	default:
		break;
	}
}

/*
�·�ͳ������
*/
void MainWindow::Count_Bottom()
{ 
	/********************************************���****************************/
	//������ʵ����	
	Count_Bottom_Model = new QStandardItemModel();	
	//������ݳ�ʼ��
	Count_Bottom_Data.Since_Start = Time_Current->currentTime().toString("hh:mm:ss");
	Count_Bottom_Data.Total = 1000;
	Count_Bottom_Data.Pass = 800;
	Count_Bottom_Data.Fail = 200;
	//���̶���ʾ����
	Count_Bottom_Model->setItem(0, 0, new QStandardItem("Since"));
	Count_Bottom_Model->setItem(0, 1, new QStandardItem("Total"));
	Count_Bottom_Model->setItem(0, 2, new QStandardItem("Pass"));
	Count_Bottom_Model->setItem(0, 3, new QStandardItem("Fail"));	
	//����ģ������
	for (int i = 0; i < 4; i++)
	{
		Count_Bottom_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);                    //ˮƽ����
		Count_Bottom_Model->item(0, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);  //����ѡ�У����ɱ༭
	}
	//������ģ��Ӧ���ڱ��
	ui.Count_Bottom->setModel(Count_Bottom_Model);
	//�����п�	
	ui.Count_Bottom->setColumnWidth(0, 202);
	ui.Count_Bottom->setColumnWidth(1, 66);
	ui.Count_Bottom->setColumnWidth(2, 66);
	ui.Count_Bottom->setColumnWidth(3, 66);
}

/*
�·�ͳ�����ݸ���
*/
void MainWindow::Count_Bottom_Update()
{
	//��ȡʱ��
	Count_Bottom_Data.Since_End = Time_Current->currentTime().toString("hh:mm:ss");
	Count_Bottom_Data.Since = QString("%1 - %2 ").arg(Count_Bottom_Data.Since_Start).arg(Count_Bottom_Data.Since_End);
	//��������ģ��������
	Count_Bottom_Model->setItem(1, 0, new QStandardItem(Count_Bottom_Data.Since));
	Count_Bottom_Model->setItem(1, 1, new QStandardItem(QString::number(Count_Bottom_Data.Total, 10)));
	Count_Bottom_Model->setItem(1, 2, new QStandardItem(QString::number(Count_Bottom_Data.Pass, 10)));
	Count_Bottom_Model->setItem(1, 3, new QStandardItem(QString::number(Count_Bottom_Data.Fail, 10)));
	//����ģ������
	for (int i = 0; i < 4; i++)
	{
		Count_Bottom_Model->item(1, i)->setTextAlignment(Qt::AlignCenter);                      //ˮƽ����
		Count_Bottom_Model->item(1, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);    //����ѡ�У����ɱ༭
	}
}

/*
������ͳ������
*/
void MainWindow::Count_Top()
{
	
	/****************************���***********************************/
	//ʵ����������	
	Count_Top_Model = new QStandardItemModel(this);	
	//���ݳ�ʼ��
	Count_Top_Data.Total = 0;
	Count_Top_Data.Pass = 0;
	Count_Top_Data.Fail = 0;
	Count_Top_Data.Persent = 0;
	Count_Top_Data.CT = 4;
	
	//�̶���ʾ����
	Count_Top_Model->setItem(0, 0, new QStandardItem("����"));
	Count_Top_Model->setItem(0, 2, new QStandardItem("�ϸ���"));
	Count_Top_Model->setItem(0, 4, new QStandardItem("���ϸ���"));
	Count_Top_Model->setItem(0, 6, new QStandardItem("�ϸ���"));
	Count_Top_Model->setItem(0, 8, new QStandardItem("CT"));
	Count_Top_Model->setItem(0, 1, new QStandardItem(QString::number(Count_Top_Data.Total, 10)));
	Count_Top_Model->setItem(0, 3, new QStandardItem(QString::number(Count_Top_Data.Pass, 10)));
	Count_Top_Model->setItem(0, 5, new QStandardItem(QString::number(Count_Top_Data.Fail, 10)));
	Count_Top_Model->setItem(0, 7, new QStandardItem(QString("%1%").arg(QString("%1").arg(Count_Top_Data.Persent))));
	Count_Top_Model->setItem(0, 9, new QStandardItem(QString::number(Count_Top_Data.CT, 10)));
	//����ģ������
	for (int i = 0; i < 10; i++)
	{
		Count_Top_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);                   //ˮƽ����
		Count_Top_Model->item(0, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable); //����ѡ�У����ɱ༭
	}	
	//������ģ��Ӧ���ڱ��	
	ui.Count_Top->setModel(Count_Top_Model);
	//�����п�
	for (int i = 0; i < 10; i++)
	{		
		ui.Count_Top->setColumnWidth(i, 80);
	}
		
}

/*
������ͳ�����ݸ���
*/
void MainWindow::Count_Top_Update()
{
	//��ȡ���ݣ�������
	Count_Top_Data.Total = Count_Bottom_Data.Total;
	Count_Top_Data.Pass = Count_Bottom_Data.Pass;
	//����ϸ���
	if (Count_Top_Data.Total != 0)
	{
		Count_Top_Data.Persent = Count_Top_Data.Pass * 100 / Count_Top_Data.Total;
	}
	else Count_Top_Data.Persent = 0;
	//��������ģ��������
	Count_Top_Model->setItem(0, 1, new QStandardItem(QString::number(Count_Top_Data.Total, 10)));
	Count_Top_Model->setItem(0, 3, new QStandardItem(QString::number(Count_Top_Data.Pass, 10)));
	Count_Top_Model->setItem(0, 5, new QStandardItem(QString::number(Count_Top_Data.Fail, 10)));
	Count_Top_Model->setItem(0, 7, new QStandardItem(QString("%1%").arg(QString("%1").arg(Count_Top_Data.Persent))));
	Count_Top_Model->setItem(0, 9, new QStandardItem(QString::number(Count_Top_Data.CT, 10)));
	//����ģ������
	for (int i = 0; i < 10; i++)
	{
		Count_Top_Model->item(0, i)->setTextAlignment(Qt::AlignCenter);                   //ˮƽ����
		Count_Top_Model->item(0, i)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable); //����ѡ�У����ɱ༭
	}
}

/*
�����Ϣ���������ڼ��ͼ�ⲻ�ϸ�
*/
void MainWindow::Test_Inf()
{		
	/****************************************************ϵͳ״̬**************************************************************/
	Sys_Model = new QStandardItemModel();
	
	/*************************************************************��ⲻ�ϸ�***************************************************/	
	//������	
	Test_Inf_Failed_Title_Model = new QStandardItemModel();
	Test_Inf_Failed_Title_Model->setItem(0, 0, new QStandardItem("Failed Barcode"));
	Test_Inf_Failed_Title_Model->setItem(0, 1, new QStandardItem("Failed Item"));
	Test_Inf_Failed_Title_Model->item(0, 0)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Failed_Title_Model->item(0, 1)->setForeground((QBrush(QColor(255, 0, 0))));
	
	ui.Test_Inf_Failed_Title_TableView->setModel(Test_Inf_Failed_Title_Model);
	ui.Test_Inf_Failed_Title_TableView->setColumnWidth(0, 300);   //�����п�
	ui.Test_Inf_Failed_Title_TableView->setColumnWidth(1, 1505);
	
	//����ģ�ͳ�ʼ��
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

	ui.Test_Inf_Failed_TableView->setColumnWidth(0, 300);   //�����п�
	ui.Test_Inf_Failed_TableView->setColumnWidth(1, 1550);

    /********************************************************���ڼ��****************************************************/
	//������	
	Test_Inf_Testing_Title_Model = new QStandardItemModel();
	Test_Inf_Testing_Title_Model->setItem(0, 0, new QStandardItem("Testing Barcode"));
	Test_Inf_Testing_Title_Model->setItem(0, 1, new QStandardItem("Testing Item"));
	Test_Inf_Testing_Title_Model->item(0, 0)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Testing_Title_Model->item(0, 1)->setForeground((QBrush(QColor(0, 255, 0))));
	
	ui.Test_Inf_Testing_Title_TableView->setModel(Test_Inf_Testing_Title_Model);
	ui.Test_Inf_Testing_Title_TableView->setColumnWidth(0, 300);   //�����п�
	ui.Test_Inf_Testing_Title_TableView->setColumnWidth(1, 1505);
	
	
	//����ģ�ͳ�ʼ��
	Test_Inf_Testing_Model = new QStandardItemModel();
	Test_Inf_Testing_Model->setItem(0, 0, new QStandardItem("Testing Barcode"));
	Test_Inf_Testing_Model->setItem(9, 0, new QStandardItem("Failed Barcode"));
	Test_Inf_Testing_Model->setItem(0, 1, new QStandardItem("Testing Item"));
	Test_Inf_Testing_Model->setItem(9, 1, new QStandardItem("Failed Item"));

	Test_Inf_Testing_Model->item(0, 0)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Testing_Model->item(0, 1)->setForeground((QBrush(QColor(0, 255, 0))));
	Test_Inf_Testing_Model->item(9, 1)->setForeground((QBrush(QColor(255, 0, 0))));
	Test_Inf_Testing_Model->item(9, 0)->setForeground((QBrush(QColor(255, 0, 0))));	

	ui.Test_Inf_Testing_TableView->setModel(Test_Inf_Testing_Model);//����ģ��Ӧ���ڱ��

	ui.Test_Inf_Testing_TableView->setColumnWidth(0, 300);   //�����п�
	ui.Test_Inf_Testing_TableView->setColumnWidth(1, 1500);
	
}

/*
ϵͳ״̬��ʼ��
*/
void MainWindow::System_Condition()
{	
	/*********************������ʼ��*********************/
	//�ַ���ʼ��Ϊ�հ�		
	Sys_Cond_Left << " " << " " << " " << " " << " " << " " << " " << " ";

	/********************������ʼ��********************/
	//�ַ���ʼ��Ϊ�հ�

	Sys_Cond_Right << " " << " " << " " << " " << " " << " " << " " << " ";
	/*********************����ģ�ͻ�ȡ�����ַ�**************************/
	//����	
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 0, new QStandardItem(Sys_Cond_Left[i]));
	
	//����	
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 1, new QStandardItem(Sys_Cond_Right[i]));
	
    //����itemΪ���ɱ༭����ѡ��
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
			Sys_Model->item(i, j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);		

	ui.Sys_Table->setModel(Sys_Model);//����ģ��Ӧ���ڱ��

	ui.Sys_Table->setColumnWidth(0, 500);   //�����п�
	ui.Sys_Table->setColumnWidth(1, 1305);
}

/*
ϵͳ״̬��ʾ���ݸ���
*/
void MainWindow::System_Condition_Update()
{
	/*******************���и���*************************/
	//����
	//�Ӳ���ʱ
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
	//����ʱ
	else
		for (int i = 0; i < 8; i++)
			Sys_Cond_Left[i] = **(SysCond_Queue_Left->base + (SysCond_Queue_Left->front + i + SysCond_Queue_Left->QueueSize) % SysCond_Queue_Left->QueueSize);
	
	//����
	//�Ӳ���ʱ
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
	//����ʱ
	else
		for (int i = 0; i < 8; i++)
			Sys_Cond_Right[i] = **(SysCond_Queue_Right->base + (SysCond_Queue_Right->front + i + SysCond_Queue_Right->QueueSize) % SysCond_Queue_Right->QueueSize);
	
	/*********************Item����**********************/
	//����	
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 0, new QStandardItem(Sys_Cond_Left[i]));

	//����
	for (int i = 0; i < 8; i++)
		Sys_Model->setItem(i, 1, new QStandardItem(Sys_Cond_Right[i]));	

	//����item���ɱ༭������ѡ��
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 2; j++)
		{
			Sys_Model->item(i, j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
		}

	ui.Sys_Table->setColumnWidth(0, 500);   //�����п�
	ui.Sys_Table->setColumnWidth(1, 1305);
}

/*
Mat��תΪQImage��
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
ͳ�����ݸ�λ
*/
void MainWindow::on_Reset_clicked()
{
	Count_Bottom_Data.Since_Start = Time_Current->currentTime().toString("hh:mm:ss"); //��ʼʱ����Ϊ��ǰʱ��
	Count_Bottom_Data.Total = 0;                                                      //ͳ����������
	Count_Bottom_Data.Pass = 0;                                                       //ͳ����������
	Count_Bottom_Data.Fail = 0;                                                       //ͳ����������		
}

/*
��һ��ͼƬ
*/
void MainWindow::on_Open_clicked()
{	

	if (subthread->isRunning() == true) {}
	else
	{		
		m_thread->setFlag(false);
		subthread->start();
		emit(sendparameterstomythread(m_roipars));//�����̴߳��ݲ���
		//�������̣߳����ǲ�û�н������߳�
		//����ͨ���ź�/�۵ķ�ʽ�������߳�
		//ֱ��ͨ��m_thread->Mywork()�ǲ��еģ�����Mywork()�е��߳̾������߳�
		emit StartThread();	
	}		
}

/*
����ROI����
*/
void MainWindow::on_Import_clicked()
{
	QString  csvFileName = QFileDialog::getOpenFileName(this, "���������ļ�", ".", "csv files(*.csv)");  //�����ļ�·��	
	QFile file(csvFileName);
	if (csvFileName.isEmpty())		return; //δѡ���ļ�   
	else
	{
		//���ļ�
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
		QStringList list;//���ڼ�¼�����ļ��е�����
		list.clear();//����б�
		QTextStream in(&file);
		//���ж�ȡ��ֱ�����һ��
		int i = 0;
		m_roipars.reserve(0);//����ղ����б�Ϊ��ȡ��������׼��
		while (!in.atEnd())
		{
			QString fileLine = in.readLine();//���ж�ȡ
			list = fileLine.split(",", QString::SkipEmptyParts);//��ÿ�е�������","�ָ�	
																//��ȡ��������
			if (i == 2)
			{
				roi_parameters *m_roi_parameters = new roi_parameters;//Ϊ���ڶ�ȡ���ݵ���ʱ�ṹ������ڴ�
																	  //��ȡ���е�����
				m_roi_parameters->x = list.at(0).toInt();
				m_roi_parameters->y = list.at(1).toInt();
				m_roi_parameters->width = list.at(2).toInt();
				m_roi_parameters->height = list.at(3).toInt();
				m_roipars.push_back(m_roi_parameters);//���¶�ȡ�Ĳ�����������б���													 
			}
			i++;
		}

	}

	file.close();//��ȡ��ϣ��ر��ļ�
}

/*
ͼ���������ۺ���
������������ʾ������ͼ��
*/
void MainWindow::slot_handle_finish()
{
	m_thread->setFlag(); //���ý��̱�־λ
	subthread->quit();//�˳��ӽ���
	subthread->wait();//�ȴ��ӽ��̽���
	
	dstImg.load("C:\\Users\\16935\\Desktop\\BatteryImg\\1(new).jpg");//����Ҫ��ʾ��ͼ��	
	
	sence->clear(); //��ճ���
	sence->addPixmap(QPixmap::fromImage(dstImg));   //�򳡾��м���ͼ��
    ui.graphicsView->setScene(sence);	            //������ͼ�����ӳ���
	
}


/*
�رս���
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
�����ý���
*/
void MainWindow::on_Setting_clicked()
{	
	sss.show();
}
