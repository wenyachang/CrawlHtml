#ifndef CRAWLBOOKSHTML_H
#define CRAWLBOOKSHTML_H

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
	
	QList<QString> exportedBooks;
};

#endif  //CRAWLBOOKSHTML_H