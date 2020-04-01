
#include "mydatabase.h"

#include <QDebug>
#include <algorithm>
#include <iostream>
using namespace std;

MyDataBase * MyDataBase::m_pInstance(NULL);



MyDataBase::MyDataBase()

{



}

MyDataBase::~MyDataBase()

{



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
	//odbc配置方法:http://blog.sina.com.cn/s/blog_6ff019f90102vpcs.html
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	db.setDatabaseName("VisionTest");


	if (!db.isValid())

	{

		return false;

	}



	if (db.isOpen())

	{

		return true;

	}



	if (db.open())
	{		
		//插入一条记录
		QSqlQuery query;
		bool resultt;
		//resultt = query.exec("create table student (id int primary key, "
		//	"name varchar(20))");
		//创建一个students表,标题分别为id、name、score、class
		query.exec("insert into student values(0, 'first')");
		query.exec("insert into student values(1, 'second')");
		query.exec("insert into student values(2, 'third')");
		query.exec("insert into student values(3, 'fourth')");
		resultt = query.exec("insert into student values(4, 'fifth')");
		qDebug() << resultt;
				

		db.close();
		return true;
	}
	

	else
	{

		qDebug() << db.lastError().text();

		return false;

	}

}
