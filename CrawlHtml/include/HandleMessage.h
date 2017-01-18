#ifndef HANDLEMESSAGE_H
#define HANDLEMESSAGE_H

#include <QObject>
#include <QVector>
#include <QVariant>
class HandleMessage : public QObject
{
	Q_OBJECT

	enum ExportType
	{
		books_export,
		book_export,
		article_export
	};

public:
	HandleMessage();
	~HandleMessage();

	static HandleMessage* getInstance();

	Q_INVOKABLE void setMessage(int exportType, QString message, bool isExportTxt, bool isOutSqlite, bool isRecordRule);

private:
	static HandleMessage* _Instance;

};

#endif  //HANDLEMESSAGE_H
