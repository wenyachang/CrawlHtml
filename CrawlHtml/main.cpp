
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
#include "include/HandleMessage.h"
#include <QVariant>
#include <QDeclarativeView>
#include "include/RegExpManager.h"
#include <include/DataBaseManager.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	qmlRegisterType<HandleMessage>("com.crawl", 1, 0, "HandleMessage");

	QQuickView viewer;
	viewer.setSource(QUrl(QStringLiteral("qml/main.qml")));
	
	viewer.rootContext()->setContextProperty("mainwindow", &viewer);
	viewer.resize(700, 600);
	
	viewer.show();
	viewer.setFlags(Qt::FramelessWindowHint);
	QObject::connect((QObject*)viewer.engine(), SIGNAL(quit()), &app, SLOT(quit()));

	RegExpManager::getInstance()->loadRegExp();

	return app.exec();
}
