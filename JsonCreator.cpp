/* 
 * File:   JsonCreator.cpp
 * Author: ellioth
 * 
 * Created on September 8, 2016, 6:38 AM
 */

#include "JsonCreator.h"

/**
 * constructor de la clase.
 */
JsonCreator::JsonCreator() {
}

/**
 * destructo de la clase
 */
JsonCreator::~JsonCreator() {
}

/**
 * metodo para crear el mensaje segun los parametros que se pasen.
 * @param pOperation entero de la operacion que queremos realizar.
 * @param pToken char* del token que estamos usando.
 * @param pMessage void* del mensaje que queremos envar a guardar.
 * @param pLenght entero del largo del mensaje que vamos a enviar-
 * @param pId entero del id del vamos a extrañr el daor
 * @return returna el mensaje ya creado.
 */
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
    if(pLenght>CERO){
        //establecemos el espacio que va a ocupar el mensaje
        writer.String(SIZE);
        writer.String(to_string(pLenght).c_str());
    }
    if(pId>-UNO){
        //establecemos el id que queremos pedir.
        writer.String(ID);
        writer.String(to_string(pId).c_str());
    }
    
    //cerramos el objeto
    writer.EndObject();
    return JsonToWrite.GetString();
}



