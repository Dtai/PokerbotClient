#ifndef HELLOCREATOR_HPP
#define HELLOCREATOR_HPP

#include <QString>

class HelloCreator
{

public:
	HelloCreator();
	void setTableName(QString tableName);
	void setPlayerName(QString playerName);
	QString toJSONString();

private:
	QString tableName;
	QString playerName;
};

#endif // HELLOCREATOR_HPP
