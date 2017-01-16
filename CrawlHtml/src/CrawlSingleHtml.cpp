#include "include/CrawlSingleHtml.h"
#include "include/RequestHtml.h"
#include "include/RegExpManager.h"
#include <QStringList>
#include <QTimer>
#include <QDir>
#include <QSqlError>

CrawlSingleHtml::CrawlSingleHtml(QString db, QString message, QObject* parent)
{
    this->db = db;
    if (!db.isEmpty())
    {
        query = QSqlQuery(QSqlDatabase::database(db));
    }
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
	if (8 == list.size())
	{
		m_strArticleUrl = list.at(0);
		m_strContentRule = list.at(1);
		m_strBookPath = list.at(2);
		m_strArticleName = list.at(3);
        m_strSecondDir = list.at(4);
        m_strIntroduction = list.at(5);
        m_strArticleId = list.at(6);
        m_strBookName = list.at(7);

        RegExpManager::getInstance()->replaceFolderNamePunctuate(m_strSecondDir);
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
			qDebug() << QString::fromLocal8Bit("CrawlSingleHtml: articleƥ�����") << endl;
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
    QDir *rootDir = new QDir;
    QString error = m_strBookPath + "," + m_strSecondDir + "," + m_strArticleName;
    QString log = getCurrentTime() + ":  " + error;
    if (!rootDir->exists(m_strBookPath))
    {
        if (!rootDir->mkdir(m_strBookPath))
        {
            qDebug() << error << "mkdir error:" << m_strBookPath << endl;
            writeTxtFileByLine(getLogPath(), log + "," + m_strBookPath);
        }
    }
    QString path = m_strBookPath +"/"+ m_strSecondDir;
	if (!newDir->exists(path))
	{
		if (newDir->mkdir(path))
		{
			writeArticleToTxt(path);
		}
		else
		{
            qDebug() << error << "mkdir error:" << path << endl;
            writeTxtFileByLine(getLogPath(), log + "," + path);
		}

	}
	else
	{
        writeArticleToTxt(path);
	}
}

void CrawlSingleHtml::writeArticleToTxt(QString path)
{
    QFile file(path + "/" + m_strArticleName + ".txt");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	QTextStream out(&file);
	out << m_strContent;
}

void CrawlSingleHtml::exportToMysql()
{
    QStringList  authorAndName = m_strBookName.split(":");
    m_strContent = m_strContent.trimmed();
    query.prepare("insert into novel_romance(topic, author, introduction, second_dir, article_id, name, content) values (:topic, :author, :introduction, :second_dir, :article_id, :name, :content)");
    query.bindValue(":topic", authorAndName.at(1));
    query.bindValue(":author", authorAndName.at(0));
    query.bindValue(":introduction", m_strIntroduction);
    query.bindValue(":second_dir", m_strSecondDir);
    query.bindValue(":article_id", m_strArticleId.toInt());
    query.bindValue(":name", m_strArticleName);
    query.bindValue(":content", m_strContent);

    
    if (!query.exec())
    {
        QString error = m_strBookName + "," + m_strSecondDir + "," + m_strArticleName + ",";
        qDebug() << error << query.lastError();
        QString lastError = query.lastError().text();
        QString log = getCurrentTime() + ":  " + error + lastError;
        writeTxtFileByLine(getLogPath(), log);
    }
   
}

