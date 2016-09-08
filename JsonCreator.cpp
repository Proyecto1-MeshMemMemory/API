/* 
 * File:   JsonCreator.cpp
 * Author: ellioth
 * 
 * Created on September 7, 2016, 11:31 PM
 */

#include "JsonCreator.h"

JsonCreator::JsonCreator() {
}

JsonCreator::~JsonCreator() {
}

string JsonCreator::createMessage(int pOperation, string pToken, void* pMessage,
        int pLenght,  int pId) {
    rapidjson::StringBuffer JsonToWrite;
    rapidjson::Writer<rapidjson::StringBuffer> writer(JsonToWrite);
    writer.StartObject();
    //establecemos la operacion que queremos realizar
    writer.String(OPERATION);
    writer.Int(pOperation);
    //establecemos el token que se nos dio, 
    writer.String(TOKEN);
    writer.String(pToken.c_str());
    if(pMessage!=NULL){
        //establecemos el mensaje que queremos enviar
        writer.String(MESSAGE);
        writer.String((const char*)pMessage, pLenght, 0);
    }
    else if(pId>-UNO){
        //establecemos el id que queremos pedir.
        writer.String(ID);
        writer.String(to_string(pId).c_str());
    }
    
    //cerramos el objeto
    writer.EndObject();
    return JsonToWrite.GetString();
}

