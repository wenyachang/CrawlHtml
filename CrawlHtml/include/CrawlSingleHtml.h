#pragma once
#include <QObject>
#include "include/CommonFunction.h"

class CrawlSingleHtml : public QObject
{
	Q_OBJECT
public:
	CrawlSingleHtml();
	CrawlSingleHtml(QString message, QObject* parent = 0);
	~CrawlSingleHtml();
	void initParam(QString message);
	QString getCrawlContent();
	void exportArticle();
	void writeArticleToTxt();
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
};

