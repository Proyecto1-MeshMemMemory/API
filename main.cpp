/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:40 PM
 */

#include <cstdlib>
#include "LocalMemoryManager.h"
#include "xReference.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    /*
    LocalMemoryManager* nuevo = new LocalMemoryManager();
    xReference<int>* object= new xReference<int>(-1, 0, 0, nuevo);
    //cout<<object->getType()<<endl;
    
    xReference<int>* object2= new xReference<int>(-1, 0, 0, nuevo);
    //cout<<object2->getType()<<endl;
    
    //prueba de igualdad
    if ((*object) == (*object2)){
        cout<<"Si"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    
    //prueba de desigualdad
    if ((*object) != (*object2)){
        cout<<"Si"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    //prueba para igualdad 
    (*object)=(*object2);
    //prueba de desreferencia 
    *(*object);
     * */
    xReference<char>* xRefNuevo;
    LocalMemoryManager * nuevo = new LocalMemoryManager();
    nuevo->initialize(5001,"127.0.0.1\0");
    //nuevo->requestNewToken();
    xRefNuevo=(xReference<char>*)nuevo->xMalloc(4,sizeof(char));
    while(true);
    return 0;
}

