#pragma once
#include "qobject.h"
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
class RequestHtml : public QObject
{
public:
    RequestHtml();
    RequestHtml(QString url);
    ~RequestHtml();
	static RequestHtml* getInstance();
    QString getHtmlContent(QString html);

private:
    static RequestHtml* _instance;
};

