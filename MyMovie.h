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
	explicit MyMovie(QWidget *parent = nullptr);	                      //���캯����ָ������
	void Init(int width, int height, int ZeroPos, uint8_t Plate);         //��ʼ�����趨��ߣ���ʼ0��ת��λ�ã���ʼ����״̬(�����̱��Ϊ׼)
	void Play(bool ifBat_In, int ifBat_Out);                              //����һ�ζ���
	int GetZeroPos();                                                     //��ȡ��ǰ0�ŵ��λ��
	uint8_t GetPlate();                                                   //��ȡ��ǰ����״̬(�����̱��Ϊ׼)


private slots:
	void timeout();                                                       //��ʱ���ۺ��������ڿ��ƴ��ʹ���������

private:
	struct Cond                                                           //ת��״̬����
	{
		int ZeroPos;                                                      //0����������λ��
		uint8_t Plate;                                                    //8λ�����Ʊ�ʾ����״̬
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

	void Bat_In();                                                        //������϶���
	void BatOut_Good();	                                                  //��Ʒ������϶���
	void BatOut_Bad();                                                    //��Ʒ������϶���	
};

#endif 