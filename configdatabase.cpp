
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

void ConfigDataBase::update_LineType(const vector<Line_Type> vec_linetype, const vector<Vec3f> vec_stdLines)
{
	if (!db.isOpen())//�����ݿ�
		db.open();
	//�����¼
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

void ConfigDataBase::read_mission(vector<Mission>& vec_mission)
{
	QSqlQuery query;	
	query.exec("select * from Mission");
	while (query.next())
	{
		Mission temp_mission;
		temp_mission.type = TypeOfMission(query.value(1).toInt());//����
		temp_mission.vec_object.push_back(query.value(3).toInt());//����1
		if(!query.value(3).isNull())//����2��Ϊ��
			temp_mission.vec_object.push_back(query.value(3).toInt());//����2	
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
		//��ȡroi ID
		strroi.ID = query.value(0).toInt();

		//��ȡroi����	
		for (int i = 0; i < 4; i++)
			strroi.roipar[i] = query.value(i + 1).toInt();

		//��ȡroi�б�Ե����
		 strroi.linetype = (Line_Type)query.value(5).toInt();

		//��ȡ��׼��ֱ�߲���
		Vec3f stdline;
		for (int i = 0; i < 3; i++)
			strroi.stdline[i] = query.value(i + 6).toDouble();

		//����vector
		vec_strrois.push_back(strroi);		
	}
}

bool IsTableExist(QSqlQuery &query, QString table)
{
	QString sql = QString("select table_name from information_schema.TABLES WHERE table_name = '%1'").arg(table);
	qDebug() << sql << endl;
	query.exec(sql);
	return query.next();
}

bool ConfigDataBase::save_stdpoints(const vector<struct_roi> vec_strrois)
{
	if (!db.isOpen())//�����ݿ�
		db.open();
	bool flag_save = false;
	bool flag_build = false;
	for (auto it_toi : vec_strrois)
	{
		//�����ӱ�
		QSqlQuery query(db);
		QString subtablename = "roi" + QString::number(it_toi.ID);//�ӱ�����
		query.prepare(QString("create table %1(ID int primary key,x double,y double)").arg(subtablename));//����
		flag_build = query.exec();
		//��������
		if (!flag_build)//����ʧ�ܣ�����
			return flag_build;
		else//����ɹ�����������
		{
			//������Ե��
			int point_id = 0;
			bool flag_save = false;
			for (auto it_SubPixelEdgePoint : it_toi.VecSubPixelEdgePoint)
			{
				query.prepare(QString("insert into %1(id, x, y)").arg(subtablename) +
					"values (:id, :x, :y)");
				query.bindValue(":id", point_id);
				query.bindValue(":x", it_SubPixelEdgePoint.x);
				query.bindValue(":y", it_SubPixelEdgePoint.y);
				flag_save = query.exec();
				point_id++;
			}			
		}
	}		
	db.close();	//�ر����ݿ�
	return flag_save;;
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






