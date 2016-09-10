/* 
 * File:   LocalMemoryManager.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:42 PM
 */

#include "LocalMemoryManager.h"
#include "xReference.h"

LocalMemoryManager::LocalMemoryManager() {
    _Token=NULL;
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
        /*-----creacion del puntero del xReference-----*/
        if(pType==CHAR){
            void* ptrVoidRefe=malloc(sizeof(xReference<char>));
            //se usa 'placemente new' para usar constructor del puntero 
            //y asignarlos en un espacio especifico
            xReference<char>* tempRefe= new (ptrVoidRefe)xReference<char>(
                tempId, pSize,CHAR, this);
            //se retorna el puntero como un void* asi como se hace con un malloc
            return (void*)tempRefe;
        }else if(pType==INT){
            void* ptrVoidRefe=malloc(sizeof(xReference<int>));
            xReference<int>* tempRefe= new (ptrVoidRefe) xReference<int>(
                tempId, pSize,INT, this);
            return (void*)tempRefe;
        }else if(pType==FLOAT){
            void* ptrVoidRefe=malloc(sizeof(xReference<float>));
            xReference<float>* tempRefe= new (ptrVoidRefe) xReference<float>(
                tempId, pSize,FLOAT, this);
            return (void*)tempRefe;
        }else if(pType==DOUBLE){
            void* ptrVoidRefe=malloc(sizeof(xReference<double>));
            xReference<double>* tempRefe= new (ptrVoidRefe) xReference<double>(
                tempId, pSize,DOUBLE, this);
            return (void*)tempRefe;
        }else if(pType==LONG){
            void* ptrVoidRefe=malloc(sizeof(xReference<long>));
            xReference<long>* tempRefe= new (ptrVoidRefe) xReference<long>(
                tempId, pSize,LONG, this);
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
            xReference<char>* tempRefe= new (ptrVoidRefe) xReference<char>(
                tempId, pSize,CHAR, this);
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==INT){
            void* ptrVoidRefe=malloc(sizeof(xReference<int>));
            xReference<int>* tempRefe= new (ptrVoidRefe) xReference<int>(
                tempId, pSize,INT, this);
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==FLOAT){
            void* ptrVoidRefe=malloc(sizeof(xReference<float>));
            xReference<float>* tempRefe= new (ptrVoidRefe) xReference<float>(
                tempId, pSize,FLOAT,this);
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==DOUBLE){
            void* ptrVoidRefe=malloc(sizeof(xReference<double>));
            xReference<double>* tempRefe= new (ptrVoidRefe) xReference<double>(
                tempId, pSize,DOUBLE,this);
            free(pValue);
            return (void*)tempRefe;
        }else if(pType==LONG){
            void* ptrVoidRefe=malloc(sizeof(xReference<long>));
            xReference<long>* tempRefe= new (ptrVoidRefe) xReference<long>(
                tempId, pSize,LONG, this);
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
            xRefePtr->getSize(),xRefePtr->getID());
    }else if(pType==INT){
        xReference<int>* xRefePtr= (xReference<int>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue,
            xRefePtr->getSize(),xRefePtr->getID());
    }else if(pType==FLOAT){
        xReference<float>* xRefePtr= (xReference<float>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue, 
            xRefePtr->getSize(),xRefePtr->getID());
    }if(pType==DOUBLE){
        xReference<double>* xRefePtr= (xReference<double>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue,
            xRefePtr->getSize(),xRefePtr->getID());
    }
    temp=(char*)_cliente->sendMessageToServer(temp);
    std::cout<<temp<<std::endl;
}

void LocalMemoryManager::xFree(void* pRefe, int pType) {
    std::string temp;
    //a la espera de ser terminado
    if(pType==CHAR){
        xReference<char>* xRefePtr= (xReference<char>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,
                xRefePtr->getID());
    }else if(pType==INT){
        xReference<int>* xRefePtr= (xReference<int>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,
                xRefePtr->getID());
    }else if(pType==FLOAT){
        xReference<float>* xRefePtr= (xReference<float>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,
                xRefePtr->getID());
    }if(pType==DOUBLE){
        xReference<double>* xRefePtr= (xReference<double>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 0,
                xRefePtr->getID());
    }
    temp=(char*)_cliente->sendMessageToServer(temp);
    std::cout<<temp<<std::endl;
}

void* LocalMemoryManager::changeReferenceCounter(int pID, int pOp) {
    string temp=_JsonMessageCreator->createMessage(pOp, _Token, NULL, 
            CERO, pID);
    string newTemp=(char*)_cliente->sendMessageToServer(temp);
    rapidjson::Document tempJsonRecived;
    tempJsonRecived.Parse(newTemp.c_str());
    if(!tempJsonRecived.IsObject()){
        cout<<"Error: Json corrupto: "<<newTemp<<endl;
        return NULL;
    }
    rapidjson::Value& tempValue= tempJsonRecived[CHECK];
    if(tempValue.GetInt()!=CERO){
        cout<<"Error: no existe dato"<<endl;
        return NULL;
    }
}

void* LocalMemoryManager::getDataFromReference(int pID, int pSize) {
    string temp=_JsonMessageCreator->createMessage(OPERATION_RD, _Token, NULL,
            pSize, pID);
    string newTemp=(char*)_cliente->sendMessageToServer(temp);
    rapidjson::Document tempJsonRecived;
    tempJsonRecived.Parse(newTemp.c_str());
    if(!tempJsonRecived.IsObject()){
        cout<<"Error: Json corrupto: "<<newTemp<<endl;
        return NULL;
    }
    rapidjson::Value& tempValue= tempJsonRecived[CHECK];
    if(tempValue.GetInt()!=CERO){
        cout<<"Error: no existe dato"<<endl;
        return NULL;
    }
    tempValue= tempJsonRecived[MESSAGE];
    return (void*)tempValue.GetString();
}
