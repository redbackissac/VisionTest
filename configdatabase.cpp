
#include "configdatabase.h"

#include <QDebug>
#include <algorithm>
#include <iostream>
using namespace std;

ConfigDataBase * ConfigDataBase::m_pInstance(NULL);



ConfigDataBase::ConfigDataBase()

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

ConfigDataBase::~ConfigDataBase()
{
	if (db.isOpen())
		db.close();	
}



ConfigDataBase * ConfigDataBase::GetInstance()

{

	if (NULL == m_pInstance)

	{

		static QMutex mutex;

		mutex.lock();

		if (NULL == m_pInstance)

		{

			static ConfigDataBase myDB;

			m_pInstance = &myDB;

		}

		mutex.unlock();

	}



	return m_pInstance;

}



bool ConfigDataBase::ConnectAccessDB(const QString &strDBName, const QString &strUser, const QString &strPwd) const

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


void ConfigDataBase::insert_Mission(const int id, const Mission mission)
{
	if (!db.isOpen())//�����ݿ�
		db.open();
	//�����¼
	QSqlQuery query(db);	

	query.prepare("insert into Mission(id, Type, Object1, Object2) "
		"values (:id, :Type, :Object1, :Object2)");

	query.bindValue(":id", id);
	query.bindValue(":Type", mission.type);
	query.bindValue(":Object1", mission.vec_object[0]);
	if(mission.vec_object.size() == 2)
		query.bindValue(":Object2", mission.vec_object[1]);
	query.exec();
	db.close();	//�ر����ݿ�
}

void ConfigDataBase::insert_roi(const int id, const int x, const int y, const int weight, const int height)
{
	if (!db.isOpen())//�����ݿ�
		db.open();
	//�����¼
	QSqlQuery query(db);
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

void ConfigDataBase::read_roi(VecRoiParas &vec_roipars)
{
	QSqlQuery query;
	query.exec("select * from roi");
	while (query.next())
	{
		Vec4i roipar;
		for (int i = 0; i < 4; i++)
			roipar[i] = query.value(i + 1).toInt();
		vec_roipars.push_back(roipar);
		//qDebug() << query.value(0).toInt() << query.value(1).toInt() << query.value(2).toInt() << query.value(3).toInt() << query.value(4).toInt();
	}
}

void ConfigDataBase::show_all()
{
	QSqlQuery query;
	query.exec("select * from roi");
	while (query.next())
	{
		qDebug() << query.value(0).toInt()
			<< query.value(1).toString();
	}
}



