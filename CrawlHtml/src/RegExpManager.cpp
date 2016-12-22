#include "include/RegExpManager.h"


RegExpManager* RegExpManager::_Instance = NULL;

RegExpManager::RegExpManager()
{
	loadRegExp();
}


RegExpManager::~RegExpManager()
{
}

RegExpManager* RegExpManager::getInstance()
{
	if (!_Instance)
	{
		_Instance = new RegExpManager();
	}
	return _Instance;
}

void RegExpManager::loadRegExp()
{
	loadRegExpsNotPairedTags();
	loadRegExpsNotConcerd();
}

void RegExpManager::loadRegExpsNotPairedTags()
{
	
	QRegExp rx1("<font(.*)>");
	QRegExp rx2("<img(.*)>");
	QRegExp rx3("<li>");
	QRegExp rx4("</li>");
	
	rx1.setMinimal(true);
	rx2.setMinimal(true);
	rx3.setMinimal(true);
	rx4.setMinimal(true);

	
	m_regExpsNotPairedTags.append(rx1);
	m_regExpsNotPairedTags.append(rx2);
	m_regExpsNotPairedTags.append(rx3);
	m_regExpsNotPairedTags.append(rx4);

}

void RegExpManager::loadRegExpsNotConcerd()
{
	QRegExp rx("<(.*)>");
	QRegExp rx1("\\{(.*)\\}");
	QRegExp rx2("&nbsp;");
	QRegExp rx3("body");

	rx.setMinimal(true);
	rx1.setMinimal(true);
	rx2.setMinimal(true);
	rx3.setMinimal(true);

	m_regExpsNotConcerd.append(rx);
	/*m_regExpsNotConcerd.append(rx1);
	m_regExpsNotConcerd.append(rx2);
	m_regExpsNotConcerd.append(rx3);*/
}

void RegExpManager::removeNotPairedTags(QString &content)
{
	for (int i = 0; i < m_regExpsNotPairedTags.size(); ++i)
	{
		content.remove(m_regExpsNotPairedTags.at(i));
	}
}

void RegExpManager::removeContentNotConcerd(QString &content)
{
	for (int i = 0; i < m_regExpsNotConcerd.size(); ++i)
	{
		content.remove(m_regExpsNotConcerd.at(i));
	}
}




