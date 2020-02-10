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
	typedef QList<GraphicsRectItem*> rectItems;//�������л��Ƶľ��ε�QList
public:
	QImage QSrc;          //������ʾ��QImage	
	GraphicsScene *scene ;//������ʾ���ο�ĳ���
	InteractiveView *SettingView;//����ʽ��ͼ
	QGraphicsPixmapItem *m_pPixmapItem;//������ʾ���ͼ���item

public:
	int32_t pic_width ;            //ͼ���ڳ����еĿ��
	int32_t pic_height ;           //ͼ���ڳ����еĸ߶�
	int32_t pic_x ;                //ͼ���ڳ��������Ͻǵ�x����
	int32_t pic_y ;                //ͼ���ڳ��������Ͻǵ�y����
	struct item_rect               //��¼�����ľ��ο�ļ�������Ľṹ��
	{
		int32_t x, y, width, height;
	};


private slots:
	void on_New_clicked();        //����������
	void on_Save_clicked();       //��������
	void on_Exist_clicked();      //�˳����ý���
	void on_createRect_clicked(); //��������
};
