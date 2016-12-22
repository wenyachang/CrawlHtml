#include "include/CrawlBooksHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QDomDocument>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

CrawlBooksHtml::CrawlBooksHtml(QString message, QObject* parent)
{
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
	m_strCurrentHtmlContent = RequestHtml::getInstance()->getHtmlContent(m_strBooksUrl);
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
			splitBooksHrefs(rx.cap(0));
		}
	} 
}

void CrawlBooksHtml::splitBooksHrefs(QString hrefs)
{
	/*int pos = 0;
	QRegExp rx("<a href=\"(.*)\">");
	while ((pos = rx.indexIn(hrefs, pos)) != -1)
	{
		pos += rx.matchedLength();
		QString a = rx.cap(1);
		m_vecBooks.append(new CrawlBookHtml(rx.cap(1)));
	}*/

	/*QFile file("D:/1.xml");
	if (!file.open(QFile::ReadOnly))
	{
	return;
	}*/

	RegExpManager::getInstance()->removeNotPairedTags(hrefs);

	QDomDocument doc;
	QString error;
	if (!doc.setContent(hrefs, false, &error))
	{
		return;
	}
	QDomElement root = doc.documentElement();
	QDomNodeList nodeList = root.elementsByTagName("a");
	if (nodeList.isEmpty())
	{
		return;
	}
	QString message = "$" + m_strBookRule  + "$" + m_strBookNameRule + "$" + m_strAuthorRule +"$" +m_strContentRule;
	for (int i = 0; i < nodeList.size(); ++i)
	{
		QString href = nodeList.at(i).toElement().attribute("href");
		QString text = nodeList.at(i).toElement().text();
		qDebug() << href << endl << text << endl;
		m_mapBooks[text] = new CrawlBookHtml(href + message, false);
		exportOneBook(text);
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



