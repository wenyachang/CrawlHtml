
#ifndef COMMON_H
#define COMMON_H

#include<QApplication>
#include<QTime>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <qDebug>

void sleep(unsigned int msec)
{
	QTime reachTime = QTime::currentTime().addMSecs(msec);

	while (QTime::currentTime() < reachTime)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

QList<QString> readTxtFileByLine(QString fileName)
{
	QList<QString>  list;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qDebug() << "打开TXT文件失败！" << endl;
	}

	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
        if (!(line.size() < 3))
        {
            list.append(QString::fromLocal8Bit(line));
        }
	}
    //file.close();
	return list;
}

void writeTxtFileByLine(QList<QString> list, QString fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream out(&file);
	for (int i = 0; i < list.size(); ++i)
	{
        if (!list.at(i).isEmpty())
        {
            out << list.at(i) << "\r\n";
        }
		
	}
    //file.close();
}

void writeTxtFileByLine(QString path, QString str)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        return;
    }

    QTextStream out(&file);
	out << "\r\n" << str;
}

QString getLogPath()
{
    return QCoreApplication::applicationDirPath() + "log/log.txt";
}

QString getCurrentTime()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    return current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}

#endif	 //	COMMON_H