#pragma once
#include"ui_Setting.h"
#include <QWidget>
#include <QFiledialog>
#include <QPushButton>
#include <QMessageBox>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <thread>
#include <QButtonGroup>
#include <QThread>
#include "interactive_view.h"
#include "GraphicsRect/graphicsscene.h"
#include "calibration.h"
#include "configdatabase.h"

//用于打印调试信息
#include <iostream>
using namespace std;


namespace Ui {
	class Setting;
}

class  Setting :public QWidget {
	Q_OBJECT
public:
	
	Setting(QWidget*parents = 0);
	~Setting() {};	
private:
	Ui::Setting ui;	
public:
	QImage QSrc;          //用于显示的QImage	
	GraphicsScene *myScene ;//用于显示矩形框的场景
	InteractiveView *SettingView;//交互式视图
	QGraphicsPixmapItem *m_pPixmapItem;//用于显示电池图像的item

public:
	Point2i Pic;                     //图像左上角在场景中的坐标(x,y)
	struct item_rect               //记录画出的矩形框的几何坐标的结构体
	{
		int32_t x, y, width, height;
	};
private:

	Calibration *m_calibration;//标定

	QButtonGroup *btngroup_missions;//选择任务类型的buttongroup
	typedef QList<GraphicsRectItem*> rectItems;//存贮所有绘制的矩形的QList
	
	VecRoiParas vec_roipars;//roi参数向量
	QString fileName_example;//标定板的文件路径
	QString fileName_CSV;//保存roi设置的csv文件路径

	vector<Mission> vec_Missions;//任务向量
	Mission m_mission = {};//临时任务
	int tmp_ObjNum = 0;//临时对象标号

	
	void setTypeButton();//设置类型按钮状态
	bool obj_isComp();//判断任务是否一建立完全
	void setObjIDButton();//设置选取对象按钮状态
	void setConfirmButton();//设置确认任务按钮状态
	void setLabelObj();//设置任务label显示内容
	QString missionType2string(const TypeOfMission type);//任务类型转为字符串
	QString missionObj2string(const int obj);//任务对象转为字符串
	void addMission2Table();//将建立的任务添加到显示任务的表格中

	void calROIPars(const rectItems m_rectItems, const Point2i Pic, VecRoiParas &vec_roipars);//根据画出的矩形框计算roi参数
	
private slots:

	
    void buildMission();//建立任务

	void on_savemission_clicked();//保存任务
	void on_createROI_clicked(); //创建ROI
	void on_selectExample_clicked();//选取标定板图像

	void on_confirmMission_clicked();//确认任务
	void on_doCalibration_clicked();//标定
	void on_saveRoi_clicked();//保存设置
	void on_Exist_clicked();      //退出设置界面	
	void on_selectObj_clicked();

	void on_selectCalib_clicked();//选择标定板图像
//	void on_saveCalib_clicked();//保存标定结果

};


