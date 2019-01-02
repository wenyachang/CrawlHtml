
#ifndef COMMON_H
#define COMMON_H

#include<QApplication>
#include<QTime>

void sleep(unsigned int msec);
QList<QString> readTxtFileByLine(QString fileName);

QString readTxtFile(QString fileName);

void appendLog(QString logMessage);
void writeTxtFileByLine(QList<QString> list, QString fileName);
void writeTxtFileByLine(QString path, QString str);
QString getLogPath();
QString getCurrentTime();

#endif	 //	COMMON_H