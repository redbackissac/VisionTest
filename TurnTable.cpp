#include "TurnTable.h"

//构造函数，指定父窗口
TurnTable::TurnTable(QWidget *parent) :
	QWidget(parent)
{	
}

/*
初始化，指定宽高
设定初始0号托盘位置，初始托盘状态
*/
void TurnTable::Init(int width, int height, int ZeroPos, uint8_t Plate)
{
	this->resize(width, height);                                     //设定宽高

	Point = new QPointF();                                           //用于设定路径起点终点

	/********************电池及数字标签初始化***************************/
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

	/*****************************加载图片资源********************************/
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

	/****************************将数字图片加载到QLabel中*********************************/
	labelNum0->setPixmap(*Num0);
	labelNum1->setPixmap(*Num1);
	labelNum2->setPixmap(*Num2);
	labelNum3->setPixmap(*Num3);
	labelNum4->setPixmap(*Num4);
	labelNum5->setPixmap(*Num5);
	labelNum6->setPixmap(*Num6);
	labelNum7->setPixmap(*Num7);

	/*******************************动画初始化*************************************/
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

	//播放初始位置	
	Refresh(ZeroPos, Plate);
	anim0->stop();
	anim1->stop();
	anim2->stop();
	anim3->stop();
	anim4->stop();
	anim5->stop();
	anim6->stop();
	anim7->stop();
	//停止播放动画，使动画定格
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
转盘动画更新，指定0号托盘位置、各托盘是否有电池
PosZero:0号托盘位置
PlateCond:转盘状态，以实际位置而非托盘标号为准
*/
void TurnTable::Refresh(int PosZero, uint8_t PlateCond)
{
	//电池动画
	PosX(label0, anim0, 0, PlateCond & 1);
	PosX(label1, anim1, 45, (PlateCond >> 1) & 1);
	PosX(label2, anim2, 90, (PlateCond >> 2) & 1);
	PosX(label3, anim3, 135, (PlateCond >> 3) & 1);
	PosX(label4, anim4, 180, (PlateCond >> 4) & 1);
	PosX(label5, anim5, 225, (PlateCond >> 5) & 1);
	PosX(label6, anim6, 270, (PlateCond >> 6) & 1);
	PosX(label7, anim7, 315, (PlateCond >> 7) & 1);
	//数字标号动画
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
电池动画
label:电池标签对象
anim:动画对象
startangle:起始运动位置
PosCond:该位置是否有电池标志
*/
void TurnTable::PosX(QLabel *label,  QPropertyAnimation *anim, int startangle,bool PosCond)
{
	//绘制运动路径
	QPainterPath *Path = new QPainterPath();
	Path->arcMoveTo(this->width()*0.15-label->width()*0.5, this->height()*0.15-label->height()*0.5, this->width()*0.7,this->height()*0.7, startangle);
	Path->arcTo(this->width()*0.15-label->width()*0.5, this->height()*0.15-label->height()*0.5, this->width()*0.7, this->height()*0.7, startangle, - 45);
	Point = &Path->pointAtPercent(0);
	//加载电池图片
	if(PosCond)                                                           //有电池
		label->setPixmap(*bat);
	else                                                                  //无电池
		label->setPixmap(*Nobat);                
	//设置动画
	anim->setTargetObject(label);                                         //设置动画对象
	anim->setPropertyName("pos");                                         //设置动画属性为位置
	anim->setDuration(400);                                               //播放时间400ms
	anim->setStartValue(Path->pointAtPercent(0));                         //设置动画起点
	for (int i = 0; i < 101; i++)                                         //设置100个关键帧
	{		
		anim->setKeyValueAt((float)i/100, Path->pointAtPercent((float)i / 100)); 
	}
	anim->setEndValue(Path->pointAtPercent(1));                           //设置动画终点	
	anim->start();                                                        //开始播放动画
	//释放路径内存
	delete Path;	                                                      
}

/*
数字标号动画
ZeroPos:0号托盘所处位置
num:当前动画数字标号
label:数字标签对象
anim:动画对象
*/
void TurnTable::NumX(int ZeroPos,int num, QLabel *label,  QPropertyAnimation *anim)
{
	//绘制运动路径
	QPainterPath *PathNum = new QPainterPath();
	PathNum->arcMoveTo(this->width()*0.3 - label->width()*0.5, this->height()*0.3 - label->height()*0.5, this->width()*0.4, this->height()*0.4, 45 * ((ZeroPos+num) % 8));
	PathNum->arcTo(this->width()*0.3 - label->width()*0.5, this->height()*0.3 - label->height()*0.5, this->width()*0.4, this->height()*0.4, 45 * ((ZeroPos + num) % 8), - 45);
	Point = &PathNum->pointAtPercent(0);
	//设置动画
	anim->setTargetObject(label);                                         //设置动画对象
	anim->setPropertyName("pos");                                         //设置动画属性为位置
	anim->setDuration(400);                                               //设置播放时间为400ms
	anim->setStartValue(PathNum->pointAtPercent(0));                      //设置动画起点
	for (int i = 0; i < 101; i++)                                         //设置100个关键帧
	{
		anim->setKeyValueAt((float)i / 100, PathNum->pointAtPercent((float)i / 100)); 
	}
	anim->setEndValue(PathNum->pointAtPercent(1));                        //设置动画终点	
	anim->start();                                                        //开始播放动画
	//释放路径内存
	delete PathNum;
}

