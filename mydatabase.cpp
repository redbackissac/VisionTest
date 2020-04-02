
#include "mydatabase.h"

#include <QDebug>
#include <algorithm>
#include <iostream>
using namespace std;

MyDataBase * MyDataBase::m_pInstance(NULL);



MyDataBase::MyDataBase()

{
	//odbc配置方法:http://blog.sina.com.cn/s/blog_6ff019f90102vpcs.html
	db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName("VisionTest");
	if (!db.isValid())
	{
		QSqlError err = db.lastError();
		QMessageBox::critical(NULL, "提示", err.text());
	}

	if (!db.open())
	{
		QSqlError err = db.lastError();

		db.close();

		QMessageBox::critical(NULL, "提示", err.text());
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
	//odbc配置方法:http://blog.sina.com.cn/s/blog_6ff019f90102vpcs.html
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
	//	////插入一条记录
	//	//QSqlQuery query;
	//	//bool resultt;
	//	////resultt = query.exec("create table student (id int primary key, "
	//	////	"name varchar(20))");
	//	////创建一个students表,标题分别为id、name、score、class
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
	if (!db.isOpen())//打开数据库
		db.open();
	//插入记录
	QSqlQuery query(db);
	
	query.exec("truncate roi");
	db.close();	//关闭数据库
	query.prepare("insert into roi(id, x, y, weight, height) "
		"values (:id, :x, :y, :weight, :height)");

	query.bindValue(":id", id);
	query.bindValue(":x", x);
	query.bindValue(":y", y);
	query.bindValue(":weight", weight);
	query.bindValue(":height", height);
	query.exec();
	db.close();	//关闭数据库

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



