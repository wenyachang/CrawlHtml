#include <QObject>
#include <QRegExp>
#include <QVector>
#include <QMap>
class RegExpManager : public QObject
{
public:
	RegExpManager();
	~RegExpManager();

	static RegExpManager* getInstance();
	void removeNotPairedTags(QString &content);
	void removeContentNotConcerd(QString &content);
	void removeFolderNameNotIncluded(QString &content);
    void replaceFolderNamePunctuate(QString &str);
	void loadRegExp();

	void loadRegExpsNotPairedTags();
	void loadRegExpsNotConcerd();
	void loadRegExpsFolderNameNotIncluded();
	void loadFormats();

private:
	static RegExpManager* _Instance;
	QVector<QRegExp>  m_regExpsNotPairedTags;
	QVector<QRegExp>  m_regExpsNotConcerd;
	QVector<QRegExp>  m_regExpsNotIncluded;
	QMap<QString, QString>  m_mapAdjustFormat;

};

