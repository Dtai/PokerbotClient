#ifndef JSONTABLECREATOR_HPP
#define JSONTABLECREATOR_HPP

#include <QString>

class JSONTableCreator
{

public:
    JSONTableCreator();
    void setTableName(QString tableName);
    void setNumberOfPlayers(int numberOfPlayers);
    std::string toJSONString();

private:
    QString tableName;
    int numberOfPlayers;
};

#endif // JSONTABLECREATOR_HPP
