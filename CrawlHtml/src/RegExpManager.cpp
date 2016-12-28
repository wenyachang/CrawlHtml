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
	loadRegExpsFolderNameNotIncluded();
}

void RegExpManager::loadRegExpsNotPairedTags()
{
	
	QRegExp rx1("<font(.*)>");
	QRegExp rx2("<img(.*)>");
	QRegExp rx3("<li(.*)>");
	QRegExp rx4("</li(.*)>");
	QRegExp rx5("<div(.*)>");
	QRegExp rx6("</div(.*)>");
	QRegExp rx7("<h1(.*)>");
	QRegExp rx8("</h1(.*)>");
	QRegExp rx9("<h2(.*)>");
	QRegExp rx10("</h2(.*)>");
	QRegExp rx11("<h3(.*)>");
	QRegExp rx12("</h3(.*)>");
	QRegExp rx13("<h4(.*)>");
	QRegExp rx14("</h4(.*)>");
	QRegExp rx15("<h5(.*)>");
	QRegExp rx16("</h5(.*)>");
	QRegExp rx17("<h6(.*)>");
	QRegExp rx18("</h6(.*)>");
	QRegExp rx19("&nbsp;");			 
	QRegExp rx20("&mdash;");
	QRegExp rx21("&middot;"); 		 
	QRegExp rx22("&ldquo;");
	QRegExp rx23("&rdquo;");
	QRegExp rx24("\((.*)\)");
	QRegExp rx25("£¨(.*)£©");
	QRegExp rx26("<p>(.*)</p>");


	rx1.setMinimal(true);
	rx2.setMinimal(true);
	rx3.setMinimal(true);
	rx4.setMinimal(true);
	rx5.setMinimal(true);
	rx6.setMinimal(true);
	rx7.setMinimal(true);
	rx8.setMinimal(true);
	rx9.setMinimal(true);
	rx10.setMinimal(true);
	rx11.setMinimal(true);
	rx12.setMinimal(true);
	rx13.setMinimal(true);
	rx14.setMinimal(true);
	rx15.setMinimal(true);
	rx16.setMinimal(true);
	rx17.setMinimal(true);
	rx18.setMinimal(true);
	rx19.setMinimal(true);
	rx20.setMinimal(true);
	rx21.setMinimal(true);
	rx22.setMinimal(true);
	rx23.setMinimal(true);
	rx24.setMinimal(true);
	rx25.setMinimal(true);
	rx26.setMinimal(true);

	
	m_regExpsNotPairedTags.append(rx1);
	m_regExpsNotPairedTags.append(rx2);
	m_regExpsNotPairedTags.append(rx3);
	m_regExpsNotPairedTags.append(rx4);
	m_regExpsNotPairedTags.append(rx5);
	m_regExpsNotPairedTags.append(rx6);
	m_regExpsNotPairedTags.append(rx7);
	m_regExpsNotPairedTags.append(rx8);
	m_regExpsNotPairedTags.append(rx9);
	m_regExpsNotPairedTags.append(rx10);
	m_regExpsNotPairedTags.append(rx11);
	m_regExpsNotPairedTags.append(rx12);
	m_regExpsNotPairedTags.append(rx13);
	m_regExpsNotPairedTags.append(rx14);
	m_regExpsNotPairedTags.append(rx15);
	m_regExpsNotPairedTags.append(rx16);
	m_regExpsNotPairedTags.append(rx17);
	m_regExpsNotPairedTags.append(rx18);
	m_regExpsNotPairedTags.append(rx19);
	m_regExpsNotPairedTags.append(rx20);
	m_regExpsNotPairedTags.append(rx21);
	m_regExpsNotPairedTags.append(rx22);
	m_regExpsNotPairedTags.append(rx23);
	//m_regExpsNotPairedTags.append(rx24);
	//m_regExpsNotPairedTags.append(rx25);
	//m_regExpsNotPairedTags.append(rx26);

}

void RegExpManager::loadRegExpsNotConcerd()
{
	
	QRegExp rx("<style>(.*)</style>");
	QRegExp rx1("<div(.*)>");
	QRegExp rx2("</div>");

	rx.setMinimal(true);
	rx1.setMinimal(true);
	rx2.setMinimal(true);

	m_regExpsNotConcerd.append(rx);
	m_regExpsNotConcerd.append(rx1);
	m_regExpsNotConcerd.append(rx2);
}

void RegExpManager::loadFormats()
{
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&ldquo;"] = "\"";
	m_mapAdjustFormat["&rdquo;"] = " \"";
	m_mapAdjustFormat["&hellip;"] = "...";
	m_mapAdjustFormat["&prime;"] = "'";
	m_mapAdjustFormat["&oline;"] = "-";
	m_mapAdjustFormat["&frasl;"] = "/";
	m_mapAdjustFormat["&quot;"] = "\"";
	m_mapAdjustFormat["&amp;"] = "&";
	m_mapAdjustFormat["&it;"] = "<";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
	m_mapAdjustFormat["&nbsp;"] = " ";
}

void RegExpManager::loadRegExpsFolderNameNotIncluded()
{
	QRegExp rx1("\\");
	QRegExp rx2("\/");
	QRegExp rx3(":");
	QRegExp rx4("\*");
	QRegExp rx5("\?");
	QRegExp rx6("\"");
	QRegExp rx7("|");
	QRegExp rx8("<");
	QRegExp rx9(">");

	rx1.setMinimal(true);
	rx2.setMinimal(true);
	rx3.setMinimal(true);
	rx4.setMinimal(true);
	rx5.setMinimal(true);
	rx6.setMinimal(true);
	rx7.setMinimal(true);
	rx8.setMinimal(true);
	rx9.setMinimal(true);

	m_regExpsNotIncluded.append(rx1);
	m_regExpsNotIncluded.append(rx2);
	m_regExpsNotIncluded.append(rx3);
	m_regExpsNotIncluded.append(rx4);
	m_regExpsNotIncluded.append(rx5);
	m_regExpsNotIncluded.append(rx6);
	m_regExpsNotIncluded.append(rx7);
	m_regExpsNotIncluded.append(rx8);
	m_regExpsNotIncluded.append(rx9);
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

void RegExpManager::removeFolderNameNotIncluded(QString &content)
{
	for (int i = 0; i < m_regExpsNotIncluded.size(); ++i)
	{
		content.remove(m_regExpsNotIncluded.at(i));
	}
}






