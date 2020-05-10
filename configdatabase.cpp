
#include "configdatabase.h"

#include <QDebug>
#include <algorithm>
#include <iostream>
using namespace std;

ConfigDataBase * ConfigDataBase::m_pInstance(NULL);



ConfigDataBase::ConfigDataBase()

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
	//odbc配置方法:http://blog.sina.com.cn/s/blog_6ff019f90102vpcs.html
	//QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
	//db = QSqlDatabase::addDatabase("QODBC");
	//db.setDatabaseName("VisionTest");

}


void ConfigDataBase::insert_Mission(const int id, const Mission mission)
{
	if (!db.isOpen())//打开数据库
		db.open();
	//插入记录
	QSqlQuery query(db);	

	query.prepare("insert into Mission(id, Type, Object1, Object2) "
		"values (:id, :Type, :Object1, :Object2)");

	query.bindValue(":id", id);
	query.bindValue(":Type", mission.type);
	query.bindValue(":Object1", mission.vec_object[0]);
	if(mission.vec_object.size() == 2)
		query.bindValue(":Object2", mission.vec_object[1]);
	query.exec();
	db.close();	//关闭数据库
}

void ConfigDataBase::insert_roi(const int id, const int x, const int y, const int weight, const int height)
{
	if (!db.isOpen())//打开数据库
		db.open();
	//插入记录
	QSqlQuery query(db);
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

void ConfigDataBase::update_LineType(const vector<Line_Type> vec_linetype, const vector<Vec3f> vec_stdLines)
{
	if (!db.isOpen())//打开数据库
		db.open();
	//插入记录
	int ID = 0;
	for (auto it_linetype : vec_linetype)
	{
		QSqlQuery query(db);
		query.prepare("update roi set LineType=? where ID=?");
		query.addBindValue(it_linetype);
		query.addBindValue(ID);
		query.exec();
		ID++;
	}
	ID = 0;
	for (auto it_stdLine : vec_stdLines)
	{
		QSqlQuery query(db);	
		query.prepare("update roi set a=?, b=?, c=? where ID=?");
		query.addBindValue((double)it_stdLine[0]);
		query.addBindValue((double)it_stdLine[1]);
		query.addBindValue((double)it_stdLine[2]);
		query.addBindValue(ID);		
		ID++;		
	}
	db.close();	//关闭数据库
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

void ConfigDataBase::read_mission(vector<Mission>& vec_mission)
{
	QSqlQuery query;	
	query.exec("select * from Mission");
	while (query.next())
	{
		Mission temp_mission;
		temp_mission.type = TypeOfMission(query.value(1).toInt());//类型
		temp_mission.vec_object.push_back(query.value(3).toInt());//对象1
		if(!query.value(3).isNull())//对象2不为空
			temp_mission.vec_object.push_back(query.value(3).toInt());//对象2	
		vec_mission.push_back(temp_mission);
	}
}

void ConfigDataBase::read_lines(vector<Line_Type>& vec_linetype, vector<Vec3f> &vec_stdLines)
{
	QSqlQuery query;
	query.exec("select * from roi");
	while (query.next())
	{
		Line_Type linetype = (Line_Type)query.value(5).toInt();
		vec_linetype.push_back(linetype);

		Vec3f stdline;
		for (int i = 0; i < 3; i++)
			stdline[i] = query.value(i + 6).toDouble();
		
		vec_stdLines.push_back(stdline);		
	}
}

void ConfigDataBase::read_structroi(vector<struct_roi>& vec_strrois)
{

	QSqlQuery query;
	query.exec("select * from roi");
	while (query.next())
	{	
		struct_roi strroi;
		//读取roi参数	
		for (int i = 0; i < 4; i++)
			strroi.roipar[i] = query.value(i + 1).toInt();

		//读取roi中边缘类型
		 strroi.linetype = (Line_Type)query.value(5).toInt();

		//读取标准板直线参数
		Vec3f stdline;
		for (int i = 0; i < 3; i++)
			strroi.stdline[i] = query.value(i + 6).toDouble();

		//存入vector
		vec_strrois.push_back(strroi);		
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



