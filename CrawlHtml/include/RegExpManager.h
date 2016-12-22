#include <QObject>
#include <QRegExp>
#include <QVector>
class RegExpManager : public QObject
{
public:
	RegExpManager();
	~RegExpManager();

	static RegExpManager* getInstance();
	void removeNotPairedTags(QString &content);
	void removeContentNotConcerd(QString &content);
	void loadRegExp();

	void loadRegExpsNotPairedTags();
	void loadRegExpsNotConcerd();

private:
	static RegExpManager* _Instance;
	QVector<QRegExp>  m_regExpsNotPairedTags;
	QVector<QRegExp>  m_regExpsNotConcerd;

};

