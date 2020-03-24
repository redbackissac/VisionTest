#pragma once
#pragma execution_character_set("utf-8")

#include"Setting.h"

#define VIEW_CENTER viewport()->rect().center()
#define VIEW_WIDTH  viewport()->rect().width()
#define VIEW_HEIGHT viewport()->rect().height()

/*
���캯��
*/
Setting::Setting(QWidget*parents )
{
	ui.setupUi(this);	
	SettingView = new InteractiveView(this);
    SettingView->setGeometry(QRect(0, 0, 1024, 576));      //�����ӿ��ڴ����е�λ��
	//SettingView->setGeometry(QRect(0, 0, this->width(), this->width()*0.5625));      //�����ӿ��ڴ����е�λ��,����Ӧ���ڴ�С�������ݺ��Ϊ1024/576
	myScene = new GraphicsScene;                             //�½��Զ��峡��
	SettingView->setScene(myScene);	                       //������ͼ�����ӳ���	
	
}

/*
�½�����
*/
void Setting::on_New_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "��ʵ��ͼƬ", ".", "Image files(*.bmp *.jpg *.png)");  //��ʵ��ͼƬ
	if (fileName.isEmpty())		return; //δѡ��ͼ��                                    
	else
	{		
		if (!(QSrc.load(fileName))) //������ͼ�񴦴�   
		{			
			QMessageBox::warning(this, tr("����"), tr("��ͼ��ʧ��!"));		
			return;
		}
		else
		{
			//QSrc = QSrc.scaled(1024, 576, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  //��ͼƬ����Ϊ����ͼһ����		
			m_pPixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(QSrc));                             	
			m_pPixmapItem->setPos(-m_pPixmapItem->pixmap().width() / 2,	-m_pPixmapItem->pixmap().height() / 2); 
			myScene->addItem(m_pPixmapItem);
			//��¼ͼ���ڳ����е����꼰�ߴ�				
			QRect rect_pic = m_pPixmapItem->sceneBoundingRect().toRect();
			pic_x = rect_pic.topLeft().x();
			pic_y = rect_pic.topLeft().y();			
			pic_width = rect_pic.width();
			pic_height = rect_pic.height();
			//��ӡ������Ϣ
			cout << "pic_x:" << pic_x << endl;	
			cout << "pic_y:" << pic_y << endl;
			cout << "pic_width:" << pic_width << endl;	
			cout << "pic_height:" << pic_height << endl;
		}		
	}		
}

/*
�˳�
*/
void Setting::on_Exist_clicked()
{		
	this-> close();	
}

/*
�����¾���
*/
void Setting::on_createRect_clicked()
{
	myScene->creatRect();//�����¾���	
}

/*
��������
*/
void Setting::on_Save_clicked()
{	
	//�������ݵ��ļ�·��
	QString csvFileName = QFileDialog::getSaveFileName(this, "��������", ".", "csv files(*.csv)");  //ѡ�񱣴�λ�ã��༭�ļ�����
	QFile file(csvFileName);
	if (!file.exists())		//�ļ������ڵ�ʱ�½�
	{
		file.open(QIODevice::WriteOnly);
		QTextStream txtOutPut(&file);
		//����
		txtOutPut << "Unit(%)\n";
		txtOutPut << "TopLeft_x,TopLeft_y,width,height\n";	//ע�⣬ÿ�����ݽ�����Ҫ�ӻ��з�
		file.close();
	}
	//���ļ�
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream txtOutPut(&file);
	//��������item	
	for (rectItems::iterator it = myScene->m_rectItems.begin(); it != myScene->m_rectItems.end(); ++it)
	{		
		GraphicsRectItem *item = *it;//����ת��
		QRect rect = item->sceneBoundingRect().toRect();//item�ı߽��
		//����������
		item_rect rectSize;
		rectSize.x = rect.topLeft().x() - pic_x;
		rectSize.y = rect.topLeft().y() - pic_y;
		rectSize.width = rect.width();
		rectSize.height = rect.height();
		//��������
		QString msg = QString::number(rectSize.x) + ","\
			+ QString::number(rectSize.y) + ","\
			+ QString::number(rectSize.width) + ","\
			+ QString::number(rectSize.height) + "\n";
		txtOutPut << msg;
		file.flush();//���ļ���д������
	}	
	file.close();//������ɺ�ر��ļ�
}


void Setting::on_look_clicked()
{
	//��������item	
	for (rectItems::iterator it = myScene->m_rectItems.begin(); it != myScene->m_rectItems.end(); ++it)
	{
		GraphicsRectItem *item = *it;//����ת��
		QRect rect = item->sceneBoundingRect().toRect();//item�ı߽��
														//����������
														//��ӡ����
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