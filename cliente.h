/* 
 * File:   cliente.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:41 PM
 */

#ifndef CLIENTE_H
#define	CLIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <iostream>
#include "Constantes.h"

using namespace std;
class cliente :public Constantes{
public:
    cliente(int pPort, char* pIP);
    virtual ~cliente();
    void * connectToServer();
    void* sendMessageToServer(string pMessage, int pLenght );
    void* sendMessageToServer(string pMessage);
private:
    int _port;
    char* _ip;
    int _sockfd,_n;
    struct sockaddr_in _serv_addr;
    struct hostent * _server;
    void error(const char* msg);

};

#endif	/* CLIENTE_H */

