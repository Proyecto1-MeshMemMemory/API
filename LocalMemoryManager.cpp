/* 
 * File:   LocalMemoryManager.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:42 PM
 */

#include "LocalMemoryManager.h"

LocalMemoryManager::LocalMemoryManager() {

}

LocalMemoryManager::~LocalMemoryManager() {
}

char* LocalMemoryManager::initialize(int pPort, char* pIp) {
    _cliente= new cliente(pPort, pIp);
    _Token=(char*)_cliente->connectToServer();
    _JsonMessageCreator= new JsonCreator();
}

char* LocalMemoryManager::requestNewToken() {
    std::string temp=(char*)_cliente->sendMessageToServer(REQUEST_NEW_TOKEN);
    rapidjson::Document JsonDocument;
    JsonDocument.Parse(temp.c_str());
    if(JsonDocument.IsObject()){
        std::cout<<"error de lectura en Json"<<std::endl;
        return NULL;
    }
    rapidjson::Value & tempValueToken= JsonDocument[TOKEN];
    _Token= (char*)tempValueToken.GetString();
    return _Token;
}

void* LocalMemoryManager::xMalloc(int pSize, int pType) {
    std::string temp= _JsonMessageCreator->createMessage(OPERATION_AL,_Token,
            NULL,pSize,-UNO);
    std::string tempFromServer=(char*)_cliente->sendMessageToServer(temp);
    rapidjson::Document JsonDocument;
    JsonDocument.Parse(tempFromServer.c_str());
    if(JsonDocument.IsObject()){
        rapidjson::Value & respondCheck= JsonDocument[CHECK];
        if(respondCheck.GetInt()==UNO){
            std::cout<<"error de alojamiento de espacio"<<std::endl;
            return NULL;
        }
        rapidjson::Value & respondId= JsonDocument[ID];
        int tempId= respondId.GetInt();
        if(pType==CHAR){
            void* ptrVoidRefe=malloc(sizeof(xReference<char>));
            xReference<char>* tempRefe= new (ptrVoidRefe) xReference<char>();
            return (void*)tempRefe;
        }else if(pType==INT){
            void* ptrVoidRefe=malloc(sizeof(xReference<int>));
            xReference<int>* tempRefe= new (ptrVoidRefe) xReference<int>();
            return (void*)tempRefe;
        }else if(pType==FLOAT){
            void* ptrVoidRefe=malloc(sizeof(xReference<float>));
            xReference<float>* tempRefe= new (ptrVoidRefe) xReference<float>();
            return (void*)tempRefe;
        }else if(pType==DOUBLE){
            void* ptrVoidRefe=malloc(sizeof(xReference<double>));
            xReference<double>* tempRefe= new (ptrVoidRefe) xReference<double>();
            return (void*)tempRefe;
        }
    }
}

void* LocalMemoryManager::xMalloc(int pSize, int pType, void* pValue) {
    std::string temp= _JsonMessageCreator->createMessage(OPERATION_WR,_Token,
            pValue,pSize,-UNO);
    std::string tempFromServer=(char*)_cliente->sendMessageToServer(temp);
    rapidjson::Document JsonDocument;
    JsonDocument.Parse(tempFromServer.c_str());
    if(JsonDocument.IsObject()){
        rapidjson::Value & respondCheck= JsonDocument[CHECK];
        if(respondCheck.GetInt()==UNO){
            std::cout<<"error de guardado de archivo"<<std::endl;
            return NULL;
        }
        rapidjson::Value & respondId= JsonDocument[ID];
        int tempId= respondId.GetInt();
        if(pType==CHAR){
            void* ptrVoidRefe=malloc(sizeof(xReference<char>));
            xReference<char>* tempRefe= new (ptrVoidRefe) xReference<char>();
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==INT){
            void* ptrVoidRefe=malloc(sizeof(xReference<int>));
            xReference<int>* tempRefe= new (ptrVoidRefe) xReference<int>();
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==FLOAT){
            void* ptrVoidRefe=malloc(sizeof(xReference<float>));
            xReference<float>* tempRefe= new (ptrVoidRefe) xReference<float>();
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==DOUBLE){
            void* ptrVoidRefe=malloc(sizeof(xReference<double>));
            xReference<double>* tempRefe= new (ptrVoidRefe) xReference<double>();
            free(pValue);
            return (void*)tempRefe;
        }
    }
    else{
        std::cout<<"error de lectura en Json"<<std::endl;
    }
    return NULL;
}

void LocalMemoryManager::xAssing(void* pRefe, void* pValue, int pType) {
    std::string temp;
    //a la espera de ser terminado
    if(pType==CHAR){
        xReference<char>* xRefePtr= (xReference<char>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue, 
            0,1);
    }else if(pType==INT){
        xReference<int>* xRefePtr= (xReference<int>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue,
            0,1);
    }else if(pType==FLOAT){
        xReference<float>* xRefePtr= (xReference<float>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue, 
            0,1);
    }if(pType==DOUBLE){
        xReference<double>* xRefePtr= (xReference<double>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue,
            0,1);
    }
    temp=_cliente->sendMessageToServer(temp);
    std::cout<<temp<<std::endl;
}

void LocalMemoryManager::xFree(void* pRefe, int pType) {
    std::string temp;
    //a la espera de ser terminado
    if(pType==CHAR){
        xReference<char>* xRefePtr= (xReference<char>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,1);
    }else if(pType==INT){
        xReference<int>* xRefePtr= (xReference<int>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,1);
    }else if(pType==FLOAT){
        xReference<float>* xRefePtr= (xReference<float>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,1);
    }if(pType==DOUBLE){
        xReference<double>* xRefePtr= (xReference<double>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,1);
    }
    temp=_cliente->sendMessageToServer(temp);
    std::cout<<temp<<std::endl;
}
