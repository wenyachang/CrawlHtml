#pragma once

#include <QObject>
#include <QMap>
#include"include/CrawlSingleHtml.h"

class CrawlBookHtml : public QObject
{
	Q_OBJECT
public:
	CrawlBookHtml();
	CrawlBookHtml(QString message, QObject* parent = 0);
	~CrawlBookHtml();
	void initParam(QString message);
	
	void splitBookCatalogHrefs(QString catalog);
	QMap<QString, CrawlSingleHtml*> getBookMap();

public slots:
    void crawlBookCatalog();


private:
	QString m_strBookUrl;
	QString m_strBookRule;
	QString m_strBookNameRule;
	QString m_strAuthorRule;
	QString m_strContentRule;
	QString m_strBookPath;


	QString m_strCurrentHtmlContent;
	QMap<QString, CrawlSingleHtml*> m_mapBook;
};

