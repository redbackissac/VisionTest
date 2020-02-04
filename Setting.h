#pragma once
#include"ui_Setting.h"
#include <stdlib.h>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <qtimer.h>
#include <qdatetime.h>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QScrollArea>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTextBrowser>
#include <iostream>
#include <string>
#include <QFiledialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include "interactive_view.h"
#include <QGraphicsPixmapItem>
#include "GraphicsRect/graphicsscene.h"
#include <QFile>

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
