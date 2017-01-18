#include "include/CrawlBookHtml.h"
#include "include/NetworkManager.h"
#include "include/RegExpManager.h"
#include "include/DataBaseManager.h"
#include <QDomDocument>
#include <QTimer>	 
#include <QDebug>
#include <QSqlDatabase>

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
	if (7 == list.size())
	{
		m_strBookUrl = list.at(0);
		m_strBookRule = list.at(1);
		m_strBookNameRule = list.at(2);
		m_strAuthorRule = list.at(3);
		m_strContentRule = list.at(4);
		m_strBookPath = list.at(5);
        m_strBookName = list.at(6);
	}

	while (m_strCurrentHtmlContent.isEmpty())
	{
		m_strCurrentHtmlContent = NetworkManager::getInstance()->getHtmlContent(m_strBookUrl);
		sleep(10000);
	}
	sleep(10000);
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
			splitBookCatalogHrefs3(rx.cap(0));
		}
		else
		{
			qDebug() << QString::fromLocal8Bit("CrawlBookHtml: book匹配错误。") << endl;
		}
	}
}

void CrawlBookHtml::splitBookCatalogHrefs2(QString catalog)
{
	
	////qDebug() << "CrawlBookHtml::catalog frefs :" << catalog << endl;
	//catalog = "<p>" + catalog + "</p>";
	//RegExpManager::getInstance()->removeNotPairedTags(catalog);

	//QDomDocument doc;
	//QString error;
	//if (!doc.setContent(catalog, false, &error))
	//{
	//	qDebug() << QString::fromLocal8Bit("CrawlBookHtml: html转xml错误。") << endl;
	//	return;
	//}
	//QDomElement root = doc.documentElement();
	//QDomNodeList nodeList = root.elementsByTagName("a");
	//if (nodeList.isEmpty())
	//{
	//	qDebug() << QString::fromLocal8Bit("CrawlBookHtml: 无book链接。") << endl;
	//	return;
	//}

	//QString message = "$" + m_strContentRule + "$" + m_strBookPath + "$";
	//qDebug() << QString::fromLocal8Bit("CrawlBookHtml: book目录链接数目：") << nodeList.size() << endl;
	//for (int i = 0; i < nodeList.size(); ++i)
	//{
	//	QString href = nodeList.at(i).toElement().attribute("href");
	//	QString text = nodeList.at(i).toElement().text();
	//	//qDebug() << href << endl << text << endl;
	//	QString num = QString("%1").arg(i+1);
	//	m_mapBook[text] = new CrawlSingleHtml(href + message + num + ". " + text, false);
	//}
	
}

QMap<QString, CrawlSingleHtml*> CrawlBookHtml::getBookMap()
{
	return m_mapBook;
}

void CrawlBookHtml::splitBookCatalogHrefs3(QString catalog)
{
    catalog = "<p>" + catalog + "</p>";
    
    QRegExp te("<h3>(.*)</h3>");
    te.setMinimal(true);
    QStringList list1 = catalog.split(te);

    QStringList list2;
    int pos = 0;
    while ((pos = te.indexIn(catalog,pos)) != -1)
    {
        list2 << te.cap(1);
        pos += te.matchedLength();
    }

    QRegExp rx("<(.*)>");
    rx.setMinimal(true);
    QString introduction = list1.at(0);
    introduction.remove(rx);

    if (list1.size() == list2.size() + 1)
    {
        for (int i = 0; i < list2.size(); ++i)
        {
            splitWithSecondaryDirectory(introduction, list2.at(i), list1.at(i + 1));
        }
    }
    
}

void CrawlBookHtml::splitWithSecondaryDirectory(QString introduction, QString secondDir, QString hrefs)
{
    RegExpManager::getInstance()->removeNotPairedTags(hrefs);
    hrefs = "<p>" + hrefs + "</p>";

    QDomDocument doc;
    QString error;
    if (!doc.setContent(hrefs, false, &error))
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
	
	QString logBook = getCurrentTime() + ":  " + m_strBookName + 
		          QString::fromLocal8Bit("CrawlBookHtml: book目录链接数目：") + QString::number(nodeList.size());
	writeTxtFileByLine(getLogPath(), logBook);
	qDebug() << logBook << endl;

    QString message = "$" + m_strContentRule + "$" + m_strBookPath + "$";
    QString db = DataBaseManager::getInstance()->connectDataBase();
    for (int i = 0; i < nodeList.size(); ++i)
    {
        QString href = nodeList.at(i).toElement().attribute("href");
        QString text = nodeList.at(i).toElement().text();
        QString num = QString("%1").arg(i + 1);
        qDebug() << m_strBookName << endl << num << text << endl;
        m_mapBook[text] = new CrawlSingleHtml(db, href + message + text + "$" + secondDir + "$" + introduction + "$" + num + "$" + m_strBookName, false);
    }
    qDebug() << m_strBookName << "export finished" << endl;
    QString log = getCurrentTime() + ":  " + m_strBookName + "export finished";
    writeTxtFileByLine(getLogPath(), log);

    QList<QString> list;
    list.append(introduction);
    writeTxtFileByLine(list, m_strBookPath + "/" + "introduction.txt");
}




