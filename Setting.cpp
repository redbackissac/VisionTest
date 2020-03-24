#pragma once
#pragma execution_character_set("utf-8")

#include"Setting.h"

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()

bool flgObjHasBeenSet = false;//��������Ƿ����ñ�־λ

/*
���캯��
*/
Setting::Setting(QWidget*parents )
{
	ui.setupUi(this);	
	SettingView = new InteractiveView(this);
    SettingView->setGeometry(QRect(0, 0, 1024, 576));      //�����ӿ��ڴ����е�λ��
	//SettingView->setGeometry(QRect(0, 0, this->width(), this->width()*0.5625));      //�����ӿ��ڴ����е�λ��,����Ӧ���ڴ�С�������ݺ��Ϊ1024/576
	myScene = new GraphicsScene;                             //�½��Զ��峡��
	SettingView->setScene(myScene);	                       //������ͼ�����ӳ���	
	
}

/*
�½�����
*/
void Setting::on_selectExample_clicked()
{
	fileName_example = QFileDialog::getOpenFileName(this, "��ʵ��ͼƬ", ".", "Image files(*.bmp *.jpg *.png)");  //��ʵ��ͼƬ
	if (fileName_example.isEmpty())		
		return; //δѡ��ͼ��                                    
	else
	{		
		if (!(QSrc.load(fileName_example))) //������ͼ�񴦴�   
		{			
			QMessageBox::warning(this, tr("����"), tr("��ͼ��ʧ��!"));		
			return;
		}
		else
		{
			//QSrc = QSrc.scaled(1024, 576, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  //��ͼƬ����Ϊ����ͼһ����		
			m_pPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(QSrc));                             	
			m_pPixmapItem->setPos(- m_pPixmapItem->pixmap().width() / 2,	-m_pPixmapItem->pixmap().height() / 2); 
			myScene->addItem(m_pPixmapItem);
			//��¼ͼ���ڳ����е�����			
			QRect rect_pic = m_pPixmapItem->sceneBoundingRect().toRect();
			Pic.x = rect_pic.topLeft().x();
			Pic.y = rect_pic.topLeft().y();	



			////��¼ͼ���ڳ����е����꼰�ߴ�				
			//QRect rect_pic = m_pPixmapItem->sceneBoundingRect().toRect();
			//pic_x = rect_pic.topLeft().x();
			//pic_y = rect_pic.topLeft().y();			
			//pic_width = rect_pic.width();
			//pic_height = rect_pic.height();
			////��ӡ������Ϣ
			//cout << "pic_x:" << pic_x << endl;	
			//cout << "pic_y:" << pic_y << endl;
			//cout << "pic_width:" << pic_width << endl;	
			//cout << "pic_height:" << pic_height << endl;
		}		
	}		
}

/*
�˳�
*/
void Setting::on_Exist_clicked()
{		
	this-> close();	
}

/*
�����¾���
*/
void Setting::on_createROI_clicked()
{
	myScene->creatRect();//�����¾���	
}


void Setting::calROIPars(const rectItems m_rectItems, const Point2i Pic, VecRoiParas &vec_roipars)
{
	//��������item	
	for (auto it_rect : m_rectItems)
	{
		QRect rect = it_rect->sceneBoundingRect().toRect();//item�ı߽��
	    //����������
		Vec4i roipar;
		roipar[0] = rect.topLeft().x() - Pic.x;
		roipar[1] = rect.topLeft().y() - Pic.y;
		roipar[2] = rect.width();
		roipar[3] = rect.height();
		vec_roipars.push_back(roipar);
	}
	//for (rectItems::iterator it = m_rectItems.begin(); it != m_rectItems.end(); ++it)
	//{
	//	GraphicsRectItem *item = *it;//����ת��
	//	QRect rect = item->sceneBoundingRect().toRect();//item�ı߽��
	//	//����������
	//	Vec4i roipar;
	//	roipar[0] = rect.topLeft().x() - pic_x;
	//	roipar[1] = rect.topLeft().y() - pic_y;
	//	roipar[2] = rect.width();
	//	roipar[3] = rect.height();
	//	vec_roipars.push_back(roipar);	
	//}
}

//��ȡ����������߳�
void waitForObj(bool &flg,  Mission &m_mission, int &tmp_ObjNum)
{
	//cout << "subID: " << this_thread::get_id() << endl;
	while (!flg) {}//�ȴ�obj��ѡ��
	flgObjHasBeenSet = false;//��־λ��λ
	(m_mission.vec_object).push_back(tmp_ObjNum);
	tmp_ObjNum = 0;//��ʱ����������
	cout << "������ѡ��" << endl;
}
//�½�����
void Setting::on_newMission_clicked()
{
	bool j = 1;
	m_mission.clear();//��ʱ�������
	std::thread waitOBJ(waitForObj, std::ref(flgObjHasBeenSet), std::ref(m_mission), std::ref(tmp_ObjNum));
	waitOBJ.detach();
	//cout << "MainID:" << this_thread::get_id() << endl;
	j = 0;
}

//ȷ������
void Setting::on_confirmMission_clicked()
{
	vec_Missions.push_back(m_mission);
	m_mission.clear();//�����ʱ����
}

void Setting::on_getsb_clicked()
{
	tmp_ObjNum = myScene->getSelectedNum();
	flgObjHasBeenSet = true;
	
}


/*
��������
*/
void Setting::on_saveSetting_clicked()
{	
	
	//�������ݵ��ļ�·��
	QString csvFileName = QFileDialog::getSaveFileName(this, "��������", ".", "csv files(*.csv)");  //ѡ�񱣴�λ�ã��༭�ļ�����
	QFile file(csvFileName);
	if (!file.exists())		//�ļ������ڵ�ʱ�½�
	{
		file.open(QIODevice::WriteOnly);
		QTextStream txtOutPut(&file);
		//����
		txtOutPut << "Unit(%)\n";
		txtOutPut << "TopLeft_x,TopLeft_y,width,height\n";	//ע�⣬ÿ�����ݽ�����Ҫ�ӻ��з�
		file.close();
	}
	//���ļ�
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream txtOutPut(&file);
	calROIPars(myScene->m_rectItems,Pic,vec_roipars);
	for (auto it_roipars : vec_roipars)
	{
		//��������
		QString msg = QString::number(it_roipars[0]) + ","\
			+ QString::number(it_roipars[1]) + ","\
			+ QString::number(it_roipars[2]) + ","\
			+ QString::number(it_roipars[3]) + "\n";
	    txtOutPut << msg;
	    file.flush();//���ļ���д������
	}
	file.close();//������ɺ�ر��ļ�
	//��������item	
	//for (rectItems::iterator it = myScene->m_rectItems.begin(); it != myScene->m_rectItems.end(); ++it)
	//{		
	//	GraphicsRectItem *item = *it;//����ת��
	//	QRect rect = item->sceneBoundingRect().toRect();//item�ı߽��
	//	//����������
	//	Vec4i roipar;
	//	roipar[0] = rect.topLeft().x() - pic_x;
	//	roipar[1] = rect.topLeft().y() - pic_y;
	//	roipar[2] = rect.width();
	//	roipar[3] = rect.height();
	//	vec_roipars.push_back(roipar);
	//	/*item_rect rectSize;
	//	rectSize.x = rect.topLeft().x() - pic_x;
	//	rectSize.y = rect.topLeft().y() - pic_y;
	//	rectSize.width = rect.width();
	//	rectSize.height = rect.height();*/
	//	//��������
	///*	QString msg = QString::number(rectSize.x) + ","\
	//		+ QString::number(rectSize.y) + ","\
	//		+ QString::number(rectSize.width) + ","\
	//		+ QString::number(rectSize.height) + "\n";*/
	//	//txtOutPut << msg;
	//	file.flush();//���ļ���д������
	//}	
	
}


void Setting::on_look_clicked()
{
	////��������item	
	//for (rectItems::iterator it = myScene->m_rectItems.begin(); it != myScene->m_rectItems.end(); ++it)
	//{
	//	GraphicsRectItem *item = *it;//����ת��
	//	QRect rect = item->sceneBoundingRect().toRect();//item�ı߽��
	//													//����������
	//													//��ӡ����
	//	cout << "rectregion.x" << rect.topLeft().x() - pic_x << endl;
	//	cout << "rectregion.y" << rect.topLeft().y() - pic_y << endl;
	//	cout << "rectregion.width" << rect.width() << endl;
	//	cout << "rectregion.height" << rect.height() << endl;

		//item_rect rectSize;
		//rectSize.x = (rect.topLeft().x() - pic_x) * 100 / pic_width;
		//rectSize.y = (rect.topLeft().y() - pic_y) * 100 / pic_height;
		//rectSize.width = rect.width() * 100 / pic_width;
		//rectSize.height = rect.height() * 100 / pic_height;

	/*	item_rect rectSize;
		rectSize.x = rect.topLeft().x() - pic_x;
		rectSize.y = rect.topLeft().y() - pic_y;
		rectSize.width = rect.width();
		rectSize.height = rect.height();		*/
	//}
}