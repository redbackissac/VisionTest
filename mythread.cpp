#pragma execution_character_set("utf-8")
#include "mythread.h"

#include "MainWindow.h"

MyThread::MyThread(QObject* parent) : QObject(parent)
{
	isStop = false;
	imgPro = new SingleBattery;
}
/*
子线程中的工作，所有处理内容放在此函数中
*/
void MyThread::MyWork()
{
	Mat scrimage, dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
	Mat ROI_top;
	
	scrimage = imgPro->ImageAverage(3);                        //多幅平均	
	////遍历参数列表
	//for (ROI_pars::iterator it = m_roipars.begin(); it != m_roipars.end(); ++it)
	//{
	//	roi_parameters *pars = *it;
	//	ROI_top = scrimage(Rect(scrimage.cols * pars->x / 100, scrimage.rows * pars->y / 100, scrimage.cols * pars->width / 100, scrimage.rows * pars->height / 100));
	//	
	//}
	
	//threshold(ROI_top, ROI_top, 170, 255, 3);
	imgPro->createROI(scrimage);
	imgPro->edge();
	imwrite("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(1) + "(new).jpg", scrimage);//保存多幅平均滤波后的图像	
	//imgPro->~CImgProcess();                         //图像处理已结束，调用析构函数释放内存
	//delete imgPro;
	//test();
	emit singal_back();
}


void MyThread::setFlag(bool flag)
{
	isStop = flag;
}

/*
从主线程接收roi参数
*/
void MyThread::acceptROIS(ROI_pars m_pars)
{
	m_roipars.reserve(0);//先清空参数列表，为接收参数做好准备
	//遍历参数列表
	for (ROI_pars::iterator it = m_pars.begin(); it != m_pars.end(); ++it)
	{
		roi_parameters *pars = *it;
		m_roipars.push_back(pars);//将新接受的参数存入参数列表中
		imgPro->m_roipars.push_back(pars);//将新接受的参数存入参数列表中		
	}
}

void MyThread::test()
{
	//Mat scrimage, dstimage, gray_scrimage, grad_x, grad_y, abs_grad_x, abs_grad_y;
	


	Mat scrimage = imread("C:\\Users\\16935\\Desktop\\BatteryImg\\" + std::to_string(3) + ".jpg");//源图像	
	Mat imageROI = scrimage(Rect(0, 0, scrimage.cols / 2, scrimage.rows / 2));//创建ROI	

	threshold(imageROI, imageROI,170,255,3);
	

	imshow("roi", imageROI);
	imshow("src", scrimage);
	waitKey(0);
	//dstimage = imgPro->getEdgeVal(ROI_top);
	//threshold(ROI_top, ROI_top,170,255,3);
	//imwrite("C:\\Users\\16935\\Desktop\\" + std::to_string(3) + ".jpg", scrimage);//保存多幅平均滤波后的图像	
	
}

 