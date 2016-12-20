#include "include/CrawlSingleHtml.h"
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QString>       
#include <QRegExp>
#include <QEventLoop>
#include <QTextCodec>

#include "include/RegExpManager.h"

CrawlSingleHtml::CrawlSingleHtml(QString url, QObject* parent) 
{
	m_strUrl = url;
	getReplyContent();
}

CrawlSingleHtml::CrawlSingleHtml()
{

}

CrawlSingleHtml::~CrawlSingleHtml()
{
}

void CrawlSingleHtml::getReplyContent()
{
	QUrl url(m_strUrl);
	QNetworkAccessManager manager;
	QEventLoop loop;
	QNetworkReply *reply;
	
	reply = manager.get(QNetworkRequest(url));     
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));     
	loop.exec();

	//获取源码，打开文件  
	QFile file("code1.txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	QTextStream out(&file);

	QString codeContent = QString::fromLocal8Bit(reply->readAll());
	removeNotConcerned(codeContent);
	out << codeContent << endl;
	m_strContent = codeContent;
	file.close();
	
}

void CrawlSingleHtml::removeNotConcerned(QString &content)
{
	QVector<QRegExp> regExps = RegExpManager::getInstance()->getRegExps();
	for (int i = 0; i < regExps.size(); ++i)
	{
		content.remove(regExps.at(i));
	}
}
