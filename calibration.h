#pragma once
#ifndef	CALIBRATION_H
#define CALIBRATION_H

#include "singlebattery.h"

class Calibration : public SingleBattery
{
public:
	void getK();//��ȡ�궨ֵ
private:
	Mat calImg;//�궨��ͼ��

};


#endif // !BATTERYTEMPLATE
