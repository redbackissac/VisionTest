#pragma once
#ifndef CONFIGDATABASE_H
#define CONFIGDATABASE_H
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
#include <opencv2\opencv.hpp>
#include "imgAlgorithm.h"


class ConfigDataBase

{

public:

	ConfigDataBase();

	~ConfigDataBase();

private:

	ConfigDataBase(const ConfigDataBase &);

	ConfigDataBase operator =(const ConfigDataBase &);
	QSqlDatabase db;

public:
	//void insert_Mission(const int id, const int Type,const int obj1,const int obj2);
	void insert_Mission(const int id, const Mission mission);
	void insert_roi(const int id, const int x, const int y, const int weight, const int height);
	void read_roi(VecRoiParas &vec_roipars);//�����ݿ��ж�ȡroi����;
	void show_all();//��ʾ��������
	//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	//QSqlDatabase db;
	static ConfigDataBase * GetInstance();

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

	static ConfigDataBase *m_pInstance;



};

