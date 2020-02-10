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
#include "interactive_view.h"

#include "GraphicsRect/graphicsscene.h"


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
	typedef QList<GraphicsRectItem*> rectItems;//存贮所有绘制的矩形的QList
public:
	QImage QSrc;          //用于显示的QImage	
	GraphicsScene *scene ;//用于显示矩形框的场景
	InteractiveView *SettingView;//交互式视图
	QGraphicsPixmapItem *m_pPixmapItem;//用于显示电池图像的item

public:
	int32_t pic_width ;            //图像在场景中的宽度
	int32_t pic_height ;           //图像在场景中的高度
	int32_t pic_x ;                //图像在场景中左上角的x坐标
	int32_t pic_y ;                //图像在场景中左上角的y坐标
	struct item_rect               //记录画出的矩形框的几何坐标的结构体
	{
		int32_t x, y, width, height;
	};


private slots:
	void on_New_clicked();        //创建新配置
	void on_Save_clicked();       //保存配置
	void on_Exist_clicked();      //退出设置界面
	void on_createRect_clicked(); //创建矩形
};
