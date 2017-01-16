#include "include/CrawlThread.h"
#include "include/CrawlBookHtml.h"
#include <QDebug>

CrawlThread::CrawlThread(QString message) : QThread()
{
    m_strMessage = message;
}

CrawlThread::~CrawlThread()
{

}

void CrawlThread::run()
{
    CrawlBookHtml* book = new CrawlBookHtml(m_strMessage, false);
}
