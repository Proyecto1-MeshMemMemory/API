/* 
 * File:   LocalMemoryManager.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:42 PM
 */

#ifndef LOCALMEMORYMANAGER_H
#define	LOCALMEMORYMANAGER_H
#include "cliente.h"
#include "Constantes.h"
#include "JsonCreator.h"
#include <new>

/**
 * clase para crear el singleton que va a manejar a nivel local los datos.
 */
class LocalMemoryManager : public Constantes{
public:
    LocalMemoryManager();
    virtual ~LocalMemoryManager();
    char* initialize(int pPort, char* pIp);
    void* xMalloc(int pSize, int pType);
    void* xMalloc(int pSize, int pType, void* pValue);
    void xAssing(void* pRefe, void* pValue, int pType);
    void xFree(void* pRefe, int pType);
    void* changeReferenceCounter(std::string pID, int pOp);
    void* getDataFromReference(std::string pID, int pSize);
private:
    cliente * _cliente;
    JsonCreator* _JsonMessageCreator;
    char* _Token;
    char* requestNewToken();
    int getSizeOfType(int pType);
};

#endif	/* LOCALMEMORYMANAGER_H */

