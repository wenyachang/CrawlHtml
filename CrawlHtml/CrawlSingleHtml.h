#pragma once

#include <QObject>
#include <QVector>

class CrawlSingleHtml : public QObject
{
	Q_OBJECT
public:
	CrawlSingleHtml();
	CrawlSingleHtml(QString url, QObject* parent = 0);
	~CrawlSingleHtml();

	void getReplyContent();
	void removeNotConcerned(QString &content);

private:
	QString m_strUrl;
	QString m_strContent;

	QByteArray m_ReplayData;

	QVector<CrawlSingleHtml*>  m_pChildUrls;
};

