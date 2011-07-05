#include "JSONCreator.hpp"
#include <sstream>

JSONCreator::JSONCreator(){
    id = 0;
    name = "";
    prologCode = "";
}

void JSONCreator::setId(int id){
    this->id = id;
}

void JSONCreator::setName(QString name){
    this->name = name;
}

void JSONCreator::setPrologCode(QString prologCode){
    this->prologCode = prologCode;
}

std::string JSONCreator::toStdString(){
    for(int i=0; i<prologCode.size(); ++i){
        if(prologCode[i] == '\n'){
            prologCode.remove(i, 1);
            prologCode.insert(i+1, "\t\t");
        }
    }

    std::stringstream ss(std::stringstream::in | std::stringstream::out);
    ss << "{" << std::endl;
    ss << "\t\"id\": " << id << "," << std::endl;
    ss << "\t\"name\": \"" << name.toStdString() << "\"," << std::endl;
    ss << "\t\"code\":" << std::endl;
    ss << "\t{" << std::endl;
    ss << "\t\t\"" << prologCode.toStdString() << "\"" << std::endl;
    ss << "\t}" << std::endl;
    ss << "}" << std::endl;

    return ss.str();
}
