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
	QRegExp rx("<(.*)>");
	QRegExp rx1("\\{(.*)\\}");
	QRegExp rx2("&nbsp;");
	QRegExp rx3("body");
	rx.setMinimal(true);
	rx1.setMinimal(true);
	rx2.setMinimal(true);
	rx3.setMinimal(true);

	m_regExps.append(rx);
	m_regExps.append(rx1);
	m_regExps.append(rx2);
	m_regExps.append(rx3);
}

QVector<QRegExp> RegExpManager::getRegExps()
{
	return m_regExps;
}
