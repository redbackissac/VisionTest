
#include "mydatabase.h"

#include <QDebug>
#include <algorithm>
#include <iostream>
using namespace std;

MyDataBase * MyDataBase::m_pInstance(NULL);



MyDataBase::MyDataBase()

{
	//odbc���÷���:http://blog.sina.com.cn/s/blog_6ff019f90102vpcs.html
	db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName("VisionTest");
	if (!db.isValid())
	{
		QSqlError err = db.lastError();
		QMessageBox::critical(NULL, "��ʾ", err.text());
	}

	if (!db.open())
	{
		QSqlError err = db.lastError();

		db.close();

		QMessageBox::critical(NULL, "��ʾ", err.text());
	}
}

MyDataBase::~MyDataBase()
{
	if (db.isOpen())
		db.close();	
}



MyDataBase * MyDataBase::GetInstance()

{

	if (NULL == m_pInstance)

	{

		static QMutex mutex;

		mutex.lock();

		if (NULL == m_pInstance)

		{

			static MyDataBase myDB;

			m_pInstance = &myDB;

		}

		mutex.unlock();

	}



	return m_pInstance;

}



bool MyDataBase::ConnectAccessDB(const QString &strDBName, const QString &strUser, const QString &strPwd) const

{	
	return true;
	//odbc���÷���:http://blog.sina.com.cn/s/blog_6ff019f90102vpcs.html
	//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	//db = QSqlDatabase::addDatabase("QODBC");
	//db.setDatabaseName("VisionTest");


	//if (!db.isValid())

	//{

	//	return false;

	//}



	//if (db.isOpen())

	//{

	//	return true;

	//}



	//if (db.open())
	//{		
	//	////����һ����¼
	//	//QSqlQuery query;
	//	//bool resultt;
	//	////resultt = query.exec("create table student (id int primary key, "
	//	////	"name varchar(20))");
	//	////����һ��students��,����ֱ�Ϊid��name��score��class
	//	//query.exec("insert into student values(0, 'first')");
	//	//query.exec("insert into student values(1, 'second')");
	//	//query.exec("insert into student values(2, 'third')");
	//	//query.exec("insert into student values(3, 'fourth')");
	//	//resultt = query.exec("insert into student values(4, 'fifth')");
	//	//qDebug() << resultt;
	//	//		

	//	//db.close();
	//	return true;
	//}
	//

	//else
	//{

	//	qDebug() << db.lastError().text();

	//	return false;

	//}

}


void MyDataBase::insert_roi(const int id, const int x, const int y, const int weight, const int height)
{
	if (!db.isOpen())//�����ݿ�
		db.open();
	//�����¼
	QSqlQuery query(db);
	
	query.exec("truncate roi");
	db.close();	//�ر����ݿ�
	query.prepare("insert into roi(id, x, y, weight, height) "
		"values (:id, :x, :y, :weight, :height)");

	query.bindValue(":id", id);
	query.bindValue(":x", x);
	query.bindValue(":y", y);
	query.bindValue(":weight", weight);
	query.bindValue(":height", height);
	query.exec();
	db.close();	//�ر����ݿ�

}

void MyDataBase::show_all()
{
	QSqlQuery query;
	query.exec("select * from roi");
	while (query.next())
	{
		qDebug() << query.value(0).toInt()
			<< query.value(1).toString();
	}
}



