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

//���ڴ�ӡ������Ϣ
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
	QImage QSrc;          //������ʾ��QImage	
	GraphicsScene *myScene ;//������ʾ���ο�ĳ���
	InteractiveView *SettingView;//����ʽ��ͼ
	QGraphicsPixmapItem *m_pPixmapItem;//������ʾ���ͼ���item

public:
	Point2i Pic;                     //ͼ�����Ͻ��ڳ����е�����(x,y)
    //int32_t pic_width ;            //ͼ���ڳ����еĿ��
	//int32_t pic_height ;           //ͼ���ڳ����еĸ߶�
	//int32_t pic_x ;                //ͼ���ڳ��������Ͻǵ�x����
	//int32_t pic_y ;                //ͼ���ڳ��������Ͻǵ�y����
	struct item_rect               //��¼�����ľ��ο�ļ�������Ľṹ��
	{
		int32_t x, y, width, height;
	};
private:
	typedef QList<GraphicsRectItem*> rectItems;//�������л��Ƶľ��ε�QList
	
	VecRoiParas vec_roipars;//roi��������
	QString fileName_example;//�궨����ļ�·��
	QString fileName_CSV;//����roi���õ�csv�ļ�·��

	vector<Mission> vec_Missions;//��������
	Mission m_mission = {};//��ʱ����
	int tmp_ObjNum = 0;//��ʱ������

	void calROIPars(const rectItems m_rectItems, const Point2i Pic, VecRoiParas &vec_roipars);//���ݻ����ľ��ο����roi����

private slots:
	//void on_selectExamplePic_clicked();        //ѡȡʾ��ͼƬ
	void on_createROI_clicked(); //����ROI
	void on_selectExample_clicked();//ѡȡ�궨��ͼ��
	void on_newMission_clicked();//�½�����
	void on_confirmMission_clicked();//ȷ������
	//void on_doCalibration_clicked();//�궨
	void on_saveSetting_clicked();//��������
	void on_Exist_clicked();      //�˳����ý���	
	void on_look_clicked();       //����鿴������Ϣ
	void on_getsb_clicked();
};


//ÿ�����͵�ص�����
class MConfiguration
{
public:
	vector<ObjectOfMission> vec_Obj;//�����������
	//VecRoiParas vec_roipars;//roi��������
	vector<Mission> vec_Missions;//��������

};
