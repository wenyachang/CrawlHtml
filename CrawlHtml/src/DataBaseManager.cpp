#include "include/DataBaseManager.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QTimer>
#include <QSqlDatabase>

DataBaseManager* DataBaseManager::_Instance = NULL;
int DataBaseManager::databaseNum = 0;

DataBaseManager::DataBaseManager()
{
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_keepAwake()));
    timer->start(60 * 1000);
}

DataBaseManager::~DataBaseManager()
{
	delete _Instance;
}						  

DataBaseManager* DataBaseManager::getInstance()
{
	if (!_Instance)
	{
		_Instance = new DataBaseManager();
	}
	return _Instance;
}

QString DataBaseManager::connectDataBase()
{
    //mutex.lock();
    ++databaseNum;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", QString::number(databaseNum));
	db.setHostName("localhost");
	db.setPort(3306);
	db.setDatabaseName("novel");
	db.setUserName("root");
	db.setPassword("mysql123");
	
	if (db.open())
	{
		qDebug() << "database is established!";
		db.exec("set names 'UTF8'");
        return QString::number(databaseNum);
	}
	else
	{
		qDebug() << db.lastError().text();
	}
    //mutex.unlock();
    return QString();
}

void DataBaseManager::slot_keepAwake()
{
    QSqlQuery query(QSqlDatabase::database(connectDataBase()));
    if (!query.exec("select count(*) from novel_social_life"))
    {
        //qDebug() << query.lastError();
    }
}



