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
#include "interactive_view.h"
#include "GraphicsRect/graphicsscene.h"
#include "calibration.h"
#include "mydatabase.h"

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
    //int32_t pic_width ;            //图像在场景中的宽度
	//int32_t pic_height ;           //图像在场景中的高度
	//int32_t pic_x ;                //图像在场景中左上角的x坐标
	//int32_t pic_y ;                //图像在场景中左上角的y坐标
	struct item_rect               //记录画出的矩形框的几何坐标的结构体
	{
		int32_t x, y, width, height;
	};
private:
	typedef QList<GraphicsRectItem*> rectItems;//存贮所有绘制的矩形的QList
	
	VecRoiParas vec_roipars;//roi参数向量
	QString fileName_example;//标定板的文件路径
	QString fileName_CSV;//保存roi设置的csv文件路径

	vector<Mission> vec_Missions;//任务向量
	Mission m_mission = {};//临时任务
	int tmp_ObjNum = 0;//临时对象标号

	void calROIPars(const rectItems m_rectItems, const Point2i Pic, VecRoiParas &vec_roipars);//根据画出的矩形框计算roi参数

private slots:
	//void on_selectExamplePic_clicked();        //选取示例图片
	void on_createROI_clicked(); //创建ROI
	void on_selectExample_clicked();//选取标定板图像
	void on_newMission_clicked();//新建任务
	void on_confirmMission_clicked();//确认任务
	//void on_doCalibration_clicked();//标定
	void on_saveSetting_clicked();//保存设置
	void on_Exist_clicked();      //退出设置界面	
	void on_look_clicked();       //点击查看调试信息
	void on_getsb_clicked();
};


//每个类型电池的配置
class MConfiguration
{
public:
	vector<ObjectOfMission> vec_Obj;//任务对象向量
	//VecRoiParas vec_roipars;//roi参数向量
	vector<Mission> vec_Missions;//任务向量

};
