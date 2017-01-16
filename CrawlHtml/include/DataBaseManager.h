#pragma once

#include <QObject>
#include <QtSql/QSqlDatabase>

class DataBaseManager : public QObject
{
	Q_OBJECT

public:
	DataBaseManager();
	~DataBaseManager();

	static DataBaseManager* getInstance();
    static int databaseNum;

    QString connectDataBase();

public slots:
    void slot_keepAwake();

private:
	static DataBaseManager* _Instance;
    QMutex mutex;

};

