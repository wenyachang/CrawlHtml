
#ifndef COMMON_H
#define COMMON_H

#include<QApplication>
#include<QTime>

void sleep(unsigned int msec);
QList<QString> readTxtFileByLine(QString fileName);
void writeTxtFileByLine(QList<QString> list, QString fileName);

#endif	 //	COMMON_H