#ifndef CRAWLSIGNALEHTML_H
#define CRAWLSIGNALEHTML_H

#include <QObject>
#include "include/CommonFunction.h"
#include "include/DataBaseManager.h"
#include <QSqlQuery>

class CrawlSingleHtml : public QObject
{
	Q_OBJECT
public:
	CrawlSingleHtml();
    CrawlSingleHtml(QString db, QString message, QObject* parent = 0);
	~CrawlSingleHtml();
	void initParam(QString message);
	QString getCrawlContent();
	void exportArticle();
    void writeArticleToTxt(QString path);
	void exportToMysql();
	
public slots:
    void crawlContent();


private:
	QString m_strArticleUrl;
	QString m_strContentRule;
	QString m_strContent;
	QString m_strCurrentHtmlContent;
	QString m_strBookPath;
	QString m_strArticleName;
    QString m_strSecondDir;
    QString m_strIntroduction;
    QString m_strArticleId;
    QString m_strBookName;

    QString db;
    QSqlQuery query;
};

#endif  //CRAWLSIGNALEHTML_H