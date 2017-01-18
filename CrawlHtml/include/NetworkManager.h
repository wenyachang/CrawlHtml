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
public:
    NetworkManager();
    NetworkManager(QString url);
    ~NetworkManager();
	static NetworkManager* getInstance();
    QString getHtmlContent(QString html);

	void post_message(QString url, QByteArray data);
	void get_message(QString url, QString content);

	//创建书籍
	void createBook(QString name, QString intro);
	//更新书籍
	void updateBook(int book_id);
	//创建目录
	void crateCatalog(int book_id, int sort_id, QString menu_name);
	//创建文章
	void createArticle(int book_id, int book_menu_id);

public slots:
    void slotError(QNetworkReply::NetworkError error);

private:
    static NetworkManager* _instance;
	QNetworkAccessManager* m_accessManager;
};

#endif  //NetworkManager_H
						  