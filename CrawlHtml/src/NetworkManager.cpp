#include "include/NetworkManager.h"
#include "include/CommonFunction.h"
#include <QTextCodec>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonParseError>

NetworkManager* NetworkManager::_instance = NULL;

NetworkManager::NetworkManager()
{
	m_accessManager = new QNetworkAccessManager(this);
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
		appendLog("NetworkManager get html content error, " + reply->errorString());
	}
	reply->deleteLater();

	return QString();
}

QByteArray NetworkManager::post_message(QString url, QByteArray data)
{
	int contentLength = data.length();
	QEventLoop loop;
	QNetworkRequest req;
	req.setUrl(QUrl(url));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
	req.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);
	QNetworkReply* reply = m_accessManager->post(req, data);
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
	return reply->readAll();
}

QByteArray NetworkManager::get_message(QString url, QString content)
{
	QEventLoop loop;
	url = url + content;
	QNetworkRequest req;
	req.setUrl(QUrl(url));
	QNetworkReply* reply = m_accessManager->get(req);
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));  //QNetworkReply异步
	loop.exec();
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
		this, SLOT(slotError(QNetworkReply::NetworkError)));
	return reply->readAll();
}

int NetworkManager::createBook(QString name, QString intro)
{
    //http://api.huati365.com/api/book/create?api_token=123&name=花木兰&intro=简介内容
	QString con("api_token=");
	con.append(API_TOKEN);
	con.append("&name=");
	con.append(name);
	con.append("&intro=");
	con.append(intro);
	QByteArray reply = get_message(QString("http://api.huati365.com/api/book/create?"), con);
	QString id = getTagMessage(reply, "id");
	appendLog("createBook" + getTagMessage(reply, "msg"));
	return id.toInt();
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

int NetworkManager::crateCatalog(int book_id, int sort_id, QString menu_name)
{
	//http://api.huati365.com/api/book_menu/create?api_token=123&book_id=30&sort=1&menu_name=第二章:序
	QString con("api_token=");
	con.append(API_TOKEN);
	con.append("&book_id=");
	con.append(QString::number(book_id));
	con.append("&sort=");
	con.append(QString::number(sort_id));
	con.append("&menu_name=");
	con.append(menu_name);
	QByteArray reply = get_message(QString("http://api.huati365.com/api/book_menu/create?"), con);
	QString status = getTagMessage(reply, QString("status"));
	return status.toInt();
}

int NetworkManager::createArticle(int book_id, int book_menu_id, QString title, QString content)
{
    //http://api.huati365.com/api/book_article?api_token=123&book_id=30&book_menu_id=1 （book_menu_id可选）
	QString url("http://api.huati365.com/api/book_article?");
	url.append("api_token=");
	url.append(API_TOKEN);
	url.append("&book_id=");
	url.append(QString::number(book_id));
	url.append("&book_menu_id=");
	url.append(QString::number(book_menu_id));

	QByteArray  postData;
	postData.append("title=");
	postData.append(title);
	postData.append("&content=");
	postData.append(content);
	QByteArray reply = post_message(url, postData);
	QString status = getTagMessage(reply, QString("status"));
	return status.toInt();
}

void NetworkManager::slotError(QNetworkReply::NetworkError error)
{
	appendLog("NetworkManager error," + QString::number((int)error));
}

QString NetworkManager::getTagMessage(QByteArray message, QString tag)
{
	QJsonParseError	error;
	QJsonDocument doc = QJsonDocument::fromJson(QString(message).toUtf8(), &error);
	if (error.error == QJsonParseError::NoError) 
	{
		if (doc.isObject()) 
		{
			QVariantMap result = doc.toVariant().toMap();
			QVariantMap nestedMap = result["data"].toMap();
			if (tag == "status")
			{
				return result["status"].toString();
			}
			else
			{
				return nestedMap[tag].toString();
			}
		}
	}
	return QString();
}
