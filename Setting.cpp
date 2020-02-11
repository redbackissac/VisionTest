#pragma once
#pragma execution_character_set("utf-8")

#include"Setting.h"

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()

/*
构造函数
*/
Setting::Setting(QWidget*parents )
{
	ui.setupUi(this);	
	SettingView = new InteractiveView(this);
    SettingView->setGeometry(QRect(0, 0, 1024, 576));      //设置视口在窗口中的位置
	//SettingView->setGeometry(QRect(0, 0, this->width(), this->width()*0.5625));      //设置视口在窗口中的位置,自适应窗口大小，保持纵横比为1024/576
	myScene = new GraphicsScene;                             //新建自定义场景
	SettingView->setScene(myScene);	                       //向界面的图像口添加场景	
	
}

/*
新建配置
*/
void Setting::on_New_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "打开实例图片", ".", "Image files(*.bmp *.jpg *.png)");  //打开实例图片
	if (fileName.isEmpty())		return; //未选择图像                                    
	else
	{		
		if (!(QSrc.load(fileName))) //若加载图像处错   
		{			
			QMessageBox::warning(this, tr("错误"), tr("打开图像失败!"));		
			return;
		}
		else
		{
			//QSrc = QSrc.scaled(1024, 576, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  //将图片缩放为与视图一样大		
			m_pPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(QSrc));                             	
			m_pPixmapItem->setPos(-m_pPixmapItem->pixmap().width() / 2,	-m_pPixmapItem->pixmap().height() / 2); 
			myScene->addItem(m_pPixmapItem);
			//记录图像在场景中的坐标及尺寸				
			QRect rect_pic = m_pPixmapItem->sceneBoundingRect().toRect();
			pic_x = rect_pic.topLeft().x();
			pic_y = rect_pic.topLeft().y();			
			pic_width = rect_pic.width();
			pic_height = rect_pic.height();
			//打印调试信息
			cout << "pic_x:" << pic_x << endl;	
			cout << "pic_y:" << pic_y << endl;
			cout << "pic_width:" << pic_width << endl;	
			cout << "pic_height:" << pic_height << endl;
		}		
	}		
}

/*
退出
*/
void Setting::on_Exist_clicked()
{		
	this-> close();	
}

/*
创建新矩形
*/
void Setting::on_createRect_clicked()
{
	myScene->creatRect();//绘制新矩形	
}

/*
保存设置
*/
void Setting::on_Save_clicked()
{	
	//保存数据的文件路径
	QString csvFileName = QFileDialog::getSaveFileName(this, "保存设置", ".", "csv files(*.csv)");  //选择保存位置，编辑文件名称
	QFile file(csvFileName);
	if (!file.exists())		//文件不存在的时新建
	{
		file.open(QIODevice::WriteOnly);
		QTextStream txtOutPut(&file);
		//标题
		txtOutPut << "Unit(%)\n";
		txtOutPut << "TopLeft_x,TopLeft_y,width,height\n";	//注意，每行数据结束后要加换行符
		file.close();
	}
	//打开文件
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream txtOutPut(&file);
	//遍历所有item	
	for (rectItems::iterator it = myScene->m_rectItems.begin(); it != myScene->m_rectItems.end(); ++it)
	{		
		GraphicsRectItem *item = *it;//类型转换
		QRect rect = item->sceneBoundingRect().toRect();//item的边界框
		//相对坐标计算
		item_rect rectSize;
		rectSize.x = rect.topLeft().x() - pic_x;
		rectSize.y = rect.topLeft().y() - pic_y;
		rectSize.width = rect.width();
		rectSize.height = rect.height();
		//保存数据
		QString msg = QString::number(rectSize.x) + ","\
			+ QString::number(rectSize.y) + ","\
			+ QString::number(rectSize.width) + ","\
			+ QString::number(rectSize.height) + "\n";
		txtOutPut << msg;
		file.flush();//向文件中写入数据
	}	
	file.close();//保存完成后关闭文件
}


void Setting::on_look_clicked()
{
	//遍历所有item	
	for (rectItems::iterator it = myScene->m_rectItems.begin(); it != myScene->m_rectItems.end(); ++it)
	{
		GraphicsRectItem *item = *it;//类型转换
		QRect rect = item->sceneBoundingRect().toRect();//item的边界框
														//相对坐标计算
														//打印数据
		cout << "rectregion.x" << rect.topLeft().x() - pic_x << endl;
		cout << "rectregion.y" << rect.topLeft().y() - pic_y << endl;
		cout << "rectregion.width" << rect.width() << endl;
		cout << "rectregion.height" << rect.height() << endl;

		//item_rect rectSize;
		//rectSize.x = (rect.topLeft().x() - pic_x) * 100 / pic_width;
		//rectSize.y = (rect.topLeft().y() - pic_y) * 100 / pic_height;
		//rectSize.width = rect.width() * 100 / pic_width;
		//rectSize.height = rect.height() * 100 / pic_height;

		item_rect rectSize;
		rectSize.x = rect.topLeft().x() - pic_x;
		rectSize.y = rect.topLeft().y() - pic_y;
		rectSize.width = rect.width();
		rectSize.height = rect.height();		
	}
}