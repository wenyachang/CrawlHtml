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
		sleep(5000);
	}
	//sleep(5000);
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
				qDebug() << QString::fromLocal8Bit("CrawlBookHtml: ��������Ϊ�գ�");
				appendLog(QString::fromLocal8Bit("CrawlBookHtml: ��������Ϊ�գ�"));
				return;
			}
			splitBookCatalogHrefs3(rx.cap(0));
		}
		else
		{
			qDebug() << QString::fromLocal8Bit("CrawlBookHtml: bookƥ�����") << endl;
			appendLog(QString::fromLocal8Bit("CrawlBookHtml: bookƥ�����"));

		}
	}
}

QMap<QString, CrawlSingleHtml*> CrawlBookHtml::getBookMap()
{
	return m_mapBook;
}

void CrawlBookHtml::splitBookCatalogHrefs3(QString catalog)
{
    catalog = "<p>" + catalog + "</p>";
    
    QRegExp te("<h3(.*)</h3>");
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

	if (!m_strBookName.isEmpty())
	{
		//m_strBookId = QString::number(NetworkManager::getInstance()->createBook(m_strBookName, introduction));
		//NetworkManager::getInstance()->updateBook(m_strBookName.toInt());
	}

    if (list1.size() == list2.size() + 1)
    {
        for (int i = 0; i < list2.size(); ++i)
        {
			/*int re = NetworkManager::getInstance()->crateCatalog(m_strBookId.toInt(), i + 1, list2.at(i));
			if (re != 0)
			{
				appendLog(QString("�鼮%1����Ŀ¼(%2)ʧ�ܡ�").arg(m_strBookId).arg(list2.at(i)));
			}*/
            splitWithSecondaryDirectory(introduction, list2.at(i), i+1, list1.at(i + 1));
        }
    }
    
}

void CrawlBookHtml::splitWithSecondaryDirectory(QString introduction, QString secondDir, int secondDirId, QString hrefs)
{
    RegExpManager::getInstance()->removeNotPairedTags(hrefs);
    hrefs = "<p>" + hrefs + "</p>";

    QDomDocument doc;
    QString error;
    if (!doc.setContent(hrefs, false, &error))
    {
        qDebug() << QString::fromLocal8Bit("CrawlBookHtml: htmlתxml����") << endl;
		appendLog(QString::fromLocal8Bit("CrawlBookHtml: htmlתxml����"));
        return;
    }
    QDomElement root = doc.documentElement();
    QDomNodeList nodeList = root.elementsByTagName("a");
    if (nodeList.isEmpty())
    {
        qDebug() << QString::fromLocal8Bit("CrawlBookHtml: ��book���ӡ�") << endl;
		appendLog(QString::fromLocal8Bit("CrawlBookHtml: ��book���ӡ�"));
        return;
    }
	
	appendLog(m_strBookName + QString::fromLocal8Bit("CrawlBookHtml: bookĿ¼������Ŀ��") + QString::number(nodeList.size()));

    QString message = "$" + m_strContentRule + "$" + m_strBookPath + "$";
    QString db = DataBaseManager::getInstance()->connectDataBase();
    for (int i = 0; i < nodeList.size(); ++i)
    {
        QString href = nodeList.at(i).toElement().attribute("href");
        QString text = nodeList.at(i).toElement().text();
        QString num = QString("%1").arg(i + 1);
        qDebug() << m_strBookName << endl << num << text << endl;
		appendLog(m_strBookName + num);
		CrawlSingleHtml* single = new CrawlSingleHtml(db, href + message + text + "$" + secondDir + "$" + introduction + "$" + num + "$" + m_strBookName + "$" + QString::number(secondDirId) + "$" + m_strBookId, false);
		delete single;
	}
    qDebug() << m_strBookName << "export finished" << endl;
	appendLog(m_strBookName + "export finished");

    QList<QString> list;
    list.append(introduction);
    writeTxtFileByLine(list, m_strBookPath + "/" + "introduction.txt");
}




