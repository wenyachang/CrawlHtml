#include "include/CrawlBooksHtml.h"
#include "include/NetworkManager.h"
#include "include/RegExpManager.h"
#include "include/CrawlThread.h"
#include <QDomDocument>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

CrawlBooksHtml::CrawlBooksHtml(QString message, QObject* parent)
{
	m_strConfigPath = QCoreApplication::applicationDirPath() + "/config/exportedBooks.txt";
	exportedBooks = readTxtFileByLine(m_strConfigPath);
	initParam(message);
}

CrawlBooksHtml::CrawlBooksHtml()
{

}

CrawlBooksHtml::~CrawlBooksHtml()
{

}

void CrawlBooksHtml::initParam(QString message)
{
	QStringList list = message.split("$");
	if (6 == list.size())
	{
		m_strBooksUrl = list.at(0);
		m_strBooksRule = list.at(1);
		m_strBookRule = list.at(2);
		m_strBookNameRule = list.at(3);
		m_strAuthorRule = list.at(4);
		m_strContentRule = list.at(5);
	}
	m_strBookPath = QCoreApplication::applicationDirPath();


	while (m_strCurrentHtmlContent.isEmpty())
	{
		m_strCurrentHtmlContent = NetworkManager::getInstance()->getHtmlContent(m_strBooksUrl);
		sleep(5000);
	}
	//sleep(5000);
	crawlBookHref();
}

void CrawlBooksHtml::crawlBookHref()
{
	QRegExp rx(m_strBooksRule);
	rx.setMinimal(true);
	if (rx.isValid())
	{
		int pos = m_strCurrentHtmlContent.indexOf(rx);
		if (pos >= 0)
		{
			if (rx.cap(0).isEmpty())
			{
				qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: ÎÞÆ¥ÅäÄÚÈÝ¡£") << endl;
				return;
			}
			splitBooksHrefs(rx.cap(0));
		}
		else
		{
			qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: booksÆ¥Åä´íÎó¡£") << endl;
		}
	} 
}

void CrawlBooksHtml::splitBooksHrefs(QString hrefs)
{
	RegExpManager::getInstance()->removeNotPairedTags(hrefs);
	QDomDocument doc;
	QString error;
	if (!doc.setContent(hrefs, false, &error))
	{
		qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: html×ªxml´íÎó¡£") << endl;
		appendLog(QString::fromLocal8Bit("CrawlBooksHtml: html×ªxml´íÎó¡£"));
		return;
	}
	QDomElement root = doc.documentElement();
	QDomNodeList nodeList = root.elementsByTagName("a");
	if (nodeList.isEmpty())
	{
		qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: ÎÞbooksÁ´½Ó¡£") << endl;
		appendLog(QString::fromLocal8Bit("CrawlBooksHtml: ÎÞbooksÁ´½Ó¡£"));
		return;
	}
	QString message = "$" + m_strBookRule + "$" + m_strBookNameRule + "$" + m_strAuthorRule + "$" + m_strContentRule + "$";
	for (int i = 0; i < nodeList.size(); ++i)
	{
		QString href = nodeList.at(i).toElement().attribute("href");
		QString text = nodeList.at(i).toElement().text();
		if (!isBookExported(text))
		{
			exportedBooks.append(text);
			writeTxtFileByLine(m_strConfigPath, text);
            QString temp = text;
            RegExpManager::getInstance()->removeFolderNameNotIncluded(temp);

            CrawlThread* thread = new CrawlThread(href + message + m_strBookPath + "/" + temp + "$" + text);
            thread->start();

			while (thread->isRunning())
			{
				sleep(2 * 60 * 1000);
			}

			if (thread->isFinished())
			{
				delete thread;
			}
		}	
		else
		{
			qDebug() << text << "has exported!" << endl;
			appendLog(text + "has exported!");
		}
	}
	
}

bool CrawlBooksHtml::isBookExported(QString bookName)
{
	for (int i = 0; i < exportedBooks.size(); ++i)
	{
		if (exportedBooks.at(i).trimmed() == bookName.trimmed())
		{
			return true;
		}
	}
	return false;
}



