#include "include/DataBaseManager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

DataBaseManager* DataBaseManager::_Instance = NULL;

DataBaseManager::DataBaseManager()
{
	
}

DataBaseManager::~DataBaseManager()
{
	
}						  

DataBaseManager* DataBaseManager::getInstance()
{
	if (!_Instance)
	{
		_Instance = new DataBaseManager();
	}
	return _Instance;
}

void DataBaseManager::connectDataBase()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
	db.setDatabaseName("novel");
	db.setUserName("root");
	db.setPassword("mysql123");
	
	if (db.open())
	{
		qDebug() << "database is established!";
		db.exec("set names 'UTF8'");
	}
	else
	{
		qDebug() << db.lastError().text();
	}
}

void DataBaseManager::closeDataBase()
{
	db.close();
}


