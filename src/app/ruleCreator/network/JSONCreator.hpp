#ifndef JSONCREATOR_HPP
#define JSONCREATOR_HPP

#include <QString>

class JSONCreator
{

public:
    JSONCreator();
    void setId(int id);
    void setName(QString name);
    void setPrologCode(QString prologCode);
    std::string toStdString();

private:
    int id;
    QString name;
    QString prologCode;
};

#endif // JSONCREATOR_HPP
