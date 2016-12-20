#pragma once
#include "qobject.h"
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
class RequestHtml : public QObject
{
public:
    RequestHtml();
    RequestHtml(QString url);
    ~RequestHtml();
    static RequestHtml* instance();
    QString getHtmlContent(QString url);

private:
    static RequestHtml* _instance;
};

