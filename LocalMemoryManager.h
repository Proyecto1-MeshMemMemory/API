/* 
 * File:   LocalMemoryManager.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:42 PM
 */

#ifndef LOCALMEMORYMANAGER_H
#define	LOCALMEMORYMANAGER_H
#include "cliente.h"
#include "xReference.h"
#include "xReference.cpp"
#include "Constantes.h"
#include "JsonCreator.h"
#include <new>

class LocalMemoryManager : public Constantes{
public:
    LocalMemoryManager();
    virtual ~LocalMemoryManager();
    char* initialize(int pPort, char* pIp);
    char* requestNewToken();
    void* xMalloc(int pSize, int pType);
    void* xMalloc(int pSize, int pType, void* pValue);
    void xAssing(void* pRefe, void* pValue, int pType);
    void xFree(void* pRefe, int pType);
private:
    cliente * _cliente;
    JsonCreator* _JsonMessageCreator;
    char* _Token;
};

#endif	/* LOCALMEMORYMANAGER_H */

