#include "include/RequestHtml.h"
#include <QTextCodec>

RequestHtml* RequestHtml::_instance = NULL;

RequestHtml::RequestHtml()
{
}

RequestHtml::RequestHtml(QString url)
{

}


RequestHtml::~RequestHtml()
{
}

RequestHtml* RequestHtml::getInstance()
{
    if (!_instance)
    {
        return new RequestHtml();
    }
    return _instance;
}

QString RequestHtml::getHtmlContent(QString html)
{
	QUrl url(html);
	QNetworkAccessManager manager;
	QEventLoop loop;
	QNetworkReply *reply;

	reply = manager.get(QNetworkRequest(url));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QTextCodec* code = QTextCodec::codecForName("utf-8");
	return code->toUnicode(reply->readAll());
	//return QString::fromLocal8Bit(reply->readAll());
}
