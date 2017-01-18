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
	sleep(5000);
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
				qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: ��ƥ�����ݡ�") << endl;
				return;
			}
			splitBooksHrefs(rx.cap(0));
		}
		else
		{
			qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: booksƥ�����") << endl;
		}
	} 
}

void CrawlBooksHtml::splitBooksHrefs(QString hrefs)
{
	RegExpManager::getInstance()->removeNotPairedTags(hrefs);
	//qDebug() << "CrawlBooksHtml::book frefs :" << hrefs << endl;
	QDomDocument doc;
	QString error;
	if (!doc.setContent(hrefs, false, &error))
	{
		qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: htmlתxml����") << endl;
		return;
	}
	QDomElement root = doc.documentElement();
	QDomNodeList nodeList = root.elementsByTagName("a");
	if (nodeList.isEmpty())
	{
		qDebug() << QString::fromLocal8Bit("CrawlBooksHtml: ��books���ӡ�") << endl;
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
            writeTxtFileByLine(exportedBooks, m_strConfigPath);
            QString temp = text;
            RegExpManager::getInstance()->removeFolderNameNotIncluded(temp);

            CrawlThread* thread = new CrawlThread(href + message + m_strBookPath + "/" + temp + "$" + text);
            thread->start();
            sleep(2 * 60 * 1000);
			//m_mapBooks[text] = new CrawlBookHtml(href + message + m_strBookPath + "/" + temp + "$" + text, false);
		}	
		else
		{
			qDebug() << text << "has exported!" << endl;
            QString log = getCurrentTime() + ":  " + text + "has exported!";
            writeTxtFileByLine(getLogPath(), log);
		}
	}
	
}

void CrawlBooksHtml::exportOneBook(QString bookName)
{
	CrawlBookHtml* book = m_mapBooks[bookName];
	QDir *newDir = new QDir;
	QString path = QCoreApplication::applicationDirPath();
	if (!newDir->exists(path + "/" + bookName))
	{
		bool ok = newDir->mkdir(path + "/" + bookName);
		if (ok)
		{
			QMap<QString, CrawlSingleHtml*>::const_iterator iter = book->getBookMap().constBegin();
			while (iter != book->getBookMap().constEnd())
			{
				QFile file(path + "/" + bookName + "/" + iter.key() + ".txt");
				if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
				{
					return;
				}
				QTextStream out(&file);
				CrawlSingleHtml* content = iter.value();
				out << content->getCrawlContent();
			}
		}
	}
}

void CrawlBooksHtml::exportToTxt()
{													 
	QMap<QString, CrawlBookHtml*>::const_iterator iter = m_mapBooks.constBegin();
	while (iter != m_mapBooks.constEnd())
	{
		QDir *newDir = new QDir;
		if (!newDir->exists("../export/" + iter.key()))
		{
			bool ok = newDir->mkdir("../export/" + iter.key());
			if (ok)
			{
				CrawlBookHtml* book = iter.value();
				QMap<QString, CrawlSingleHtml*>::const_iterator iter1 = book->getBookMap().constBegin();
				while (iter1 != book->getBookMap().constEnd())
				{
					QFile file(newDir->absolutePath() +"/" +iter1.key() + ".txt");
					if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
					{
						return;
					}
					QTextStream out(&file);
					CrawlSingleHtml* content = iter1.value();
					out << content->getCrawlContent();
				}
			}
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



