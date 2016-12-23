#include "include/CrawlBookHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QDomDocument>
#include <QTimer>

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

	int count = 0;
	while (m_strCurrentHtmlContent.isEmpty() && count < 3)
	{
		m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strBookUrl);
		count++;
	}
	QTimer::singleShot(5000, this, SLOT(crawlBookCatalog()));
	
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
	catalog = "<p>" + catalog + "</p>";
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

	QString message = "$" + m_strContentRule + "$" + m_strBookPath + "$";
	for (int i = 0; i < nodeList.size(); ++i)
	{
		QString href = nodeList.at(i).toElement().attribute("href");
		QString text = nodeList.at(i).toElement().text();
		qDebug() << href << endl << text << endl;
		QString num = QString("%1").arg(i+1);
		m_mapBook[text] = new CrawlSingleHtml(href + message + num + ". " + text + ".txt", false);
	}
	
}

QMap<QString, CrawlSingleHtml*> CrawlBookHtml::getBookMap()
{
	return m_mapBook;
}


