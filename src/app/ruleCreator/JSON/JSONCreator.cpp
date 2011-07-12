#include "JSONCreator.hpp"
#include <sstream>

JSONCreator::JSONCreator(){
	tableName = "";
    name = "";
    prologCode = "";
}

void JSONCreator::setTableName(QString tableName){
	this->tableName = tableName;
}

void JSONCreator::setName(QString name){
    this->name = name;
}

void JSONCreator::setPrologCode(QString prologCode){
    this->prologCode = prologCode;
}

QString JSONCreator::toJSONString(){
    for(int i=0; i<prologCode.size(); ++i){
        if(prologCode[i] == '\n'){
            prologCode.remove(i, 1);
            prologCode.insert(i+1, "\t\t");
        }
    }

	QString res;

	res.append("{\n");
	res.append("\t\"tableName\": \""); res.append(tableName); res.append("\",\n");
	res.append("\t\"name\": \""); res.append(name); res.append("\",\n");
	res.append("\t\"code\":\n");
	res.append("\t{\n");
	res.append("\t\t\""); res.append(prologCode); res.append("\"\n");
	res.append("\t}\n");
	res.append("}\n");

	return res;
}
