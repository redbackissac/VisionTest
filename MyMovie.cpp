#include "MyMovie.h"

/*
构造函数，指定父窗口
*/
MyMovie::MyMovie(QWidget *parent) :
	QWidget(parent)
{
}

/*
初始化函数，设定宽高,设定初始0号托盘位置及托盘状态
*/
void MyMovie::Init(int width, int height, int ZeroPos, uint8_t Plate )
{
	this->resize(width, height);                                          //设定大小
	cond.ZeroPos = ZeroPos;                                               //0号托盘位置初始化
	cond.Plate = (Plate >> (8 - ZeroPos)) | (Plate << ZeroPos);           //托盘状态初始化	

	TimeCtrl = new QTimer();                                              //实例化传送带定时器，用于控制传送带动画启停
	TimeCtrl->setInterval(1100);                                          //设置定时周期，1100ms
	connect(TimeCtrl, SIGNAL(timeout()), this, SLOT(timeout()));          //连接定时器槽函数timeout()

	/*********************箭头******************/
	//上料箭头
	Arrow_In = new QLabel(this);                                          //实例化上料箭头标签
	Arrow_Yellow = new QPixmap("./Resources/Pictures/Arrow_Yellow.png");  //载入黄箭头图片资源

	Arrow_In->move(this->width()*0.325, this->height()*0.665);            //设定位置(0.325,0.665)
	Arrow_In->resize(this->width()*0.05, this->height()*0.08);            //设定大小(0.05,0.08)
	Arrow_In->setScaledContents(true);                                    //使图片填满标签
	Arrow_In->setPixmap(*Arrow_Yellow);                                   //向标签加载图片

	//下料箭头
	Arrow_Out = new QLabel(this);                                         //实例化下料箭头标签
	Arrow_Blue = new QPixmap("./Resources/Pictures/Arrow_Blue.png");      //载入蓝箭头图片资源

	Arrow_Out->move(this->width()*0.635, this->height()*0.325);           //设定位置(0.635,0.325)
	Arrow_Out->resize(this->width()*0.1, this->height()*0.05);            //设定大小(0.1,0.05)
	Arrow_Out->setScaledContents(true);                                   //使图片填满标签
	Arrow_Out->setPixmap(*Arrow_Blue);                                    //向标签加载图片

	/*********************转盘******************/
	turntable = new TurnTable(this);                                      //实例化转盘对象
	turntable->Init(this->width()*0.7, this->height()*0.7, cond.ZeroPos, cond.Plate);//初始化转盘，设定大小为(0.7,0.7)
	turntable->move(0, 0);                                                //设定位置(0,0)

	/********************传送带*****************/
	//上料传送带
	label_in = new QLabel(this);                                          //实例化上料传送带标签
	movie_In = new QMovie;                                                //实例化上料传送带动画

	label_in->move(0, this->height()*0.75);                               //设定位置(0,0.75)
	label_in->resize(this->width()*0.7, this->height()*0.1);              //设定大小(0.7,0.1)
	label_in->setMovie(movie_In);                                         //向标签加载动画
	movie_In->setScaledSize(label_in->size());                            //设定动画大小即为标签大小	            
	movie_In->setFileName("./Resources/Pictures/Belt_In.gif");            //载入上料传送带动画资源
	movie_In->setSpeed(500);                                              //设定动画播放速度为5倍
	movie_In->start();                                                    //播放上料传送带动画

	//良品下料传送带
	label_outgood = new QLabel(this);                                     //实例化良品下料传送带标签
	movie_OutGood = new QMovie;                                           //实例化良品下料传送带动画 

	label_outgood->move(this->width()*0.9, this->height()*0.2);           //设定位置(0.9,0.2)
	label_outgood->resize(this->width()*0.1, this->height()*0.7);         //设定大小(0.1,0.7)	
	label_outgood->setMovie(movie_OutGood);                               //向标签加载动画
	movie_OutGood->setScaledSize(label_outgood->size());                  //设定动画大小即为标签大小 	
	movie_OutGood->setFileName("./Resources/Pictures/Belt_Out.gif");      //载入下料传送带动画资源
	movie_OutGood->setSpeed(500);                                         //设定动画播放速度为5倍
	movie_OutGood->start();                                               //播放良品下料传送带动画

	//次品下料传送带
	label_outbad = new QLabel(this);                                      //实例化次品下料传送带标签   
	movie_OutBad = new QMovie;                                            //实例化次品下料传送带动画 

	label_outbad->move(this->width()*0.75, 0);                            //设定位置(0.75,0)
	label_outbad->resize(this->width()*0.1, this->height()*0.7);          //设定大小(0.1,0.7)
	label_outbad->setMovie(movie_OutBad);                                 //向标签加载动画
	movie_OutBad->setScaledSize(label_outbad->size());                    //设定动画大小即为标签大小	
	movie_OutBad->setFileName("./Resources/Pictures/Belt_Out.gif");       //载入下料传送带动画资源
	movie_OutBad->setSpeed(500);                                          //设定动画播放速度为5倍
	movie_OutBad->start();                                                //播放次品下料传送带动画

	/********************电池*****************/	
	Battery = new QPixmap("./Resources/Pictures/Redbattery.png");         //载入电池图片资源	
	
	//上料电池
	Battery_In = new QLabel(this);                                        //实例化上料电池标签
	anim_In_1 = new QPropertyAnimation();                                 //实例化上料电池第1段属性动画
	anim_In_2 = new QPropertyAnimation();                                 //实例化上料电池第2段属性动画
	SeqAnim_In = new QSequentialAnimationGroup();                         //实例化上料电池顺序动画组

	Battery_In->resize(0, 0);                                             //初始化大小为(0,0)
	Battery_In->setScaledContents(true);                                  //使图片填满标签
    Battery_In->setPixmap(*Battery);                                      //向标签加载图片
	Bat_In();                                                             //设定上料电池动画组

	//良品下料电池
	Battery_Out_Good = new QLabel(this);                                  //实例化良品下料电池标签
	anim_Good_1 = new QPropertyAnimation();                               //实例化良品下料第1段属性动画
	anim_Good_2 = new QPropertyAnimation();                               //实例化良品下料第2段属性动画
	anim_Good_3 = new QPropertyAnimation();                               //实例化良品下料第3段属性动画
	SeqAnim_Good = new QSequentialAnimationGroup();                       //实例化良品下料顺序动画组

	Battery_Out_Good->resize(0, 0);                                       //初始化大小为(0,0)
	Battery_Out_Good->setScaledContents(true);                            //使图片填满标签
	Battery_Out_Good->setPixmap(*Battery);                                //向标签加载图片
	BatOut_Good();                                                        //设定良品下料电池动画组

	//次品下料电池
	Battery_Out_Bad = new QLabel(this);                                   //实例化次品下料电池标签
	anim_Bad_1 = new QPropertyAnimation();                                //实例化次品下料电池第1段属性动画
	anim_Bad_2 = new QPropertyAnimation();                                //实例化次品下料电池第2段属性动画
	anim_Bad_3 = new QPropertyAnimation();                                //实例化次品下料电池第3段属性动画
	SeqAnim_Bad = new QSequentialAnimationGroup();                        //实例化次品下料电池顺序动画组

	Battery_Out_Bad->resize(0, 0);                                        //初始化大小为(0,0)
	Battery_Out_Bad->setScaledContents(true);                             //使图片填满标签	
	Battery_Out_Bad->setPixmap(*Battery);                                 //向标签加载图片
	BatOut_Bad();                                                         //设定次品下料电池动画组  
	/******************转盘状态初始化*****************/
	
}

/*
上料电池动画组
*/
void MyMovie::Bat_In()
{
	//第1段动画
	anim_In_1->setTargetObject(Battery_In);                               //设置目标对象
	anim_In_1->setPropertyName("geometry");                               //设置动画属性为大小、位置
	anim_In_1->setDuration(700);                                          //设置播放时间700ms
	anim_In_1->setStartValue(QRect(this->width()*0.15, this->height()*0.75, this->width()*0.15*0.7, this->height()*0.15*0.7));   //起始(0.15,0.75,0.15*0.7,0.15*0.7)
	anim_In_1->setEndValue(QRect(this->width()*0.2925, this->height()*0.55, this->width()*0.15*0.7, this->height()*0.15*0.7));   //结束(0.2925,0.55,0.15*0.7,0.15*0.7

	//第2段动画
	anim_In_2->setTargetObject(Battery_In);                               //设置目标对象
	anim_In_2->setPropertyName("geometry");                               //设置动画属性为大小、位置
	anim_In_2->setDuration(200);                                          //设置播放时间200ms
	anim_In_2->setStartValue(QRect(this->width()*0.2925, this->height()*0.55, this->width()*0.15*0.7, this->height()*0.15*0.7)); //起始(0.2925,0.55,0.15*0.7,0.15*0.7)
	anim_In_2->setEndValue(QRect(this->width()*0.35, this->height()*0.6, 0, 0));                                                 //结束(0.35,0.6,0,0)

	//组合为顺序动画组
	SeqAnim_In->addAnimation(anim_In_1);                                  //向动画组中添加第1段动画
	SeqAnim_In->addPause(50);                                             //停顿50ms
	SeqAnim_In->addAnimation(anim_In_2);                                  //向动画组中添加第2段动画
}

/*
良品下料电池动画
*/
void MyMovie::BatOut_Good()
{
	//第1段动画
	anim_Good_1->setTargetObject(Battery_Out_Good);                       //设置目标对象
	anim_Good_1->setPropertyName("geometry");                             //设置动画属性为大小、位置
	anim_Good_1->setDuration(300);                                        //设置播放时间300ms
	anim_Good_1->setStartValue(QRect(this->width()*0.7, this->height()*0.35, 0, 0));                                             //起始(0.7,0.35,0,0)
	anim_Good_1->setEndValue(QRect(this->width()*0.9, this->height()*0.4, this->width()*0.15*0.7, this->height()*0.15*0.7));     //结束(0.9,0.4,0.15*0.7,0.15*0.7)

	//第2段动画
	anim_Good_2->setTargetObject(Battery_Out_Good);                       //设置目标对象
	anim_Good_2->setPropertyName("geometry");                             //设置动画属性为大小、位置                              
	anim_Good_2->setDuration(600);                                        //设置播放时间600ms
	anim_Good_2->setStartValue(QRect(this->width()*0.9, this->height()*0.4, this->width()*0.15*0.7, this->height()*0.15*0.7));   //起始(0.9,0.4,.015*0.7,0.15*0.7)
	anim_Good_2->setEndValue(QRect(this->width()*0.9, this->height()*0.6, this->width()*0.15*0.7, this->height()*0.15*0.7));     //结束(0.9,0.6,0.15*0.7,0.15*0.7)

	//第3段动画
	anim_Good_3->setTargetObject(Battery_Out_Good);                       //设置目标对象                       
	anim_Good_3->setPropertyName("size");                                 //设置动画属性为大小
	anim_Good_3->setDuration(1);                                          //设置播放时间1ms
	anim_Good_3->setStartValue(QSize(this->width()*0.15*0.7, this->height()*0.15*0.7));                                          //起始(0.15*0.7,0.15*0.7)
	anim_Good_3->setEndValue(QSize(0, 0));                                                                                       //结束(0,0)

	//组合为顺序动画组
	SeqAnim_Good->addAnimation(anim_Good_1);                              //向动画组中添加第1段动画
	SeqAnim_Good->addPause(50);                                           //停顿50ms
	SeqAnim_Good->addAnimation(anim_Good_2);                              //向动画组中添加第2段动画
	SeqAnim_Good->addPause(50);                                           //停顿50ms
	SeqAnim_Good->addAnimation(anim_Good_3);                              //向动画组中添加第3段动画
}

/*
次品下料动画
*/
void MyMovie::BatOut_Bad()
{
	//第1段动画
	anim_Bad_1->setTargetObject(Battery_Out_Bad);                         //设置目标对象     
	anim_Bad_1->setPropertyName("geometry");                              //设置动画属性为大小、位置       
	anim_Bad_1->setDuration(300);                                         //设置播放时间300ms
	anim_Bad_1->setStartValue(QRect(this->width()*0.7, this->height()*0.35, 0, 0));                                              //起始(0.7,0.35,0,0)
	anim_Bad_1->setEndValue(QRect(this->width()*0.75, this->height()*0.37, this->width()*0.15*0.7, this->height()*0.15*0.7));    //结束(0.75,0.37,0.15*0.7,0.15*0.7)

	//第2段动画
	anim_Bad_2->setTargetObject(Battery_Out_Bad);                         //设置目标对象
	anim_Bad_2->setPropertyName("geometry");                              //设置动画属性为大小、位置   
	anim_Bad_2->setDuration(600);                                         //设置播放时间600ms
	anim_Bad_2->setStartValue(QRect(this->width()*0.75, this->height()*0.37, this->width()*0.15*0.7, this->height()*0.15*0.7));  //起始(0.75,0.37,0.15*0.7,0.15*0.7)
	anim_Bad_2->setEndValue(QRect(this->width()*0.75, this->height()*0.45, this->width()*0.15*0.7, this->height()*0.15*0.7));    //结束(0.75,0.45,0.15*0.7,0.15*0.7)

	//第3段动画
	anim_Bad_3->setTargetObject(Battery_Out_Bad);                         //设置目标对象                     
	anim_Bad_3->setPropertyName("size");                                  //设置动画属性为大小
	anim_Bad_3->setDuration(1);                                           //设置播放时间1ms
	anim_Bad_3->setStartValue(QSize(this->width()*0.15*0.7, this->height()*0.15*0.7));                                           //起始(0.15*0.7,0.15*0.7)
	anim_Bad_3->setEndValue(QSize(0, 0));                                                                                        //结束(0,0)

	//组合为顺序动画
	SeqAnim_Bad->addAnimation(anim_Bad_1);                                //向动画组中添加第1段动画
	SeqAnim_Bad->addPause(50);                                            //停顿50ms
	SeqAnim_Bad->addAnimation(anim_Bad_2);                                //向动画组中添加第2段动画
	SeqAnim_Bad->addPause(50);                                            //停顿50ms
	SeqAnim_Bad->addAnimation(anim_Bad_3);                                //向动画组中添加第3段动画
}

/*
播放一次动画
ifBat_In 为true时播放上料电池动画，为false不播放
ifBat_Out为1时播放良品下料电池动画，为2时播放次品下料电池动画，为0时不播放
*/
void MyMovie::Play(bool ifBat_In, int ifBat_Out)
{	
	movie_In->start();                                                    //开始上料传送带动画
	movie_OutGood->start();                                               //开始良品下料传送带动画
	movie_OutBad->start();                                                //开始次品下料传送带动画
	TimeCtrl->start();                                                    //传送带定时器开始计时
	if (ifBat_In)                                                         //若有电池上料
	{
		cond.Plate = cond.Plate | 0x40;                                   //上料工位置1		
		SeqAnim_In->start();                                              //开始上料电池动画
	}

	if (ifBat_Out == 1)                                                   //若有良品下料
	{
		cond.Plate = cond.Plate & 0xfe;                                   //下料工位置0
		SeqAnim_Good->start();                                            //开始良品下料电池动画
	}

	if (ifBat_Out == 2)                                                   //若有次品下料
	{
		cond.Plate = cond.Plate & 0xfe;                                   //下料工位置0
		SeqAnim_Bad->start();                                             //开始次品下料电池动画
	}
}


/*
传送带定时器到达定时后槽函数，控制传送带动画播放时长
*/
void MyMovie::timeout()
{
	movie_In->stop();                                                     //停止上料传送带动画
	movie_OutGood->stop();                                                //停止良品下料传送带动画
	movie_OutBad->stop();                                                 //停止次品下料传送带动画
	turntable->Refresh(cond.ZeroPos, cond.Plate);                          //更新转盘状态
	cond.ZeroPos = (cond.ZeroPos - 1) % 8;                                //更新0号托盘位置	
	cond.Plate = (cond.Plate << (8 - 1)) | (cond.Plate >> 1);             //托盘状态循环右移1位	
	TimeCtrl->stop();                                                     //停止定时器，等待下一次播放
}

/*
获取当前0号电池位置
*/
int MyMovie::GetZeroPos()
{
	return cond.ZeroPos;
}

/*
获取当前托盘状态(以托盘标号为准)
*/
uint8_t MyMovie::GetPlate()
{
	return  (cond.Plate << (8 - cond.ZeroPos)) | (cond.Plate >> cond.ZeroPos);
}

