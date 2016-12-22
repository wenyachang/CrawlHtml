#include "include/HandleMessage.h"
#include "include/CrawlBookHtml.h"
#include "include/CrawlBooksHtml.h"
#include "include/CrawlSingleHtml.h"


HandleMessage* HandleMessage::_Instance = NULL;

HandleMessage::HandleMessage()
{
	
}

HandleMessage::~HandleMessage()
{
	
}

HandleMessage* HandleMessage::getInstance()
{
	if (!_Instance)
	{
		_Instance = new HandleMessage();
	}
	return _Instance;
}

void HandleMessage::setMessage(int exportType, QString message, bool isExportTxt, bool isOutSqlite, bool isRecordRule)
{
	switch (exportType)
	{
	case books_export:
	{
		CrawlBooksHtml* crawlBooks = new CrawlBooksHtml(message);
		break;
	}
	case book_export:
	{

		break;
	}
	case article_export:
	{

		break;
	}
	default:
		break;
	}
}

