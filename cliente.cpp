/* 
 * File:   cliente.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:41 PM
 */

#include "cliente.h"

/**
 * constructor, recibe el puerto y el ip a donde nos vamos a conectar.
 * @param pPort dato tipo entero, es el puerto.
 * @param pIP dato tipo char*, es el ip.
 */
cliente::cliente(int pPort, char* pIP) {
    _ip=pIP;
    _port=pPort;
}

/**
 * destructor
 */
cliente::~cliente() {
    
}

/**
 * metodo para conectar el servidor y este nos retornara el Token contra el que
 * cual hacemos las comunicaciones.
 * @return retorna el token en forma de char*.
 */
void* cliente::connectToServer() {
    _sockfd= socket(AF_INET, SOCK_STREAM, CERO);
    if (_sockfd < CERO) 
        error(ERROR1);
    _server = gethostbyname(_ip);
    if (_server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(CERO);
    }
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    bcopy((char *)_server->h_addr, 
        (char *)&_serv_addr.sin_addr.s_addr,
        _server->h_length);
    _serv_addr.sin_port = htons(_port);
    if (connect(_sockfd,(struct sockaddr *) &_serv_addr,sizeof(_serv_addr))<
            CERO) 
        error(ERROR4);
    void* askForToken=malloc(TOKE_SIZE);
    bzero(askForToken,TOKE_SIZE);
    _n=recv(_sockfd,askForToken,TOKE_SIZE,0);
    if(_n<CERO)
        error(ERROR6);
    return askForToken;
}

/**
 * metodo para enviar un mensaje al server con un tamaño definido.
 * @param pMessage recibe un string del mensaje en formato Json.
 * @param pLenght recibe un entero del largo de string Json que le enviamos.
 * @return retorna el resultado del envio del mensaje.
 */
void* cliente::sendMessageToServer(string pMessage, int pLenght) {
    void* bufferedReader=malloc(BUFFER_SIZE);
    char datoToServer[pLenght+UNO];
    strcpy(datoToServer,pMessage.c_str());
    datoToServer[pLenght]='\n';
    _n=send(_sockfd,datoToServer,pLenght+UNO,0);
    if(_n<CERO)
        error(ERROR4);
    bzero(bufferedReader,BUFFER_SIZE);
    _n=recv(_sockfd,bufferedReader,BUFFER_SIZE,0);
    if(_n<CERO)
        error(ERROR6);
    return bufferedReader;
}

/**
 * metodo para enviar un mensaje al server sin un tamaño definido.
 * @param pMessage recibe un string del mensaje en formato Json.
 * @return retorna el resultado del envio del mensaje.
 */
void* cliente::sendMessageToServer(string pMessage) {
    void* bufferedReader=malloc(BUFFER_SIZE);
    char datoToServer[pMessage.length()+UNO];
    strcpy(datoToServer,pMessage.c_str());
    datoToServer[pMessage.length()]='\n';
    _n=send(_sockfd,datoToServer,pMessage.length()+UNO,0);
    if(_n<CERO)
        error(ERROR4);
    bzero(bufferedReader, BUFFER_SIZE);
    _n=recv(_sockfd,bufferedReader,BUFFER_SIZE,0);
    if(_n<CERO)
        error(ERROR6);
    return bufferedReader;
}

/**
 * metodo debug para saber cuando se presente un error.
 * @param msg recibe el char* del mensaje que fue atrapado.
 */
void cliente::error(const char* msg) {
    perror(msg);
    exit(UNO);
}