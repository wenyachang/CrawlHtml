#include "include/CrawlSingleHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QStringList>
#include <QTimer>
#include <QDir>
#include <QSqlQuery>

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

	while (m_strCurrentHtmlContent.isEmpty())
	{
		m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strArticleUrl);
		sleep(5000);
	}
	sleep(5000);
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
		else
		{
			qDebug() << QString::fromLocal8Bit("CrawlSingleHtml: articleÆ¥Åä´íÎó¡£") << endl;
		}
	}
	RegExpManager::getInstance()->removeContentNotConcerd(m_strContent);
	exportArticle();
	exportToMysql();
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

void CrawlSingleHtml::exportToMysql()
{
	QStringList list = m_strBookPath.split("/");

	qDebug() << list.at(list.size() - 1) << endl;
	qDebug() << m_strArticleName << endl;

	QSqlQuery query;
	query.prepare("insert into novel_social_life (topic, name, content) values (:topic, :name, :content)");
	query.bindValue(":topic", list.at(list.size() - 1));
	query.bindValue(":name", m_strArticleName);
	query.bindValue(":content", m_strContent);
	query.exec();
}

