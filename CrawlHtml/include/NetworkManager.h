#ifndef NetworkManager_H
#define NetworkManager_H

#include "qobject.h"
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>

const QString API_TOKEN = "DHUDHIUEI34EHDEHWUE8D23E31D2";

class NetworkManager : public QObject
{
	Q_OBJECT

public:
    NetworkManager();
    NetworkManager(QString url);
    ~NetworkManager();
	static NetworkManager* getInstance();
    QString getHtmlContent(QString html);

	QByteArray post_message(QString url, QByteArray data);
	QByteArray get_message(QString url, QString content);

	//创建书籍
	int createBook(QString name, QString intro);
	//更新书籍
	void updateBook(int book_id);
	//创建目录
	int crateCatalog(int book_id, int sort_id, QString menu_name);
	//创建文章
	int createArticle(int book_id, int book_menu_id, QString title, QString content);

	QString getTagMessage(QByteArray message, QString tag);

public slots:
    void slotError(QNetworkReply::NetworkError error);

private:
    static NetworkManager* _instance;
	QNetworkAccessManager* m_accessManager;
};

#endif  //NetworkManager_H
						  