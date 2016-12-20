#include "include/RequestHtml.h"

RequestHtml* RequestHtml::_instance = NULL;

RequestHtml::RequestHtml()
{
}

RequestHtml::RequestHtml(QString url)
{

}


RequestHtml::~RequestHtml()
{
}

RequestHtml* RequestHtml::instance()
{
    if (_instance)
    {
        return new RequestHtml();
    }
    return _instance;
}

QString RequestHtml::getHtmlContent(QString url)
{
	return QString();
}
