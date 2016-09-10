/* 
 * File:   xReference.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:41 PM
 */

#ifndef XREFERENCE_H
#define	XREFERENCE_H
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include "Constantes.h"
#include "LocalMemoryManager.h"

template <class T> 
class xReference : public Constantes{
    friend class LocalMemoryManager;
protected:
    int _ID;
    int _size;
    int _type;
    int _count;
    LocalMemoryManager* _pointerToLocalManager;
public:
    xReference(int pID, int pSize, int pType, LocalMemoryManager* pLocalManager){
        _ID=pID;
        _size=pSize;
        _type=pType;
        _pointerToLocalManager=pLocalManager;
    };
    virtual ~xReference(){
        
    };
    int getType(){
        return _type;
    };
    int getCount(){
        return _count;
    };
    int getID(){
        return _ID;
    };
    int getSize(){
        return _size;
    };
    friend bool operator==(const xReference<T>& obj, const xReference<T>& obj2){
        bool rVal = false;      
        if (obj._ID==obj2._ID && obj._type==obj2._type){
            rVal = true;
        }     
        return rVal;
    };
    
    friend bool operator!=(const xReference<T>& obj, const xReference<T>& obj2){
        bool rVal = false;      
        if (obj._ID!=obj2._ID && obj._type!=obj2._type){
            rVal = true;
        }     
        return rVal;     
    };
    
    xReference& operator=(const xReference<T>& obj){   
        if(this != &obj){
            printf("Tome mil :3:\n");
            this->_pointerToLocalManager->changeReferenceCounter(this->_ID,OPERATION_DR);
            this->_pointerToLocalManager->changeReferenceCounter(obj._ID,OPERATION_IR);
            this->_ID=obj._ID;
        }
    }
    xReference<T>& operator*(){
        this->_pointerToLocalManager->getDataFromReference(_ID, OPERATION_RD);
        printf("Tome dos mil :3\n");
    };
    
};


#endif	/* XREFERENCE_H */

