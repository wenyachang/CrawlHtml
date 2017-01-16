#pragma once

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

