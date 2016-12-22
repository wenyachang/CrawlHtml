#include "include/CrawlSingleHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QStringList>

CrawlSingleHtml::CrawlSingleHtml(QString message, QObject* parent) 
{
	initParam(message);
}

CrawlSingleHtml::CrawlSingleHtml()
{

}

CrawlSingleHtml::~CrawlSingleHtml()
{
}

void CrawlSingleHtml::initParam(QString message)
{
	QStringList list = message.split("$");
	if (2 == list.size())
	{
		m_strArticleUrl = list.at(0);
		m_strContentRule = list.at(1);
	}
	m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strArticleUrl);
	crawlContent();
}

void CrawlSingleHtml::crawlContent()
{
	QRegExp rx(m_strContentRule);
	rx.setMinimal(true);
	if (rx.isValid())
	{
		int pos = m_strCurrentHtmlContent.indexOf(rx);
		if (pos >= 0)
		{
			m_strContent = rx.cap(0);
		}
	}
	RegExpManager::getInstance()->removeContentNotConcerd(m_strContent);
}

QString CrawlSingleHtml::getCrawlContent()
{
	return m_strContent;
}

