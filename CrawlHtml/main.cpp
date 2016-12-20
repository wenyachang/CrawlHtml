
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
#include "CrawlSingleHtml.h"
#include <QVariant>
#include <QDeclarativeView>
#include "RegExpManager.h"


//ÍøÒ³µØÖ·      
const QString URLSTR = "http://t.icesmall.cn/bookDir/53/819/0.html";
//´¢´æÍøÒ³´úÂëµÄÎÄ¼þ      
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

	QApplication app(argc, argv);
	qmlRegisterType<CrawlSingleHtml>("com.crawl", 1, 0, "CrawlSingleHtml");

	QQuickView viewer;
	viewer.setSource(QUrl(QStringLiteral("qml/main.qml")));
	
	viewer.rootContext()->setContextProperty("mainwindow", &viewer);
	viewer.resize(700, 600);
	//viewer.setOpacity(0.8);
	viewer.show();
	viewer.setFlags(Qt::FramelessWindowHint);
	QObject::connect((QObject*)viewer.engine(), SIGNAL(quit()), &app, SLOT(quit()));

	RegExpManager::getInstance()->loadRegExp();
	CrawlSingleHtml* html = new CrawlSingleHtml(URLSTR);

	return app.exec();
}
