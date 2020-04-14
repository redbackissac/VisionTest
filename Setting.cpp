#pragma once
#pragma execution_character_set("utf-8")

#include"Setting.h"

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()


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
	
	m_mission.clear();//��ʱ�������

	/*��ť���ʼ��*/
	btngroup_missions = new QButtonGroup;
	btngroup_missions->addButton(ui.radioButton_none,0);
	btngroup_missions->addButton(ui.radioButton_straightness,1);
	btngroup_missions->addButton(ui.radioButton_perpendicularity, 2);
	btngroup_missions->addButton(ui.radioButton_parallelism,3);
	btngroup_missions->addButton(ui.radioButton_distance,4);
	btngroup_missions->setExclusive(true);
	connect(btngroup_missions, SIGNAL(buttonClicked(int)), this, SLOT(buildMission()));//�����ť��ʼ��������
		
	setObjIDButton();
	setTypeButton();
	setConfirmButton();
	setLabelObj();
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
		}		
	}		
}






/*
������roi
*/
void Setting::on_createROI_clicked()
{
	myScene->creatRect();//�����¾���	
}

/*
����roi����
*/
void Setting::on_saveRoi_clicked()
{
	ConfigDataBase my_db;
	calROIPars(myScene->m_rectItems, Pic, vec_roipars);
	int roi_ID = 0;
	for (auto it_roipars : vec_roipars)
	{
		//��������
		my_db.insert_roi(roi_ID, it_roipars[0], it_roipars[1], it_roipars[2], it_roipars[3]);
		roi_ID++;
	}
}







/*
�ж������Ƿ��ѽ������
*/
bool Setting::obj_isComp()
{
	switch (m_mission.type)
	{
	case NONE:
		return false;
		break;
	case STRAIGHTNESS:
		if (m_mission.vec_object.size() == 1)
			return true;
		else return false;
		break;
	case PARALLELISM:
		if (m_mission.vec_object.size() == 2)
			return true;
		else return false;
		break;
	case PERPENDICULARITY:
		if (m_mission.vec_object.size() == 2)
			return true;
		else return false;
		break;
	case DISTANCE:
		if (m_mission.vec_object.size() == 2)
			return true;
		else return false;
		break;
	}	
}

/*
�����������Ͱ�ť��ѡ״̬
*/
void Setting::setTypeButton()
{
	if (m_mission.type == NONE)//��������δȷ��ʱ��ť�ſ���
		for (auto it_buttons : btngroup_missions->buttons())//����group�еİ�ť
			it_buttons->setEnabled(true);//��ť����
	else //����������ȷ��
		for (auto it_buttons : btngroup_missions->buttons())//����group�еİ�ť
			it_buttons->setEnabled(false);//��ť������			
}

/*
������Ӷ���ť����״̬
*/
void Setting::setObjIDButton()
{
	if(m_mission.type != NONE)//��ȷ����������
		if (obj_isComp())//����������ȫ����
			ui.selectObj->setEnabled(false);//��Ӷ���ť������
		else ui.selectObj->setEnabled(true);//��Ӷ���ť����
	else
		ui.selectObj->setEnabled(false);//��Ӷ���ť������
	
}

/*
����ȷ���������ť����״̬
*/
void Setting::setConfirmButton()
{
	if (!obj_isComp())//������δ��ȫ����
		ui.confirmMission->setEnabled(false);//ȷ���������ť������
	else//������ȫ��������
		ui.confirmMission->setEnabled(true);//ȷ���������ť����
}

/*
��������label��ʾ����
*/
void Setting::setLabelObj()
{
	
	if (m_mission.type != NONE)//���������Ѿ�ȷ��
	{
		/*obj1*/
		if (m_mission.vec_object.size() == 0)//һ������ûѡ��
			ui.label_obj1->setText("ѡ�����1");
		else
			ui.label_obj1->setText("FAI" + QString::number(m_mission.vec_object[0]));
			/*obj2*/
		if (m_mission.type == STRAIGHTNESS)//������Ϊֱ�߶ȣ�ֻ��һ������
			ui.label_obj2->setText("");//ɶ������ʾ
		else
		{
			if (m_mission.vec_object.size() == 0)//ɶ����ûѡ
				ui.label_obj2->setText("");//ɶ������ʾ
			else if (m_mission.vec_object.size() == 1)//ֻѡ����һ������
				ui.label_obj2->setText("ѡ�����2");				
			else
				ui.label_obj2->setText("FAI" + QString::number(m_mission.vec_object[1]));
		}
	}
	else //��������δȷ����ɶ������ʾ
	{
		ui.label_obj1->setText("");
		ui.label_obj2->setText("");
	}
	
}

QString Setting::missionType2string(const TypeOfMission type)
{
	QString missionType;
	switch (type)
	{
	case NONE:
		missionType = "��";
		break;
	case STRAIGHTNESS:
		missionType = "ֱ�߶�";
		break;
	case PERPENDICULARITY:
		missionType = "��ֱ��";
		break;
	case PARALLELISM:
		missionType = "ƽ�ж�";
		break;
	case DISTANCE:
		missionType = "����";
		break;
	default:
		missionType = "����";
		break;
	}
	return missionType;
}

QString Setting::missionObj2string(const int obj)
{
	QString strobj = "FAI" + QString::number(obj);
	return strobj;
}

/*
����ʾ����ı�����������һ������
*/
void Setting::addMission2Table()
{
	int rowCount = ui.missiontable->rowCount();
	ui.missiontable->insertRow(rowCount);//���һ��
	ui.missiontable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(rowCount)));
	ui.missiontable->setItem(rowCount,1,new QTableWidgetItem(missionType2string(m_mission.type)));
	ui.missiontable->setItem(rowCount, 2, new QTableWidgetItem(missionObj2string(m_mission.vec_object[0])));
	if (m_mission.vec_object.size() == 2)
		ui.missiontable->setItem(rowCount, 3, new QTableWidgetItem(missionObj2string(m_mission.vec_object[1])));
	else
		ui.missiontable->setItem(rowCount, 3, new QTableWidgetItem("��"));	
}

/*
��rectitemsת��Ϊroi����
*/
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
}

/*
��������
*/
void Setting::buildMission()
{	
	switch (btngroup_missions->checkedId())//ѡ�еİ�ť
	{
	case 1:
		m_mission.type = STRAIGHTNESS;
		break;
	case 2:
		m_mission.type = PERPENDICULARITY;
		break;
	case 3:
		m_mission.type = PARALLELISM;
		break;
	case 4:
		m_mission.type = DISTANCE;
		break;
	default:
		m_mission.type = NONE;
		break;
	}
	//�������ð�ť״̬
	setObjIDButton();//ѡȡ����ť����
	setTypeButton();//�������Ͱ�ť������
	setLabelObj();
}

/*
ѡȡ����
*/
void Setting::on_selectObj_clicked()
{
	(m_mission.vec_object).push_back(myScene->getSelectedNum());//��ȡ����id	
	setObjIDButton();//����������״������ѡȡ����ť����״̬
	setConfirmButton();//����������״������ȷ���������ť����״̬
	setLabelObj();
}

void Setting::on_selectCalib_clicked()
{
	m_calibration = new Calibration;
	m_calibration->srcImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
	//fileName_example = QFileDialog::getOpenFileName(this, "�򿪱궨��ͼƬ", ".", "Image files(*.bmp *.jpg *.png)");  //��ʵ��ͼƬ
	//if (fileName_example.isEmpty())
	//	return; //δѡ��ͼ��                                    
	//else
	//{
	//	if (!(QSrc.load(fileName_example))) //������ͼ�񴦴�   
	//	{
	//		QMessageBox::warning(this, tr("����"), tr("��ͼ��ʧ��!"));
	//		return;
	//	}
	//	else
	//	{
	//		//m_calibration->srcImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//��ȡͼ�񣬲��ı�ͨ����
	//		//QSrc = QSrc.scaled(1024, 576, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  //��ͼƬ����Ϊ����ͼһ����		
	//		m_pPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(QSrc));
	//		m_pPixmapItem->setPos(-m_pPixmapItem->pixmap().width() / 2, -m_pPixmapItem->pixmap().height() / 2);
	//		myScene->addItem(m_pPixmapItem);			
	//	}
	//}

}

/*
ȷ������
*/
void Setting::on_confirmMission_clicked()
{
	vec_Missions.push_back(m_mission);//����ʱ������ӵ�����������
	addMission2Table();
	setObjIDButton();//��������ȫ������������Ӷ���ť������
	m_mission.clear();//�����ʱ����
	
	setConfirmButton();//������ȷ�ϣ���ȷ�ϰ�ť��Ϊ������
	btngroup_missions->button(0)->setChecked(true);//�����������Ͱ�ťΪNONE
	setTypeButton();//���������ѽ������ص���ʼ״̬������ѡ��ť����
	setLabelObj();
}

void Setting::on_doCalibration_clicked()
{
	ConfigDataBase db;
	m_calibration = new Calibration;
	m_calibration->vec_roipars.clear();
	db.read_roi(m_calibration->vec_roipars);//��ȡroi����
	m_calibration->getK();
	db.update_LineType(m_calibration->vec_linetype);
}

/*
�����趨������
*/
void Setting::on_savemission_clicked()
{
	ConfigDataBase my_db;
	int mission_ID = 0;
	for (auto it_mission : vec_Missions)//������������
	{
		my_db.insert_Mission(mission_ID, it_mission);		
		mission_ID++;
	}
}


/*
�˳����ý���
*/
void Setting::on_Exist_clicked()
{
	this->close();
}







