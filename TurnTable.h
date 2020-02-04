#pragma once
#ifndef	TURNTABLE_H
#define TURNTABLE_H
#include <QWidget>
#include <QLabel>
#include <QPainterPath> 
#include <QPropertyAnimation> 
#include <QPoint> 
#include <QPixmap>

class TurnTable : public QWidget
{
	Q_OBJECT

public:	
	explicit TurnTable(QWidget *parent = nullptr);	                      //构造函数，指定父类
	void Init(int width, int height, int ZeroPos, uint8_t Plate);         //初始化，指定宽高，设定初始0号托盘位置，初始托盘状态
	void Refresh(int PosZero, uint8_t PlateCond);                         //转盘动画更新，指定0号托盘位置、各托盘是否有电池
	
private:
	QPointF *Point;	

	QLabel *label0;
	QLabel *label1;
	QLabel *label2;
	QLabel *label3;
	QLabel *label4;
	QLabel *label5;
	QLabel *label6;
	QLabel *label7;
	QLabel *labelNum0;
	QLabel *labelNum1;
	QLabel *labelNum2;
	QLabel *labelNum3;
	QLabel *labelNum4;
	QLabel *labelNum5;
	QLabel *labelNum6;
	QLabel *labelNum7;	

	QPropertyAnimation *anim0;
	QPropertyAnimation *anim1;
	QPropertyAnimation *anim2;
	QPropertyAnimation *anim3;
	QPropertyAnimation *anim4;
	QPropertyAnimation *anim5;
	QPropertyAnimation *anim6;
	QPropertyAnimation *anim7;
	QPropertyAnimation *animNum0;
	QPropertyAnimation *animNum1;
	QPropertyAnimation *animNum2;
	QPropertyAnimation *animNum3;
	QPropertyAnimation *animNum4;
	QPropertyAnimation *animNum5;
	QPropertyAnimation *animNum6;
	QPropertyAnimation *animNum7;

	QPixmap *bat;
	QPixmap *Nobat;
	QPixmap *Num0;
	QPixmap *Num1;
	QPixmap *Num2;
	QPixmap *Num3;
	QPixmap *Num4;
	QPixmap *Num5;
	QPixmap *Num6;
	QPixmap *Num7;
	
	void PosX(QLabel *label, QPropertyAnimation *anim,int startangle, bool PosCond);//电池动画
	void NumX(int ZeroPos,int num, QLabel *label, QPropertyAnimation *anim);        //数字标号动画
};

#endif 