
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
	/*QStringList drivers = QSqlDatabase::drivers();
	foreach(QString driver, drivers)
		qDebug() << driver;*/
	
	/*QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "MyAccessDB");*/
	
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	//const QString strName(QString("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=%1;Uid=%2;Pwd=%3")

	//	.arg(strDBName)

	//	.arg(strUser)

	//	.arg(strPwd));
	//db.setDatabaseName(strName);
	db.setDatabaseName("VisionTest");
	//db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=VisionTest.mdb");
	//db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=bacode.mdb");
	//db.setDatabaseName("barcode");
	/*db.setHostName("acidalia");
	db.setDatabaseName("customdb");*/
	/*db.setUserName("szlg");
	db.setPassword("123456");*/
	//qDebug() << strName;

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

		        QStringList p=db.tables(QSql::AllTables);

		        for(int i=0;i<p.count();i++)

		        {

		            qDebug()<<p[i];

		        }

		return true;

	}

	else

	{

		qDebug() << db.lastError().text();

		return false;

	}

}
