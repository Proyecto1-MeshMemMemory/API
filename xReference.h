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

/**
 * clase que hace los xReference.
 */
template <class T> 
class xReference : public Constantes{
    friend class LocalMemoryManager;
public:
    virtual ~xReference(){
        
    };
    
    /**
     * metodo para obetener el tipo del xReference.
     * @return entero del tipado
     */
    int getType(){
        return _type;
    };
    
    /**
     * retorna la cantidad de apuntadores que tiene el objeto.
     * @return entero de la cantidad de conteos.
     */
    int getCount(){
        return _count;
    };
    
    /**
     * retorna el id del objeto 
     * @return entero del id del objeto.
     */
    string getID(){
        return _ID;
    };
    
    /**
     * obtiene el tamaño del objeto guardado en el Manager.
     * @return entero del tamaño.
     */
    int getSize(){
        return _size;
    };
    
    /**
     * sobrecarga del operador '==', este operador lo vamos a usar para 
     * comparar un objeto xReference y otro.
     * @param obj recibe un otro xReference para comparar.
     * @return return booleano de si la verificacion.
     */
    friend bool operator==(const xReference<T>& obj, const xReference<T>& obj2){
        bool rVal = false;      
        if (obj._ID==obj2._ID && obj._type==obj2._type){
            rVal = true;
        }     
        return rVal;
    };
    
    /**
     * sobrecarga del operador '!=', este operador lo vamos a usar para 
     * comparar un objeto xReference y otro.
     * @param obj recibe un otro xReference para comparar.
     * @return return booleano de si la verificacion.
     */
    friend bool operator!=(const xReference<T>& obj, const xReference<T>& obj2){
        bool rVal = false;      
        if (obj._ID!=obj2._ID && obj._type!=obj2._type){
            rVal = true;
        }     
        return rVal;     
    };
    
    /**
     * operador de igualdad, este verifica que sean diferentes y los datos
     * internos del objeto 1 se hacen iguales a los del objeto 2.
     * @param obj
     * @return 
     */
    xReference& operator=(const xReference<T>& obj){ 
        if(obj==NULL){
            this->_pointerToLocalManager->changeReferenceCounter(this->_ID,OPERATION_DR);
            this->_ID=NULL;
            this->_type=NULL;
            this->_size=NULL;
            this->_count=NULL;
        }
        else if(this != &obj){
            this->_pointerToLocalManager->changeReferenceCounter(this->_ID,OPERATION_DR);
            this->_pointerToLocalManager->changeReferenceCounter(obj._ID,OPERATION_IR);
            this->_ID=obj._ID;
            this->_type=obj._type;
            this->_size=obj._size;
            this->_count=obj._count;
        }
    }
    
    /**
     * metodo para realizarle una desreferencia del objeto y pedirselo al Local
     * Manager y este al Manager.
     * @return retorna el objeto del Manager y lo guarda en memoria para su
     * previo uso.
     */
    void* operator*(){
        void * temp= this->_pointerToLocalManager->getDataFromReference(_ID,
                OPERATION_RD);
        return temp;
    };
    
private:
    std::string _ID;
    int _size;
    int _type;
    int _count;
    LocalMemoryManager* _pointerToLocalManager;
    /**
     * constructor que se usa nada mas sobre el Manager locar ya que es privado.
     * @param pID recibe el id del objetp, el tipado y el this del manager.
     * @param pSize
     * @param pType
     * @param pLocalManager
     */
    xReference(std::string pID, int pSize, int pType, LocalMemoryManager* pLocalManager){
        _ID=pID;
        _size=pSize;
        _type=pType;
        _pointerToLocalManager=pLocalManager;
    };
};


#endif	/* XREFERENCE_H */

