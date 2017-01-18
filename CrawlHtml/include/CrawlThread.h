#ifndef CRAWLTHREAD_H
#define CRAWLTHREAD_H

#include <QThread>

class CrawlThread : public QThread
{
    Q_OBJECT
public:
    CrawlThread(QString message);
    ~CrawlThread();

protected:
    void run();

private:
    QString m_strMessage;

};

#endif  //CRAWLTHREAD_H
