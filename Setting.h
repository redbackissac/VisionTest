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
	struct item_rect               //��¼�����ľ��ο�ļ�������Ľṹ��
	{
		int32_t x, y, width, height;
	};
private:

	Calibration *m_calibration;//�궨

	QButtonGroup *btngroup_missions;//ѡ���������͵�buttongroup
	typedef QList<GraphicsRectItem*> rectItems;//�������л��Ƶľ��ε�QList
	
	VecRoiParas vec_roipars;//roi��������
	QString fileName_example;//�궨����ļ�·��
	QString fileName_CSV;//����roi���õ�csv�ļ�·��

	vector<Mission> vec_Missions;//��������
	Mission m_mission = {};//��ʱ����
	int tmp_ObjNum = 0;//��ʱ������

	
	void setTypeButton();//�������Ͱ�ť״̬
	bool obj_isComp();//�ж������Ƿ�һ������ȫ
	void setObjIDButton();//����ѡȡ����ť״̬
	void setConfirmButton();//����ȷ������ť״̬
	void setLabelObj();//��������label��ʾ����
	QString missionType2string(const TypeOfMission type);//��������תΪ�ַ���
	QString missionObj2string(const int obj);//�������תΪ�ַ���
	void addMission2Table();//��������������ӵ���ʾ����ı����

	void calROIPars(const rectItems m_rectItems, const Point2i Pic, VecRoiParas &vec_roipars);//���ݻ����ľ��ο����roi����
	
private slots:

	
    void buildMission();//��������

	void on_savemission_clicked();//��������
	void on_createROI_clicked(); //����ROI
	void on_selectExample_clicked();//ѡȡ�궨��ͼ��

	void on_confirmMission_clicked();//ȷ������
	void on_doCalibration_clicked();//�궨
	void on_saveRoi_clicked();//��������
	void on_Exist_clicked();      //�˳����ý���	
	void on_selectObj_clicked();

	void on_selectCalib_clicked();//ѡ��궨��ͼ��
//	void on_saveCalib_clicked();//����궨���

};


