/* 
 * File:   LocalMemoryManager.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:42 PM
 */

#include "LocalMemoryManager.h"
#include "xReference.h"

/**
 * constructor de la clase
 */
LocalMemoryManager::LocalMemoryManager() {
    _Token=NULL;
}

/**
 * destructor
 */
LocalMemoryManager::~LocalMemoryManager() {
}

/**
 * metodo para inicializar la conexion contra el manager remoto, recibe un 
 * puerto y un ip.
 * @param pPort recibe un entero que es el puerto
 * @param pIp recibe un char* que es el ip.
 * @return retorna elresultado del mensaje recibido y por dehajo establece el 
 * token recibido.
 */
char* LocalMemoryManager::initialize(int pPort, char* pIp) {
    _cliente= new cliente(pPort, pIp);
    _Token=(char*)_cliente->connectToServer();
    _JsonMessageCreator= new JsonCreator();
}

/**
 * metodo para pedir un nuevo toke.
 * @return retorna el mensaje recibido por el Manager.
 */
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

/**
 * metodo para pedirle memoria al Manager, recibe la cantidad de espacio que se 
 * quiere pedir y el typo del dato que estan creando.
 * @param pSize entero del tamaño del espacio que van a pedir.
 * @param pType entero del tipo de dato que van a pedir.
 * @return retorna un puntero xReference en forma de void * ya que no existe un 
 * solo tipo que se puede retornar al ser un template el xReference.
 */
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

/**
 * metodo para pedirle memoria al Manager, recibe la cantidad de espacio que se 
 * quiere pedir, el typo del dato que estan creando y el dato que de una vez 
 * vamos a guardar en ese espacio de memoria.
 * @param pSize entero del tamaño del espacio que van a pedir.
 * @param pType entero del tipo de dato que van a pedir.
 * @param pValue es dato que vamos a guardar en el espacio de memoria.
 * @return retorna un puntero xReference en forma de void * ya que no existe un 
 * solo tipo que se puede retornar al ser un template el xReference.
 */
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

/**
 * metodo para asignar un cierto dato a una posicion de memoria dentro del 
 * manager y una vez terminado libera el dato que el pasamos, recibe un 
 * xReference, el valor que queremos y el tipado del xReference.
 * @param pRefe dato tipo xReference<T>* es la referencia donde vamos a 
 * guardarla.
 * @param pValue dato tipo void*, es el dato queremos enviar.
 * @param pType dato entero, es la constante del tipado que vamos a usar.
 */
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

/**
 * metodo para liberar memoria, recibe un xReference y su tipado, 
 * @param pRefe puntero del xReference que queremos liberar.
 * @param pType entero del tipado del dato.
 */
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

/**
 * metodo para cambiar la cantidad de referencias de un xReference en el 
 * Manager, recibe un entero del id y un entero de la operacion que vamos a
 * realizar, ya sea aumentar o disminuir conteo de referencias.
 * @param pID entero del id del xReference.
 * @param pOp entero de la operacion que vamos a realizar.
 * @return retorna el mensaje que nos devolvio el Manager.
 */
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

/**
 * metodo para realizar la desreferencia de un xReference, con lo cual se nos
 * devolvera el dato al que apunta ese xReference. Recibe el id del objeto y 
 * el tamaño que esta pidiendo.
 * @param pID entero que es el id del objeto que queremos.
 * @param pSize entero del tamaño del objeto que estamos pidiendo.
 * @return retorna el dato almacenado ahora en un puntero void*s
 */
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
    void * tempToReturn= malloc(pSize);
    string tempDataFromJson= tempValue.GetString();
    memcpy(tempToReturn, tempDataFromJson.c_str(), pSize);
    return tempToReturn;
}
