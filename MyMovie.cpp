#include "MyMovie.h"

/*
���캯����ָ��������
*/
MyMovie::MyMovie(QWidget *parent) :
	QWidget(parent)
{
}

/*
��ʼ���������趨���,�趨��ʼ0������λ�ü�����״̬
*/
void MyMovie::Init(int width, int height, int ZeroPos, uint8_t Plate )
{
	this->resize(width, height);                                          //�趨��С
	cond.ZeroPos = ZeroPos;                                               //0������λ�ó�ʼ��
	cond.Plate = (Plate >> (8 - ZeroPos)) | (Plate << ZeroPos);           //����״̬��ʼ��	

	TimeCtrl = new QTimer();                                              //ʵ�������ʹ���ʱ�������ڿ��ƴ��ʹ�������ͣ
	TimeCtrl->setInterval(1100);                                          //���ö�ʱ���ڣ�1100ms
	connect(TimeCtrl, SIGNAL(timeout()), this, SLOT(timeout()));          //���Ӷ�ʱ���ۺ���timeout()

	/*********************��ͷ******************/
	//���ϼ�ͷ
	Arrow_In = new QLabel(this);                                          //ʵ�������ϼ�ͷ��ǩ
	Arrow_Yellow = new QPixmap("./Resources/Pictures/Arrow_Yellow.png");  //����Ƽ�ͷͼƬ��Դ

	Arrow_In->move(this->width()*0.325, this->height()*0.665);            //�趨λ��(0.325,0.665)
	Arrow_In->resize(this->width()*0.05, this->height()*0.08);            //�趨��С(0.05,0.08)
	Arrow_In->setScaledContents(true);                                    //ʹͼƬ������ǩ
	Arrow_In->setPixmap(*Arrow_Yellow);                                   //���ǩ����ͼƬ

	//���ϼ�ͷ
	Arrow_Out = new QLabel(this);                                         //ʵ�������ϼ�ͷ��ǩ
	Arrow_Blue = new QPixmap("./Resources/Pictures/Arrow_Blue.png");      //��������ͷͼƬ��Դ

	Arrow_Out->move(this->width()*0.635, this->height()*0.325);           //�趨λ��(0.635,0.325)
	Arrow_Out->resize(this->width()*0.1, this->height()*0.05);            //�趨��С(0.1,0.05)
	Arrow_Out->setScaledContents(true);                                   //ʹͼƬ������ǩ
	Arrow_Out->setPixmap(*Arrow_Blue);                                    //���ǩ����ͼƬ

	/*********************ת��******************/
	turntable = new TurnTable(this);                                      //ʵ����ת�̶���
	turntable->Init(this->width()*0.7, this->height()*0.7, cond.ZeroPos, cond.Plate);//��ʼ��ת�̣��趨��СΪ(0.7,0.7)
	turntable->move(0, 0);                                                //�趨λ��(0,0)

	/********************���ʹ�*****************/
	//���ϴ��ʹ�
	label_in = new QLabel(this);                                          //ʵ�������ϴ��ʹ���ǩ
	movie_In = new QMovie;                                                //ʵ�������ϴ��ʹ�����

	label_in->move(0, this->height()*0.75);                               //�趨λ��(0,0.75)
	label_in->resize(this->width()*0.7, this->height()*0.1);              //�趨��С(0.7,0.1)
	label_in->setMovie(movie_In);                                         //���ǩ���ض���
	movie_In->setScaledSize(label_in->size());                            //�趨������С��Ϊ��ǩ��С	            
	movie_In->setFileName("./Resources/Pictures/Belt_In.gif");            //�������ϴ��ʹ�������Դ
	movie_In->setSpeed(500);                                              //�趨���������ٶ�Ϊ5��
	movie_In->start();                                                    //�������ϴ��ʹ�����

	//��Ʒ���ϴ��ʹ�
	label_outgood = new QLabel(this);                                     //ʵ������Ʒ���ϴ��ʹ���ǩ
	movie_OutGood = new QMovie;                                           //ʵ������Ʒ���ϴ��ʹ����� 

	label_outgood->move(this->width()*0.9, this->height()*0.2);           //�趨λ��(0.9,0.2)
	label_outgood->resize(this->width()*0.1, this->height()*0.7);         //�趨��С(0.1,0.7)	
	label_outgood->setMovie(movie_OutGood);                               //���ǩ���ض���
	movie_OutGood->setScaledSize(label_outgood->size());                  //�趨������С��Ϊ��ǩ��С 	
	movie_OutGood->setFileName("./Resources/Pictures/Belt_Out.gif");      //�������ϴ��ʹ�������Դ
	movie_OutGood->setSpeed(500);                                         //�趨���������ٶ�Ϊ5��
	movie_OutGood->start();                                               //������Ʒ���ϴ��ʹ�����

	//��Ʒ���ϴ��ʹ�
	label_outbad = new QLabel(this);                                      //ʵ������Ʒ���ϴ��ʹ���ǩ   
	movie_OutBad = new QMovie;                                            //ʵ������Ʒ���ϴ��ʹ����� 

	label_outbad->move(this->width()*0.75, 0);                            //�趨λ��(0.75,0)
	label_outbad->resize(this->width()*0.1, this->height()*0.7);          //�趨��С(0.1,0.7)
	label_outbad->setMovie(movie_OutBad);                                 //���ǩ���ض���
	movie_OutBad->setScaledSize(label_outbad->size());                    //�趨������С��Ϊ��ǩ��С	
	movie_OutBad->setFileName("./Resources/Pictures/Belt_Out.gif");       //�������ϴ��ʹ�������Դ
	movie_OutBad->setSpeed(500);                                          //�趨���������ٶ�Ϊ5��
	movie_OutBad->start();                                                //���Ŵ�Ʒ���ϴ��ʹ�����

	/********************���*****************/	
	Battery = new QPixmap("./Resources/Pictures/Redbattery.png");         //������ͼƬ��Դ	
	
	//���ϵ��
	Battery_In = new QLabel(this);                                        //ʵ�������ϵ�ر�ǩ
	anim_In_1 = new QPropertyAnimation();                                 //ʵ�������ϵ�ص�1�����Զ���
	anim_In_2 = new QPropertyAnimation();                                 //ʵ�������ϵ�ص�2�����Զ���
	SeqAnim_In = new QSequentialAnimationGroup();                         //ʵ�������ϵ��˳�򶯻���

	Battery_In->resize(0, 0);                                             //��ʼ����СΪ(0,0)
	Battery_In->setScaledContents(true);                                  //ʹͼƬ������ǩ
    Battery_In->setPixmap(*Battery);                                      //���ǩ����ͼƬ
	Bat_In();                                                             //�趨���ϵ�ض�����

	//��Ʒ���ϵ��
	Battery_Out_Good = new QLabel(this);                                  //ʵ������Ʒ���ϵ�ر�ǩ
	anim_Good_1 = new QPropertyAnimation();                               //ʵ������Ʒ���ϵ�1�����Զ���
	anim_Good_2 = new QPropertyAnimation();                               //ʵ������Ʒ���ϵ�2�����Զ���
	anim_Good_3 = new QPropertyAnimation();                               //ʵ������Ʒ���ϵ�3�����Զ���
	SeqAnim_Good = new QSequentialAnimationGroup();                       //ʵ������Ʒ����˳�򶯻���

	Battery_Out_Good->resize(0, 0);                                       //��ʼ����СΪ(0,0)
	Battery_Out_Good->setScaledContents(true);                            //ʹͼƬ������ǩ
	Battery_Out_Good->setPixmap(*Battery);                                //���ǩ����ͼƬ
	BatOut_Good();                                                        //�趨��Ʒ���ϵ�ض�����

	//��Ʒ���ϵ��
	Battery_Out_Bad = new QLabel(this);                                   //ʵ������Ʒ���ϵ�ر�ǩ
	anim_Bad_1 = new QPropertyAnimation();                                //ʵ������Ʒ���ϵ�ص�1�����Զ���
	anim_Bad_2 = new QPropertyAnimation();                                //ʵ������Ʒ���ϵ�ص�2�����Զ���
	anim_Bad_3 = new QPropertyAnimation();                                //ʵ������Ʒ���ϵ�ص�3�����Զ���
	SeqAnim_Bad = new QSequentialAnimationGroup();                        //ʵ������Ʒ���ϵ��˳�򶯻���

	Battery_Out_Bad->resize(0, 0);                                        //��ʼ����СΪ(0,0)
	Battery_Out_Bad->setScaledContents(true);                             //ʹͼƬ������ǩ	
	Battery_Out_Bad->setPixmap(*Battery);                                 //���ǩ����ͼƬ
	BatOut_Bad();                                                         //�趨��Ʒ���ϵ�ض�����  
	/******************ת��״̬��ʼ��*****************/
	
}

/*
���ϵ�ض�����
*/
void MyMovie::Bat_In()
{
	//��1�ζ���
	anim_In_1->setTargetObject(Battery_In);                               //����Ŀ�����
	anim_In_1->setPropertyName("geometry");                               //���ö�������Ϊ��С��λ��
	anim_In_1->setDuration(700);                                          //���ò���ʱ��700ms
	anim_In_1->setStartValue(QRect(this->width()*0.15, this->height()*0.75, this->width()*0.15*0.7, this->height()*0.15*0.7));   //��ʼ(0.15,0.75,0.15*0.7,0.15*0.7)
	anim_In_1->setEndValue(QRect(this->width()*0.2925, this->height()*0.55, this->width()*0.15*0.7, this->height()*0.15*0.7));   //����(0.2925,0.55,0.15*0.7,0.15*0.7

	//��2�ζ���
	anim_In_2->setTargetObject(Battery_In);                               //����Ŀ�����
	anim_In_2->setPropertyName("geometry");                               //���ö�������Ϊ��С��λ��
	anim_In_2->setDuration(200);                                          //���ò���ʱ��200ms
	anim_In_2->setStartValue(QRect(this->width()*0.2925, this->height()*0.55, this->width()*0.15*0.7, this->height()*0.15*0.7)); //��ʼ(0.2925,0.55,0.15*0.7,0.15*0.7)
	anim_In_2->setEndValue(QRect(this->width()*0.35, this->height()*0.6, 0, 0));                                                 //����(0.35,0.6,0,0)

	//���Ϊ˳�򶯻���
	SeqAnim_In->addAnimation(anim_In_1);                                  //�򶯻�������ӵ�1�ζ���
	SeqAnim_In->addPause(50);                                             //ͣ��50ms
	SeqAnim_In->addAnimation(anim_In_2);                                  //�򶯻�������ӵ�2�ζ���
}

/*
��Ʒ���ϵ�ض���
*/
void MyMovie::BatOut_Good()
{
	//��1�ζ���
	anim_Good_1->setTargetObject(Battery_Out_Good);                       //����Ŀ�����
	anim_Good_1->setPropertyName("geometry");                             //���ö�������Ϊ��С��λ��
	anim_Good_1->setDuration(300);                                        //���ò���ʱ��300ms
	anim_Good_1->setStartValue(QRect(this->width()*0.7, this->height()*0.35, 0, 0));                                             //��ʼ(0.7,0.35,0,0)
	anim_Good_1->setEndValue(QRect(this->width()*0.9, this->height()*0.4, this->width()*0.15*0.7, this->height()*0.15*0.7));     //����(0.9,0.4,0.15*0.7,0.15*0.7)

	//��2�ζ���
	anim_Good_2->setTargetObject(Battery_Out_Good);                       //����Ŀ�����
	anim_Good_2->setPropertyName("geometry");                             //���ö�������Ϊ��С��λ��                              
	anim_Good_2->setDuration(600);                                        //���ò���ʱ��600ms
	anim_Good_2->setStartValue(QRect(this->width()*0.9, this->height()*0.4, this->width()*0.15*0.7, this->height()*0.15*0.7));   //��ʼ(0.9,0.4,.015*0.7,0.15*0.7)
	anim_Good_2->setEndValue(QRect(this->width()*0.9, this->height()*0.6, this->width()*0.15*0.7, this->height()*0.15*0.7));     //����(0.9,0.6,0.15*0.7,0.15*0.7)

	//��3�ζ���
	anim_Good_3->setTargetObject(Battery_Out_Good);                       //����Ŀ�����                       
	anim_Good_3->setPropertyName("size");                                 //���ö�������Ϊ��С
	anim_Good_3->setDuration(1);                                          //���ò���ʱ��1ms
	anim_Good_3->setStartValue(QSize(this->width()*0.15*0.7, this->height()*0.15*0.7));                                          //��ʼ(0.15*0.7,0.15*0.7)
	anim_Good_3->setEndValue(QSize(0, 0));                                                                                       //����(0,0)

	//���Ϊ˳�򶯻���
	SeqAnim_Good->addAnimation(anim_Good_1);                              //�򶯻�������ӵ�1�ζ���
	SeqAnim_Good->addPause(50);                                           //ͣ��50ms
	SeqAnim_Good->addAnimation(anim_Good_2);                              //�򶯻�������ӵ�2�ζ���
	SeqAnim_Good->addPause(50);                                           //ͣ��50ms
	SeqAnim_Good->addAnimation(anim_Good_3);                              //�򶯻�������ӵ�3�ζ���
}

/*
��Ʒ���϶���
*/
void MyMovie::BatOut_Bad()
{
	//��1�ζ���
	anim_Bad_1->setTargetObject(Battery_Out_Bad);                         //����Ŀ�����     
	anim_Bad_1->setPropertyName("geometry");                              //���ö�������Ϊ��С��λ��       
	anim_Bad_1->setDuration(300);                                         //���ò���ʱ��300ms
	anim_Bad_1->setStartValue(QRect(this->width()*0.7, this->height()*0.35, 0, 0));                                              //��ʼ(0.7,0.35,0,0)
	anim_Bad_1->setEndValue(QRect(this->width()*0.75, this->height()*0.37, this->width()*0.15*0.7, this->height()*0.15*0.7));    //����(0.75,0.37,0.15*0.7,0.15*0.7)

	//��2�ζ���
	anim_Bad_2->setTargetObject(Battery_Out_Bad);                         //����Ŀ�����
	anim_Bad_2->setPropertyName("geometry");                              //���ö�������Ϊ��С��λ��   
	anim_Bad_2->setDuration(600);                                         //���ò���ʱ��600ms
	anim_Bad_2->setStartValue(QRect(this->width()*0.75, this->height()*0.37, this->width()*0.15*0.7, this->height()*0.15*0.7));  //��ʼ(0.75,0.37,0.15*0.7,0.15*0.7)
	anim_Bad_2->setEndValue(QRect(this->width()*0.75, this->height()*0.45, this->width()*0.15*0.7, this->height()*0.15*0.7));    //����(0.75,0.45,0.15*0.7,0.15*0.7)

	//��3�ζ���
	anim_Bad_3->setTargetObject(Battery_Out_Bad);                         //����Ŀ�����                     
	anim_Bad_3->setPropertyName("size");                                  //���ö�������Ϊ��С
	anim_Bad_3->setDuration(1);                                           //���ò���ʱ��1ms
	anim_Bad_3->setStartValue(QSize(this->width()*0.15*0.7, this->height()*0.15*0.7));                                           //��ʼ(0.15*0.7,0.15*0.7)
	anim_Bad_3->setEndValue(QSize(0, 0));                                                                                        //����(0,0)

	//���Ϊ˳�򶯻�
	SeqAnim_Bad->addAnimation(anim_Bad_1);                                //�򶯻�������ӵ�1�ζ���
	SeqAnim_Bad->addPause(50);                                            //ͣ��50ms
	SeqAnim_Bad->addAnimation(anim_Bad_2);                                //�򶯻�������ӵ�2�ζ���
	SeqAnim_Bad->addPause(50);                                            //ͣ��50ms
	SeqAnim_Bad->addAnimation(anim_Bad_3);                                //�򶯻�������ӵ�3�ζ���
}

/*
����һ�ζ���
ifBat_In Ϊtrueʱ�������ϵ�ض�����Ϊfalse������
ifBat_OutΪ1ʱ������Ʒ���ϵ�ض�����Ϊ2ʱ���Ŵ�Ʒ���ϵ�ض�����Ϊ0ʱ������
*/
void MyMovie::Play(bool ifBat_In, int ifBat_Out)
{	
	movie_In->start();                                                    //��ʼ���ϴ��ʹ�����
	movie_OutGood->start();                                               //��ʼ��Ʒ���ϴ��ʹ�����
	movie_OutBad->start();                                                //��ʼ��Ʒ���ϴ��ʹ�����
	TimeCtrl->start();                                                    //���ʹ���ʱ����ʼ��ʱ
	if (ifBat_In)                                                         //���е������
	{
		cond.Plate = cond.Plate | 0x40;                                   //���Ϲ�λ��1		
		SeqAnim_In->start();                                              //��ʼ���ϵ�ض���
	}

	if (ifBat_Out == 1)                                                   //������Ʒ����
	{
		cond.Plate = cond.Plate & 0xfe;                                   //���Ϲ�λ��0
		SeqAnim_Good->start();                                            //��ʼ��Ʒ���ϵ�ض���
	}

	if (ifBat_Out == 2)                                                   //���д�Ʒ����
	{
		cond.Plate = cond.Plate & 0xfe;                                   //���Ϲ�λ��0
		SeqAnim_Bad->start();                                             //��ʼ��Ʒ���ϵ�ض���
	}
}


/*
���ʹ���ʱ�����ﶨʱ��ۺ��������ƴ��ʹ���������ʱ��
*/
void MyMovie::timeout()
{
	movie_In->stop();                                                     //ֹͣ���ϴ��ʹ�����
	movie_OutGood->stop();                                                //ֹͣ��Ʒ���ϴ��ʹ�����
	movie_OutBad->stop();                                                 //ֹͣ��Ʒ���ϴ��ʹ�����
	turntable->Refresh(cond.ZeroPos, cond.Plate);                          //����ת��״̬
	cond.ZeroPos = (cond.ZeroPos - 1) % 8;                                //����0������λ��	
	cond.Plate = (cond.Plate << (8 - 1)) | (cond.Plate >> 1);             //����״̬ѭ������1λ	
	TimeCtrl->stop();                                                     //ֹͣ��ʱ�����ȴ���һ�β���
}

/*
��ȡ��ǰ0�ŵ��λ��
*/
int MyMovie::GetZeroPos()
{
	return cond.ZeroPos;
}

/*
��ȡ��ǰ����״̬(�����̱��Ϊ׼)
*/
uint8_t MyMovie::GetPlate()
{
	return  (cond.Plate << (8 - cond.ZeroPos)) | (cond.Plate >> cond.ZeroPos);
}

