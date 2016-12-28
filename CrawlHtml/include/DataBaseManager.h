#include <QObject>
#include <QtSql/QSqlDatabase>

class DataBaseManager : public QObject
{
	Q_OBJECT

public:
	DataBaseManager();
	~DataBaseManager();

	static DataBaseManager* getInstance();

	void connectDataBase();
	void closeDataBase();

private:
	static DataBaseManager* _Instance;
	QSqlDatabase db;

};

