#include "include/CrawlSingleHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QStringList>
#include <QTimer>
#include <QDir>

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
	if (4 == list.size())
	{
		m_strArticleUrl = list.at(0);
		m_strContentRule = list.at(1);
		m_strBookPath = list.at(2);
		m_strArticleName = list.at(3);
	}

	int count = 0;
	while (m_strCurrentHtmlContent.isEmpty() && count < 3)
	{
		m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strArticleUrl);
		count++;
	}
	QTimer::singleShot(5000, this, SLOT(crawlContent()));
	
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
	exportArticle();
}

QString CrawlSingleHtml::getCrawlContent()
{
	return m_strContent;
}

void CrawlSingleHtml::exportArticle()
{
	QDir *newDir = new QDir;
	if (!newDir->exists(m_strBookPath))
	{
		if (newDir->mkdir(m_strBookPath))
		{
			writeArticleToTxt();
		}
		else
		{
			qDebug() << "error : write article to txt." << endl;
		}

	}
	else
	{
		writeArticleToTxt();
	}
}

void CrawlSingleHtml::writeArticleToTxt()
{
	QFile file(m_strBookPath + "/"+ m_strArticleName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	QTextStream out(&file);
	out << m_strContent;
}

