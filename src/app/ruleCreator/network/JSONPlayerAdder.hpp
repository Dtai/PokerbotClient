#ifndef JSONPLAYERADDER_HPP
#define JSONPLAYERADDER_HPP

#include <QString>

class JSONPlayerAdder
{

public:
    JSONPlayerAdder();
    void setPlayerName(QString playerName);
    void setTableName(QString tableName);
    void setDescription(QString description);
    std::string toJSONString();

private:
    QString playerName;
    QString tableName;
    QString description;
};

#endif // JSONPLAYERADDER_HPP
