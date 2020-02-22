#pragma once
#ifndef	CALIBRATION_H
#define CALIBRATION_H

#include "singlebattery.h"

class Calibration : public SingleBattery
{
public:
	void getK();//获取标定值
private:
	Mat calImg;//标定板图像

};


#endif // !BATTERYTEMPLATE
