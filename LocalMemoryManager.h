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
#include "Constantes.h"


class LocalMemoryManager : public Constantes{
public:
    LocalMemoryManager();
    virtual ~LocalMemoryManager();
    xReference* xMalloc(int pSize, int pType);
    xReference* xMalloc(int pSize, int pType, void* pValue);
    void xAssing(xReference* pRefe, void* pValue);
    void xFree(xReference* pRefe);
private:
    cliente * _cliente;
    

};

#endif	/* LOCALMEMORYMANAGER_H */

