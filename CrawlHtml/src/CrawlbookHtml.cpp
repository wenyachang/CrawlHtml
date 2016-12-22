#include "include/CrawlBookHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QDomDocument>

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
	if (5 == list.size())
	{
		m_strBookUrl = list.at(0);
		m_strBookRule = list.at(1);
		m_strBookNameRule = list.at(2);
		m_strAuthorRule = list.at(3);
		m_strContentRule = list.at(4);
	}
	m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strBookUrl);
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
			splitBookCatalogHrefs(rx.cap(0));
		}
	}
}

void CrawlBookHtml::splitBookCatalogHrefs(QString catalog)
{
	RegExpManager::getInstance()->removeNotPairedTags(catalog);

	QDomDocument doc;
	QString error;
	if (!doc.setContent(catalog, false, &error))
	{
		qDebug() << error << endl;
		return;
	}
	QDomElement root = doc.documentElement();
	QDomNodeList nodeList = root.elementsByTagName("a");
	if (nodeList.isEmpty())
	{
		return;
	}
	//QString message =  "$" + m_strBookNameRule + "$" + m_strAuthorRule + "$" + m_strContentRule;
	QString message = "$" + m_strContentRule;
	for (int i = 0; i < nodeList.size(); ++i)
	{
		QString href = nodeList.at(i).toElement().attribute("href");
		QString text = nodeList.at(i).toElement().text();
		qDebug() << href << endl << text << endl;
		m_mapBook[text] = new CrawlSingleHtml(href + message, false);
	}
	
}

QMap<QString, CrawlSingleHtml*> CrawlBookHtml::getBookMap()
{
	return m_mapBook;
}


