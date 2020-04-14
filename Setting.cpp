#pragma once
#pragma execution_character_set("utf-8")

#include"Setting.h"

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()


/*
构造函数
*/
Setting::Setting(QWidget*parents )
{
	ui.setupUi(this);	
	SettingView = new InteractiveView(this);
    SettingView->setGeometry(QRect(0, 0, 1024, 576));      //设置视口在窗口中的位置
	//SettingView->setGeometry(QRect(0, 0, this->width(), this->width()*0.5625));      //设置视口在窗口中的位置,自适应窗口大小，保持纵横比为1024/576
	myScene = new GraphicsScene;                             //新建自定义场景
	SettingView->setScene(myScene);	                       //向界面的图像口添加场景
	
	m_mission.clear();//临时任务清空

	/*按钮组初始化*/
	btngroup_missions = new QButtonGroup;
	btngroup_missions->addButton(ui.radioButton_none,0);
	btngroup_missions->addButton(ui.radioButton_straightness,1);
	btngroup_missions->addButton(ui.radioButton_perpendicularity, 2);
	btngroup_missions->addButton(ui.radioButton_parallelism,3);
	btngroup_missions->addButton(ui.radioButton_distance,4);
	btngroup_missions->setExclusive(true);
	connect(btngroup_missions, SIGNAL(buttonClicked(int)), this, SLOT(buildMission()));//点击按钮开始建立任务
		
	setObjIDButton();
	setTypeButton();
	setConfirmButton();
	setLabelObj();
}

/*
新建配置
*/
void Setting::on_selectExample_clicked()
{
	fileName_example = QFileDialog::getOpenFileName(this, "打开实例图片", ".", "Image files(*.bmp *.jpg *.png)");  //打开实例图片
	if (fileName_example.isEmpty())		
		return; //未选择图像                                    
	else
	{		
		if (!(QSrc.load(fileName_example))) //若加载图像处错   
		{			
			QMessageBox::warning(this, tr("错误"), tr("打开图像失败!"));		
			return;
		}
		else
		{
			//QSrc = QSrc.scaled(1024, 576, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  //将图片缩放为与视图一样大		
			m_pPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(QSrc));                             	
			m_pPixmapItem->setPos(- m_pPixmapItem->pixmap().width() / 2,	-m_pPixmapItem->pixmap().height() / 2); 
			myScene->addItem(m_pPixmapItem);
			//记录图像在场景中的坐标			
			QRect rect_pic = m_pPixmapItem->sceneBoundingRect().toRect();
			Pic.x = rect_pic.topLeft().x();
			Pic.y = rect_pic.topLeft().y();	
		}		
	}		
}






/*
创建新roi
*/
void Setting::on_createROI_clicked()
{
	myScene->creatRect();//绘制新矩形	
}

/*
保存roi设置
*/
void Setting::on_saveRoi_clicked()
{
	ConfigDataBase my_db;
	calROIPars(myScene->m_rectItems, Pic, vec_roipars);
	int roi_ID = 0;
	for (auto it_roipars : vec_roipars)
	{
		//保存数据
		my_db.insert_roi(roi_ID, it_roipars[0], it_roipars[1], it_roipars[2], it_roipars[3]);
		roi_ID++;
	}
}







/*
判断任务是否已建立完成
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
设置任务类型按钮可选状态
*/
void Setting::setTypeButton()
{
	if (m_mission.type == NONE)//任务类型未确定时按钮才可用
		for (auto it_buttons : btngroup_missions->buttons())//遍历group中的按钮
			it_buttons->setEnabled(true);//按钮可用
	else //任务类型已确定
		for (auto it_buttons : btngroup_missions->buttons())//遍历group中的按钮
			it_buttons->setEnabled(false);//按钮不可用			
}

/*
设置添加对象按钮可用状态
*/
void Setting::setObjIDButton()
{
	if(m_mission.type != NONE)//已确定任务类型
		if (obj_isComp())//若任务已完全建立
			ui.selectObj->setEnabled(false);//添加对象按钮不可用
		else ui.selectObj->setEnabled(true);//添加对象按钮可用
	else
		ui.selectObj->setEnabled(false);//添加对象按钮不可用
	
}

/*
设置确认添加任务按钮可用状态
*/
void Setting::setConfirmButton()
{
	if (!obj_isComp())//若任务未完全建立
		ui.confirmMission->setEnabled(false);//确认添加任务按钮不可用
	else//若已完全建立任务
		ui.confirmMission->setEnabled(true);//确认添加任务按钮可用
}

/*
设置任务label显示内容
*/
void Setting::setLabelObj()
{
	
	if (m_mission.type != NONE)//任务类型已经确定
	{
		/*obj1*/
		if (m_mission.vec_object.size() == 0)//一个对象都没选择
			ui.label_obj1->setText("选择对象1");
		else
			ui.label_obj1->setText("FAI" + QString::number(m_mission.vec_object[0]));
			/*obj2*/
		if (m_mission.type == STRAIGHTNESS)//若类型为直线度，只有一个对象
			ui.label_obj2->setText("");//啥都不显示
		else
		{
			if (m_mission.vec_object.size() == 0)//啥都还没选
				ui.label_obj2->setText("");//啥都不显示
			else if (m_mission.vec_object.size() == 1)//只选择了一个对象
				ui.label_obj2->setText("选择对象2");				
			else
				ui.label_obj2->setText("FAI" + QString::number(m_mission.vec_object[1]));
		}
	}
	else //任务类型未确定，啥都不显示
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
		missionType = "无";
		break;
	case STRAIGHTNESS:
		missionType = "直线度";
		break;
	case PERPENDICULARITY:
		missionType = "垂直度";
		break;
	case PARALLELISM:
		missionType = "平行度";
		break;
	case DISTANCE:
		missionType = "距离";
		break;
	default:
		missionType = "错误";
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
向显示任务的表格中添加最新一条任务
*/
void Setting::addMission2Table()
{
	int rowCount = ui.missiontable->rowCount();
	ui.missiontable->insertRow(rowCount);//添加一行
	ui.missiontable->setItem(rowCount, 0, new QTableWidgetItem(QString::number(rowCount)));
	ui.missiontable->setItem(rowCount,1,new QTableWidgetItem(missionType2string(m_mission.type)));
	ui.missiontable->setItem(rowCount, 2, new QTableWidgetItem(missionObj2string(m_mission.vec_object[0])));
	if (m_mission.vec_object.size() == 2)
		ui.missiontable->setItem(rowCount, 3, new QTableWidgetItem(missionObj2string(m_mission.vec_object[1])));
	else
		ui.missiontable->setItem(rowCount, 3, new QTableWidgetItem("无"));	
}

/*
将rectitems转换为roi参数
*/
void Setting::calROIPars(const rectItems m_rectItems, const Point2i Pic, VecRoiParas &vec_roipars)
{
	//遍历所有item	
	for (auto it_rect : m_rectItems)
	{
		QRect rect = it_rect->sceneBoundingRect().toRect();//item的边界框
	    //相对坐标计算
		Vec4i roipar;
		roipar[0] = rect.topLeft().x() - Pic.x;
		roipar[1] = rect.topLeft().y() - Pic.y;
		roipar[2] = rect.width();
		roipar[3] = rect.height();
		vec_roipars.push_back(roipar);
	}
}

/*
建立任务
*/
void Setting::buildMission()
{	
	switch (btngroup_missions->checkedId())//选中的按钮
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
	//重新设置按钮状态
	setObjIDButton();//选取对象按钮可用
	setTypeButton();//任务类型按钮不可用
	setLabelObj();
}

/*
选取对象
*/
void Setting::on_selectObj_clicked()
{
	(m_mission.vec_object).push_back(myScene->getSelectedNum());//获取对象id	
	setObjIDButton();//根据任务建立状况设置选取对象按钮可用状态
	setConfirmButton();//根据任务建立状况设置确认添加任务按钮可用状态
	setLabelObj();
}

void Setting::on_selectCalib_clicked()
{
	m_calibration = new Calibration;
	m_calibration->srcImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(tt).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数
	//fileName_example = QFileDialog::getOpenFileName(this, "打开标定板图片", ".", "Image files(*.bmp *.jpg *.png)");  //打开实例图片
	//if (fileName_example.isEmpty())
	//	return; //未选择图像                                    
	//else
	//{
	//	if (!(QSrc.load(fileName_example))) //若加载图像处错   
	//	{
	//		QMessageBox::warning(this, tr("错误"), tr("打开图像失败!"));
	//		return;
	//	}
	//	else
	//	{
	//		//m_calibration->srcImg = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(sb).jpg", IMREAD_UNCHANGED);//读取图像，不改变通道数
	//		//QSrc = QSrc.scaled(1024, 576, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  //将图片缩放为与视图一样大		
	//		m_pPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(QSrc));
	//		m_pPixmapItem->setPos(-m_pPixmapItem->pixmap().width() / 2, -m_pPixmapItem->pixmap().height() / 2);
	//		myScene->addItem(m_pPixmapItem);			
	//	}
	//}

}

/*
确认任务
*/
void Setting::on_confirmMission_clicked()
{
	vec_Missions.push_back(m_mission);//将临时任务添加到任务向量中
	addMission2Table();
	setObjIDButton();//任务已完全建立，设置添加对象按钮不可用
	m_mission.clear();//清空临时任务
	
	setConfirmButton();//任务已确认，将确认按钮设为不可用
	btngroup_missions->button(0)->setChecked(true);//重置任务类型按钮为NONE
	setTypeButton();//本轮任务已结束，回到初始状态，类型选择按钮可用
	setLabelObj();
}

void Setting::on_doCalibration_clicked()
{
	ConfigDataBase db;
	m_calibration = new Calibration;
	m_calibration->vec_roipars.clear();
	db.read_roi(m_calibration->vec_roipars);//读取roi参数
	m_calibration->getK();
	db.update_LineType(m_calibration->vec_linetype);
}

/*
保存设定的任务
*/
void Setting::on_savemission_clicked()
{
	ConfigDataBase my_db;
	int mission_ID = 0;
	for (auto it_mission : vec_Missions)//遍历所有任务
	{
		my_db.insert_Mission(mission_ID, it_mission);		
		mission_ID++;
	}
}


/*
退出设置界面
*/
void Setting::on_Exist_clicked()
{
	this->close();
}







