
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
		list.append(QString::fromLocal8Bit(line));
	}
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
		out << list.at(i) << "\n";
	}
}

#endif	 //	COMMON_H