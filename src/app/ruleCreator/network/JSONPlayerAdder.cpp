#include "JSONPlayerAdder.hpp"

JSONPlayerAdder::JSONPlayerAdder(){

}


void JSONPlayerAdder::setTableName(QString tableName){
    this->tableName = tableName;
}

void JSONPlayerAdder::setPlayerName(QString playerName){
    this->playerName = playerName;
}

void JSONPlayerAdder::setDescription(QString description){
    this->description = description;
}

std::string JSONPlayerAdder::toJSONString(){

}
