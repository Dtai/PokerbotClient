#ifndef JSONCREATOR_HPP
#define JSONCREATOR_HPP

#include <QString>

class JSONCreator
{

public:
	JSONCreator();
	void setTableName(QString tableName);
    void setName(QString name);
    void setPrologCode(QString prologCode);
	QString toJSONString();

private:
	QString tableName;
    QString name;
    QString prologCode;
};

#endif // JSONCREATOR_HPP
