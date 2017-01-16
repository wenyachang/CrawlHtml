#pragma once

#include <QObject>
#include <QVector>
#include <QMap>
#include "include/CrawlBookHtml.h"

class CrawlBooksHtml : public QObject
{
	Q_OBJECT
public:
	CrawlBooksHtml();
	CrawlBooksHtml(QString message, QObject* parent = 0);
	~CrawlBooksHtml();
	void initParam(QString message);
	void splitBooksHrefs(QString hrefs);
	void exportOneBook(QString bookName);
	void exportToTxt();
	bool isBookExported(QString bookName);
	
public slots:
    void crawlBookHref();
    

private:
	QString m_strBooksUrl;
	QString m_strBooksRule;
	QString m_strBookRule;
	QString m_strBookNameRule;
	QString m_strAuthorRule;
	QString m_strContentRule;

	QString m_strBookPath;
	QString m_strConfigPath;

	QString m_strCurrentHtmlContent;
	
	QMap<QString, CrawlBookHtml*> m_mapBooks;
	QList<QString> exportedBooks;
};

