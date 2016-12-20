#include <QObject>
#include <QRegExp>
#include <QVector>
class RegExpManager : public QObject
{
public:
	RegExpManager();
	~RegExpManager();

	static RegExpManager* getInstance();
	QVector<QRegExp> getRegExps();

	void loadRegExp();

private:
	static RegExpManager* _Instance;
	QVector<QRegExp>  m_regExps;

};

