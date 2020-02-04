#include "TurnTable.h"

//���캯����ָ��������
TurnTable::TurnTable(QWidget *parent) :
	QWidget(parent)
{	
}

/*
��ʼ����ָ�����
�趨��ʼ0������λ�ã���ʼ����״̬
*/
void TurnTable::Init(int width, int height, int ZeroPos, uint8_t Plate)
{
	this->resize(width, height);                                     //�趨���

	Point = new QPointF();                                           //�����趨·������յ�

	/********************��ؼ����ֱ�ǩ��ʼ��***************************/
	label0 = new QLabel(this);
	label0->resize(this->width()*0.15, this->height()*0.15);
	label0->setScaledContents(true);

	label1 = new QLabel(this);
	label1->resize(this->width()*0.15, this->height()*0.15);
	label1->setScaledContents(true);

	label2 = new QLabel(this);
	label2->resize(this->width()*0.15, this->height()*0.15);
	label2->setScaledContents(true);

	label3 = new QLabel(this);
	label3->resize(this->width()*0.15, this->height()*0.15);
	label3->setScaledContents(true);

	label4 = new QLabel(this);
	label4->resize(this->width()*0.15, this->height()*0.15);
	label4->setScaledContents(true);

	label5 = new QLabel(this);
	label5->resize(this->width()*0.15, this->height()*0.15);
	label5->setScaledContents(true);

	label6 = new QLabel(this);
	label6->resize(this->width()*0.15, this->height()*0.15);
	label6->setScaledContents(true);

	label7 = new QLabel(this);
	label7->resize(this->width()*0.15, this->height()*0.15);
	label7->setScaledContents(true);

	labelNum0 = new QLabel(this);
	labelNum0->resize(this->width()*0.1, this->height()*0.1);
	labelNum0->setScaledContents(true);

	labelNum1 = new QLabel(this);
	labelNum1->resize(this->width()*0.1, this->height()*0.1);
	labelNum1->setScaledContents(true);

	labelNum2 = new QLabel(this);
	labelNum2->resize(this->width()*0.1, this->height()*0.1);
	labelNum2->setScaledContents(true);

	labelNum3 = new QLabel(this);
	labelNum3->resize(this->width()*0.1, this->height()*0.1);
	labelNum3->setScaledContents(true);

	labelNum4 = new QLabel(this);
	labelNum4->resize(this->width()*0.1, this->height()*0.1);
	labelNum4->setScaledContents(true);

	labelNum5 = new QLabel(this);
	labelNum5->resize(this->width()*0.1, this->height()*0.1);
	labelNum5->setScaledContents(true);

	labelNum6 = new QLabel(this);
	labelNum6->resize(this->width()*0.1, this->height()*0.1);
	labelNum6->setScaledContents(true);

	labelNum7 = new QLabel(this);
	labelNum7->resize(this->width()*0.1, this->height()*0.1);
	labelNum7->setScaledContents(true);

	/*****************************����ͼƬ��Դ********************************/
	bat = new QPixmap("./Resources/Pictures/Redbattery.png");
	Nobat = new QPixmap("./Resources/Pictures/Nobattery.png");
	Num0 = new QPixmap("./Resources/Pictures/Num0.png");
	Num1 = new QPixmap("./Resources/Pictures/Num1.png");
	Num2 = new QPixmap("./Resources/Pictures/Num2.png");
	Num3 = new QPixmap("./Resources/Pictures/Num3.png");
	Num4 = new QPixmap("./Resources/Pictures/Num4.png");
	Num5 = new QPixmap("./Resources/Pictures/Num5.png");
	Num6 = new QPixmap("./Resources/Pictures/Num6.png");
	Num7 = new QPixmap("./Resources/Pictures/Num7.png");

	/****************************������ͼƬ���ص�QLabel��*********************************/
	labelNum0->setPixmap(*Num0);
	labelNum1->setPixmap(*Num1);
	labelNum2->setPixmap(*Num2);
	labelNum3->setPixmap(*Num3);
	labelNum4->setPixmap(*Num4);
	labelNum5->setPixmap(*Num5);
	labelNum6->setPixmap(*Num6);
	labelNum7->setPixmap(*Num7);

	/*******************************������ʼ��*************************************/
	anim0 = new QPropertyAnimation();
	anim1 = new QPropertyAnimation();
	anim2 = new QPropertyAnimation();
	anim3 = new QPropertyAnimation();
	anim4 = new QPropertyAnimation();
	anim5 = new QPropertyAnimation();
	anim6 = new QPropertyAnimation();
	anim7 = new QPropertyAnimation();
	animNum0 = new QPropertyAnimation();
	animNum1 = new QPropertyAnimation();
	animNum2 = new QPropertyAnimation();
	animNum3 = new QPropertyAnimation();
	animNum4 = new QPropertyAnimation();
	animNum5 = new QPropertyAnimation();
	animNum6 = new QPropertyAnimation();
	animNum7 = new QPropertyAnimation();	

	//���ų�ʼλ��	
	Refresh(ZeroPos, Plate);
	anim0->stop();
	anim1->stop();
	anim2->stop();
	anim3->stop();
	anim4->stop();
	anim5->stop();
	anim6->stop();
	anim7->stop();
	//ֹͣ���Ŷ�����ʹ��������
	animNum0->stop();
	animNum1->stop();
	animNum2->stop();
	animNum3->stop();
	animNum4->stop();
	animNum5->stop();
	animNum6->stop();
	animNum7->stop();
}

/*
ת�̶������£�ָ��0������λ�á��������Ƿ��е��
PosZero:0������λ��
PlateCond:ת��״̬����ʵ��λ�ö������̱��Ϊ׼
*/
void TurnTable::Refresh(int PosZero, uint8_t PlateCond)
{
	//��ض���
	PosX(label0, anim0, 0, PlateCond & 1);
	PosX(label1, anim1, 45, (PlateCond >> 1) & 1);
	PosX(label2, anim2, 90, (PlateCond >> 2) & 1);
	PosX(label3, anim3, 135, (PlateCond >> 3) & 1);
	PosX(label4, anim4, 180, (PlateCond >> 4) & 1);
	PosX(label5, anim5, 225, (PlateCond >> 5) & 1);
	PosX(label6, anim6, 270, (PlateCond >> 6) & 1);
	PosX(label7, anim7, 315, (PlateCond >> 7) & 1);
	//���ֱ�Ŷ���
	NumX(PosZero, 0, labelNum0, animNum0);
	NumX(PosZero, 1, labelNum1, animNum1);
	NumX(PosZero, 2, labelNum2, animNum2);
	NumX(PosZero, 3, labelNum3, animNum3);
	NumX(PosZero, 4, labelNum4, animNum4);
	NumX(PosZero, 5, labelNum5, animNum5);
	NumX(PosZero, 6, labelNum6, animNum6);
	NumX(PosZero, 7, labelNum7, animNum7);	
}

/*
��ض���
label:��ر�ǩ����
anim:��������
startangle:��ʼ�˶�λ��
PosCond:��λ���Ƿ��е�ر�־
*/
void TurnTable::PosX(QLabel *label,  QPropertyAnimation *anim, int startangle,bool PosCond)
{
	//�����˶�·��
	QPainterPath *Path = new QPainterPath();
	Path->arcMoveTo(this->width()*0.15-label->width()*0.5, this->height()*0.15-label->height()*0.5, this->width()*0.7,this->height()*0.7, startangle);
	Path->arcTo(this->width()*0.15-label->width()*0.5, this->height()*0.15-label->height()*0.5, this->width()*0.7, this->height()*0.7, startangle, - 45);
	Point = &Path->pointAtPercent(0);
	//���ص��ͼƬ
	if(PosCond)                                                           //�е��
		label->setPixmap(*bat);
	else                                                                  //�޵��
		label->setPixmap(*Nobat);                
	//���ö���
	anim->setTargetObject(label);                                         //���ö�������
	anim->setPropertyName("pos");                                         //���ö�������Ϊλ��
	anim->setDuration(400);                                               //����ʱ��400ms
	anim->setStartValue(Path->pointAtPercent(0));                         //���ö������
	for (int i = 0; i < 101; i++)                                         //����100���ؼ�֡
	{		
		anim->setKeyValueAt((float)i/100, Path->pointAtPercent((float)i / 100)); 
	}
	anim->setEndValue(Path->pointAtPercent(1));                           //���ö����յ�	
	anim->start();                                                        //��ʼ���Ŷ���
	//�ͷ�·���ڴ�
	delete Path;	                                                      
}

/*
���ֱ�Ŷ���
ZeroPos:0����������λ��
num:��ǰ�������ֱ��
label:���ֱ�ǩ����
anim:��������
*/
void TurnTable::NumX(int ZeroPos,int num, QLabel *label,  QPropertyAnimation *anim)
{
	//�����˶�·��
	QPainterPath *PathNum = new QPainterPath();
	PathNum->arcMoveTo(this->width()*0.3 - label->width()*0.5, this->height()*0.3 - label->height()*0.5, this->width()*0.4, this->height()*0.4, 45 * ((ZeroPos+num) % 8));
	PathNum->arcTo(this->width()*0.3 - label->width()*0.5, this->height()*0.3 - label->height()*0.5, this->width()*0.4, this->height()*0.4, 45 * ((ZeroPos + num) % 8), - 45);
	Point = &PathNum->pointAtPercent(0);
	//���ö���
	anim->setTargetObject(label);                                         //���ö�������
	anim->setPropertyName("pos");                                         //���ö�������Ϊλ��
	anim->setDuration(400);                                               //���ò���ʱ��Ϊ400ms
	anim->setStartValue(PathNum->pointAtPercent(0));                      //���ö������
	for (int i = 0; i < 101; i++)                                         //����100���ؼ�֡
	{
		anim->setKeyValueAt((float)i / 100, PathNum->pointAtPercent((float)i / 100)); 
	}
	anim->setEndValue(PathNum->pointAtPercent(1));                        //���ö����յ�	
	anim->start();                                                        //��ʼ���Ŷ���
	//�ͷ�·���ڴ�
	delete PathNum;
}

