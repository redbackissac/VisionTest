#pragma once
#ifndef	MYMOVIE_H
#define MYMOVIE_H
#include <QWidget>
#include <QLabel>
#include <QPainterPath> 
#include <QPropertyAnimation> 
#include <QSequentialAnimationGroup> 
#include <QMovie> 
#include <QPixmap>
#include <QTimer.h>
#include "TurnTable.h"

class MyMovie : public QWidget
{
	Q_OBJECT
public:
	explicit MyMovie(QWidget *parent = nullptr);	                      //构造函数，指定父类
	void Init(int width, int height, int ZeroPos, uint8_t Plate);         //初始化，设定宽高，初始0号转盘位置，初始托盘状态(以托盘标号为准)
	void Play(bool ifBat_In, int ifBat_Out);                              //播放一次动画
	int GetZeroPos();                                                     //获取当前0号电池位置
	uint8_t GetPlate();                                                   //获取当前托盘状态(以托盘标号为准)


private slots:
	void timeout();                                                       //定时器槽函数，用于控制传送带动画播放

private:
	struct Cond                                                           //转盘状态参数
	{
		int ZeroPos;                                                      //0号托盘所处位置
		uint8_t Plate;                                                    //8位二进制表示托盘状态
	}cond;

	QTimer *TimeCtrl;

	QLabel *label_in;
	QLabel *label_outbad;
	QLabel *label_outgood;
	QLabel *Arrow_In;
	QLabel *Arrow_Out;                                     
	QLabel *Battery_In;
	QLabel *Battery_Out_Good;
	QLabel *Battery_Out_Bad;

	QPixmap *Arrow_Yellow;
	QPixmap *Arrow_Blue;
	QPixmap *Battery;

	QPropertyAnimation *anim_In_1;	
	QPropertyAnimation *anim_In_2;
	QSequentialAnimationGroup *SeqAnim_In;

	QPropertyAnimation *anim_Good_1;
	QPropertyAnimation *anim_Good_2;
	QPropertyAnimation *anim_Good_3;
	QSequentialAnimationGroup *SeqAnim_Good;

	QPropertyAnimation *anim_Bad_1;
	QPropertyAnimation *anim_Bad_2;
	QPropertyAnimation *anim_Bad_3;
	QSequentialAnimationGroup *SeqAnim_Bad;

	QMovie *movie_In;
	QMovie *movie_OutBad;
	QMovie *movie_OutGood;

	TurnTable *turntable;

	void Bat_In();                                                        //电池上料动画
	void BatOut_Good();	                                                  //良品电池下料动画
	void BatOut_Bad();                                                    //次品电池下料动画	
};

#endif 