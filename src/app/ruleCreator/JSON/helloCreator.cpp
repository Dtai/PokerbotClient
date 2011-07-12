#include "helloCreator.hpp"

HelloCreator::HelloCreator(){

}

void HelloCreator::setPlayerName(QString playerName){
	this->playerName = playerName;
}

void HelloCreator::setTableName(QString tableName){
	this->tableName = tableName;
}

QString HelloCreator::toJSONString(){
	QString json;
	json.append("{\n");
	json.append("\t\"Type\":\"Hello\",\n");
	json.append("\t\"TableName\":\""); json.append(tableName); json.append("\",\n");
	json.append("\t\"PlayerName\":\""); json.append(playerName); json.append("\"\n");
	json.append("}");

	return json;
}
