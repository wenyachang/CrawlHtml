
#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QString>       
#include <QRegExp>

#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <CrawlSingleHtml.h>
#include <QVariant>
#include "RegExpManager.h"


//网页地址      
const QString URLSTR = "http://wx.cclawnet.com/worldmz/%E3%80%90%E7%BE%8E%E3%80%91%E7%8E%9B%E6%A0%BC%E4%B8%BD%E7%89%B9%C2%B7%E7%B1%B3%E5%88%87%E5%B0%94%EF%BC%9A%E9%A3%98/p001.htm";
//储存网页代码的文件      
const QString FILE_NAME = "code.txt";

class CrawlSingleHtml;
int main(int argc, char *argv[])
{
	
	//QRegExp rx0(QString("charset=\"(.*)\""));
	//rx0.setMinimal(true);
	//int pos = content.indexOf(rx0);
	//QTextCodec * code;
	//QString codeContent;

	//if (pos >= 0)
	//{
	//	code = QTextCodec::codecForName(rx0.cap(1).toStdString().c_str());				
	//	codeContent = code->toUnicode(reply->readAll());
	//	
	//}
	//else
	//{
	//	codeContent = QString::fromLocal8Bit(reply->readAll());
	//}

	//QCoreApplication app(argc, argv);
	//QUrl url(URLSTR);
	//QNetworkAccessManager manager;
	//QEventLoop loop;
	//QNetworkReply *reply;

	//qDebug() << "Reading html code form " << URLSTR;
	//reply = manager.get(QNetworkRequest(url));
	////请求结束并下载完成后，退出子事件循环      
	//QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	////开启子事件循环      
	//loop.exec();

	////获取源码，打开文件  
	//QFile file(FILE_NAME);
	//if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	//{
	//	qDebug() << "Cannot open the file: " << FILE_NAME;
	//	return 0;
	//}
	//QTextStream out(&file);
	//QString codeContent = QString::fromLocal8Bit(reply->readAll());

	//out << codeContent << endl;
	//file.close();

	//QRegExp rx("<(.*)>");
	//QRegExp rx1("\\{(.*)\\}");
	//QRegExp rx2("&nbsp;");
	//QRegExp rx3("body");
	//rx.setMinimal(true);
	//rx1.setMinimal(true);
	//rx2.setMinimal(true);
	//rx3.setMinimal(true);

	//codeContent.remove(rx);
	//codeContent.remove(rx1);
	//codeContent.remove(rx2);
	//codeContent.remove(rx3);
	//codeContent.remove(" ");
	//codeContent.trimmed();
	//QFile file1("result.txt");
	//if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))
	//{
	//	return 0;
	//}
	//QTextStream oue(&file1);
	//oue << codeContent << endl;
	//file1.close();

	QApplication app(argc, argv);
	qmlRegisterType<CrawlSingleHtml>("com.crawl", 1, 0, "CrawlSingleHtml");

	QQuickView viewer;
	viewer.setSource(QUrl(QStringLiteral("qml/main.qml")));
	viewer.show();

	RegExpManager::getInstance()->loadRegExp();
	CrawlSingleHtml* html = new CrawlSingleHtml(URLSTR);

	return app.exec();
}
