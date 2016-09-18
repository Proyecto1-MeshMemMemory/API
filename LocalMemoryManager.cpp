/* 
 * File:   LocalMemoryManager.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:42 PM
 */

#include "LocalMemoryManager.h"
#include "xReference.h"
#include "libb64-1.2/include/b64/cdecode.h"

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
    string temp=(char*)_cliente->connectToServer();
    cout<<temp<<endl;
    _JsonMessageCreator= new JsonCreator();
    //extraemos el Token que viene dentro del Json.
    rapidjson::Document JsonTkoneTemp;
    JsonTkoneTemp.Parse(temp.c_str());
    if(!JsonTkoneTemp.IsObject()){
        cout<<"Error: Json corrupto"<<endl;
        return NULL;
    }
    rapidjson::Value& TokenInJson=JsonTkoneTemp[TOKEN];
    _Token=(char*)TokenInJson.GetString();
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
 * metodo para obtener el tamaño del tipado del dato segun el 
 * dato que se escogio que sera el xReference.
 * @param pType se ingresa la constante del tipado que tenemos.
 * @return retorna el peso del tipado real en c++.
 */
int LocalMemoryManager::getSizeOfType(int pType) {
    if(pType==CHAR)
        return sizeof(char);
    else if(pType==INT)
        return sizeof(int);
    else if(pType==FLOAT)
        return sizeof(float);
    else if(pType==DOUBLE)
        return sizeof(double);
    else if(pType==LONG)
        return sizeof(long);
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
            NULL,pSize*getSizeOfType(pType),-UNO);
    std::string tempFromServer=(char*)_cliente->sendMessageToServer(temp);
    rapidjson::Document JsonDocument;
    JsonDocument.Parse(tempFromServer.c_str());
    if(!JsonDocument.IsObject()){
        std::cout<<"Error: Json corrupto:"<<tempFromServer<<std::endl;
        return NULL;
    }
    rapidjson::Value & respondCheck= JsonDocument[CHECK];
    //revisamos si es un positivo la accion pedida.
    if(respondCheck.GetInt()==DOS){
        std::cout<<"Error: token invalido o expirado"<<std::endl;
        requestNewToken();
        return xMalloc(pSize, pType);
    }
    else if(respondCheck.GetInt()==UNO){
        std::cout<<"Error: alojamiento de memoria invalido"<<std::endl;
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
            tempId, pSize*getSizeOfType(pType),CHAR, this);
        //se retorna el puntero como un void* asi como se hace con un malloc
        return (void*)tempRefe;
    }else if(pType==INT){
        void* ptrVoidRefe=malloc(sizeof(xReference<int>));
        xReference<int>* tempRefe= new (ptrVoidRefe) xReference<int>(
            tempId, pSize*getSizeOfType(pType),INT, this);
        return (void*)tempRefe;
    }else if(pType==FLOAT){
        void* ptrVoidRefe=malloc(sizeof(xReference<float>));
        xReference<float>* tempRefe= new (ptrVoidRefe) xReference<float>(
            tempId, pSize*getSizeOfType(pType),FLOAT, this);
        return (void*)tempRefe;
    }else if(pType==DOUBLE){
        void* ptrVoidRefe=malloc(sizeof(xReference<double>));
        xReference<double>* tempRefe= new (ptrVoidRefe) xReference<double>(
            tempId, pSize*getSizeOfType(pType),DOUBLE, this);
        return (void*)tempRefe;
    }else if(pType==LONG){
        void* ptrVoidRefe=malloc(sizeof(xReference<long>));
        xReference<long>* tempRefe= new (ptrVoidRefe) xReference<long>(
            tempId, pSize*getSizeOfType(pType),LONG, this);
        return (void*)tempRefe;
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
            pValue,pSize*getSizeOfType(pType),-UNO);
    std::string tempFromServer=(char*)_cliente->sendMessageToServer(temp);
    rapidjson::Document JsonDocument;
    JsonDocument.Parse(tempFromServer.c_str());
    if(!JsonDocument.IsObject()){
        std::cout<<"Error: Json corrupto"<<std::endl;
        return NULL;
    }
    rapidjson::Value & respondCheck= JsonDocument[CHECK];
    //revisamos si el token existe
    if(respondCheck.GetInt()==DOS){
        std::cout<<"Error: token invalido o expirado"<<std::endl;
        requestNewToken();
        return xMalloc(pSize, pType, pValue);
    }
    else if(respondCheck.GetInt()==UNO){
        std::cout<<"Error: alojamiento de memoria invalido"<<std::endl;
        return NULL;
    }
    rapidjson::Value & respondId= JsonDocument[ID];
    int tempId= respondId.GetInt();
    if(pType==CHAR){
        void* ptrVoidRefe=malloc(sizeof(xReference<char>));
        xReference<char>* tempRefe= new (ptrVoidRefe) xReference<char>(
            tempId, pSize*getSizeOfType(pType),CHAR, this);
        free(pValue);
        return (void*)tempRefe;
    }else if(pType==INT){
        void* ptrVoidRefe=malloc(sizeof(xReference<int>));
        xReference<int>* tempRefe= new (ptrVoidRefe) xReference<int>(
            tempId, pSize*getSizeOfType(pType),INT, this);
        free(pValue);
        return (void*)tempRefe;
    }else if(pType==FLOAT){
        void* ptrVoidRefe=malloc(sizeof(xReference<float>));
        xReference<float>* tempRefe= new (ptrVoidRefe) xReference<float>(
            tempId, pSize*getSizeOfType(pType),FLOAT,this);
        free(pValue);
        return (void*)tempRefe;
    }else if(pType==DOUBLE){
        void* ptrVoidRefe=malloc(sizeof(xReference<double>));
        xReference<double>* tempRefe= new (ptrVoidRefe) xReference<double>(
            tempId, pSize*getSizeOfType(pType),DOUBLE,this);
        free(pValue);
        return (void*)tempRefe;
    }else if(pType==LONG){
        void* ptrVoidRefe=malloc(sizeof(xReference<long>));
        xReference<long>* tempRefe= new (ptrVoidRefe) xReference<long>(
            tempId, pSize*getSizeOfType(pType),LONG, this);
        return (void*)tempRefe;
    }
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
    }else if(pType==DOUBLE){
        xReference<double>* xRefePtr= (xReference<double>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue,
            xRefePtr->getSize(),xRefePtr->getID());
    }else if(pType==LONG){
        xReference<long>* xRefePtr= (xReference<long>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_WR, _Token, pValue,
            xRefePtr->getSize(),xRefePtr->getID());
    }
    
    temp=(char*)_cliente->sendMessageToServer(temp);
    std::cout<<temp<<std::endl;
    rapidjson::Document JsonFromServer;
    JsonFromServer.Parse(temp.c_str());
    if(!JsonFromServer.IsObject()){
        std::cout<<"Error: Json corrupto"<<std::endl;
        return;
    }
    rapidjson::Value & respondCheck= JsonFromServer[CHECK];
    //revisamos si es un positivo la accion pedida.
    if(respondCheck.GetInt()==DOS){
        std::cout<<"Error: token invalido o expirado"<<std::endl;
        requestNewToken();
        return xAssing(pRefe, pValue, pType);
    }
    else if(respondCheck.GetInt()==UNO){
        std::cout<<"Error: alojamiento de memoria invalido"<<std::endl;
        return;
    }
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
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 
                xRefePtr->getSize(),xRefePtr->getID());
    }else if(pType==INT){
        xReference<int>* xRefePtr= (xReference<int>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 
                xRefePtr->getSize(),xRefePtr->getID());
    }else if(pType==FLOAT){
        xReference<float>* xRefePtr= (xReference<float>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 
                xRefePtr->getSize(),xRefePtr->getID());
    }if(pType==DOUBLE){
        xReference<double>* xRefePtr= (xReference<double>*)pRefe;
        temp= _JsonMessageCreator->createMessage(OPERATION_DL, _Token, NULL, 
                xRefePtr->getSize(),xRefePtr->getID());
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
 * metodo para decodificar el arreglo de chars que contiene codificacion en 
 * base64, se le ingresa el arreglo y el largo de este y nos devolvera un 
 * arreglo que contiene los bytes que anteriormente se habian codificado.
 * @param input recibe un const char* que es el arreglo de caracteres 
 * codificado.
 * @param lenght dato del tipo entero que es el largo de la cadena de 
 * caracteres.
 * @return retorna un arreglo de char que contiene los bytes que se habian 
 * codificado.
 */
char* decode(const char* input, int lenght){
    /* set up a destination buffer large enough to hold the encoded data */
    char* output = (char*)malloc(lenght+1);
    /* keep track of our decoded position */
    char* c = output;
    /* store the number of bytes decoded by a single call */
    int cnt = 0;
    /* we need a decoder state */
    base64_decodestate s;
            /*---------- START DECODING ----------*/
    /* initialise the decoder state */
    base64_init_decodestate(&s);
    /* decode the input data */
    cnt = base64_decode_block(input, lenght, c, &s);
    c += cnt;
    /* note: there is no base64_decode_blockend! */
    /*---------- STOP DECODING  ----------*/

    /* we want to print the decoded data, so null-terminate it: */
    (*c) = '\0';

    return output;
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
    string tempMsg=tempValue.GetString();
    char* decodedMsg;
    decodedMsg = decode(tempMsg.c_str(), pSize);
    void *dataRecovered= malloc(pSize);
    memcpy(&dataRecovered, (const char*)decodedMsg, pSize);
    return dataRecovered;
}