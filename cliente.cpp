/* 
 * File:   cliente.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:41 PM
 */

#include "cliente.h"

cliente::cliente(int pPort, char* pIP) {
    _ip=pIP;
    _port=pPort;
}

cliente::~cliente() {
    
}

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

void cliente::error(const char* msg) {
    perror(msg);
    exit(UNO);
}