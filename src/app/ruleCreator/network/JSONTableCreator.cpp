#include "JSONTableCreator.hpp"

JSONTableCreator::JSONTableCreator(){

}

void JSONTableCreator::setTableName(QString tableName){
    this->tableName = tableName;
}

void JSONTableCreator::setNumberOfPlayers(int numberOfPlayers){
    this->numberOfPlayers = numberOfPlayers;
}

std::string JSONTableCreator::toJSONString(){

}
