#include "include/NetworkManager.h"
#include "include/CommonFunction.h"
#include <QTextCodec>

NetworkManager* NetworkManager::_instance = NULL;

NetworkManager::NetworkManager()
{
}

NetworkManager::NetworkManager(QString url)
{

}


NetworkManager::~NetworkManager()
{
}

NetworkManager* NetworkManager::getInstance()
{
    if (!_instance)
    {
        return new NetworkManager();
    }
    return _instance;
}

QString NetworkManager::getHtmlContent(QString html)
{
	QUrl url(html);
	QEventLoop loop;
	QNetworkReply *reply;

	reply = m_accessManager->get(QNetworkRequest(url));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QTextCodec* code = QTextCodec::codecForName("utf-8");
		return code->toUnicode(reply->readAll());
		//return QString::fromLocal8Bit(reply->readAll());
	}
	else
	{
		QString log = getCurrentTime() + ":  NetworkManager get html content error, " + reply->errorString();
		writeTxtFileByLine(getLogPath(), log);
	}
	reply->deleteLater();

	return QString();
}

void NetworkManager::post_message(QString url, QByteArray data)
{
	int contentLength = data.length();
	QNetworkRequest req;
	req.setUrl(QUrl(url));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	req.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);
	QNetworkReply* reply = m_accessManager->post(req, data);
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void NetworkManager::get_message(QString url ,QString content)
{
	url = url + content;
	QNetworkRequest req;
	req.setUrl(QUrl(url));
	QNetworkReply* reply = m_accessManager->get(req);
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void NetworkManager::createBook(QString name, QString intro)
{
    //http://api.huati365.com/api/book/create?api_token=123&name=花木兰&intro=简介内容
	QString con("api_token=");
	con.append(API_TOKEN);
	con.append("&name=");
	con.append(name);
	con.append("&intro=");
	con.append(intro);
	get_message(QString("http://api.huati365.com/api/book/create?"), con);
}

void NetworkManager::updateBook(int book_id)
{
    //http://api.huati365.com/api/book?api_token=123&book_id=32
	QByteArray  postData;
	postData.append("api_token=");
	postData.append(API_TOKEN);
	postData.append("&book_id=");
	postData.append(QString::number(book_id));

	post_message("http://api.huati365.com/api/book", postData);
}

void NetworkManager::crateCatalog(int book_id, int sort_id, QString menu_name)
{
	//http://api.huati365.com/api/book_menu/create?api_token=123&book_id=30&sort=1&menu_name=第二章:序
	QString con("api_token=");
	con.append(API_TOKEN);
	con.append("book_id=");
	con.append(QString::number(book_id));
	con.append("&sort=");
	con.append(QString::number(sort_id));
	con.append("&menu_name=");
	con.append(menu_name);
	get_message("http://api.huati365.com/api/book_menu/create?", con);
}

void NetworkManager::createArticle(int book_id, int book_menu_id)
{
    //http://api.huati365.com/api/book_article?api_token=123&book_id=30&book_menu_id=1 （book_menu_id可选）
	QByteArray  postData;
	postData.append("api_token=");
	postData.append(API_TOKEN);
	postData.append("&book_id=");
	postData.append(QString::number(book_id));
	postData.append("&book_menu_id=");
	postData.append(QString::number(book_menu_id));
	post_message("http://api.huati365.com/api/book_article", postData);
}

void NetworkManager::slotError(QNetworkReply::NetworkError error)
{
	QString log = getCurrentTime() + ": NetworkManager error," + QString::number((int)error);
	writeTxtFileByLine(getLogPath(), log);
}
