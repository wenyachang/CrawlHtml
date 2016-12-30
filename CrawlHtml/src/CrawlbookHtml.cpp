#include "include/CrawlBookHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QDomDocument>
#include <QTimer>	 
#include <QDebug>

CrawlBookHtml::CrawlBookHtml(QString message, QObject* parent)
{
	initParam(message);
}

CrawlBookHtml::CrawlBookHtml()
{

}

CrawlBookHtml::~CrawlBookHtml()
{
}

void CrawlBookHtml::initParam(QString message)
{
	QStringList list = message.split("$");
	if (6 == list.size())
	{
		m_strBookUrl = list.at(0);
		m_strBookRule = list.at(1);
		m_strBookNameRule = list.at(2);
		m_strAuthorRule = list.at(3);
		m_strContentRule = list.at(4);
		m_strBookPath = list.at(5);
	}

	while (m_strCurrentHtmlContent.isEmpty())
	{
		m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strBookUrl);
		sleep(5000);
	}
	sleep(5000);
	crawlBookCatalog();
	
}

void CrawlBookHtml::crawlBookCatalog()
{
	QRegExp rx(m_strBookRule);
	rx.setMinimal(true);
	if (rx.isValid())
	{
		int pos = m_strCurrentHtmlContent.indexOf(rx);
		if (pos >= 0)
		{
			if (rx.cap(0).isEmpty())
			{
				qDebug() << QString::fromLocal8Bit("CrawlBookHtml: 链接内容为空！");
				return;
			}
			splitBookCatalogHrefs(rx.cap(0));
		}
		else
		{
			qDebug() << QString::fromLocal8Bit("CrawlBookHtml: book匹配错误。") << endl;
		}
	}
}

void CrawlBookHtml::splitBookCatalogHrefs(QString catalog)
{
	
	//qDebug() << "CrawlBookHtml::catalog frefs :" << catalog << endl;
	catalog = "<p>" + catalog + "</p>";
	RegExpManager::getInstance()->removeNotPairedTags(catalog);

	QDomDocument doc;
	QString error;
	if (!doc.setContent(catalog, false, &error))
	{
		qDebug() << QString::fromLocal8Bit("CrawlBookHtml: html转xml错误。") << endl;
		return;
	}
	QDomElement root = doc.documentElement();
	QDomNodeList nodeList = root.elementsByTagName("a");
	if (nodeList.isEmpty())
	{
		qDebug() << QString::fromLocal8Bit("CrawlBookHtml: 无book链接。") << endl;
		return;
	}

	QString message = "$" + m_strContentRule + "$" + m_strBookPath + "$";
	qDebug() << QString::fromLocal8Bit("CrawlBookHtml: book目录链接数目：") << nodeList.size() << endl;
	for (int i = 0; i < nodeList.size(); ++i)
	{
		QString href = nodeList.at(i).toElement().attribute("href");
		QString text = nodeList.at(i).toElement().text();
		//qDebug() << href << endl << text << endl;
		QString num = QString("%1").arg(i+1);
		m_mapBook[text] = new CrawlSingleHtml(href + message + num + ". " + text + ".txt", false);
	}
	
}

QMap<QString, CrawlSingleHtml*> CrawlBookHtml::getBookMap()
{
	return m_mapBook;
}


