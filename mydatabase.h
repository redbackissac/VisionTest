#pragma once
#ifndef MYDATABASE_H
#define MYDATABASE_H
#endif 
#include <QString>
#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QtDebug>
#include <QSqlDatabase>
#include <QStringList>
#include <QSqlError>
#include <QSqlIndex>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QVariant>
#include <QMutex>
#include <QMessageBox>


class MyDataBase

{

public:

	MyDataBase();

	~MyDataBase();

private:

	MyDataBase(const MyDataBase &);

	MyDataBase operator =(const MyDataBase &);
	QSqlDatabase db;

public:

	void insert_roi(const int id, const int x, const int y, const int weight, const int height);
	void show_all();//显示所有内容
	//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	//QSqlDatabase db;
	static MyDataBase * GetInstance();

	bool ConnectAccessDB(const QString &strDBName,

		const QString &strUser,

		const QString &strPwd) const;

	QSqlDatabase GetDatabase() const

	{

		return QSqlDatabase::database("MyAccessDB");

	}



	QSqlQuery GetSqlQuery() const

	{

		static QSqlQuery query(m_pInstance->GetDatabase());

		return query;

	}



	bool IsValid() const

	{

		return this->GetDatabase().isValid();

	}

	bool IsConnected() const

	{

		return this->GetDatabase().isOpen();

	}



private:

	static MyDataBase *m_pInstance;



};


