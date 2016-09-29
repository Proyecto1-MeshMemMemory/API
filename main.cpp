/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:40 PM
 */

#include <cstdlib>
#include "LocalMemoryManager.h"
#include "xReference.h"
#include <assert.h>
#include "Constantes.h"

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
    
    /*prueba para Api con un alojo de memoria*/
    Constantes* constt= new Constantes();
    xReference<int>* xRefNuevo=NULL;
    xReference<int>* xRefNuevo2=NULL;
    LocalMemoryManager * nuevo = new LocalMemoryManager();
    nuevo->initialize(5001,"127.0.0.1\0");
    //nuevo->requestNewToken();
    int* temp=(int*)malloc(sizeof(int));
    *temp=1234567;
    xRefNuevo=(xReference<int>*)nuevo->xMalloc(4,sizeof(int));
    xRefNuevo=(xReference<int>*)nuevo->xMalloc(4,sizeof(int),temp);
    nuevo->xAssing(xRefNuevo, temp, constt->INT);
    nuevo->xFree(xRefNuevo, constt->INT);
    if((*xRefNuevo)==(*xRefNuevo2)){
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    if((*xRefNuevo)!=(*xRefNuevo2)){
        cout<<"true"<<endl;
    }
    else
        cout<<"false"<<endl;
    
    while(true);
    
    /**lineas necesarias para codificar y decodificar**
    int datoToCode=9785144;
    char data[sizeof(datoToCode)+1];
    memcpy(data, (const void*)&datoToCode, sizeof(datoToCode));
    data[sizeof(datoToCode)]='\0';
    char* encoded;
    encoded = encode((const char*)data, sizeof(datoToCode)+1);
    char* decoded;
    decoded = decode(encoded, sizeof(datoToCode)+1);
    int dataRecovered;
    memcpy(&dataRecovered, (const char*)decoded, sizeof(datoToCode));
    /****
    int datoToCode=9785144;
    char data[sizeof(datoToCode)+1];
    memcpy(data, (const void*)&datoToCode, sizeof(datoToCode));
    data[sizeof(datoToCode)]='\0';
    cout<<data<<endl;
    const char* input = "hello world";
    char* encoded;
    char* decoded;

    /* encode the data *
    encoded = encode((const char*)data, sizeof(datoToCode)+1);
    printf("encoded: %s", encoded); /* encoded data has a trailing newline */

    /* decode the data *
    decoded = decode(encoded, sizeof(datoToCode)+1);
    printf("decoded: %s\n", decoded);
    for(int i =0; i< (sizeof(datoToCode)+1); i++){
        if(data[i]==decoded[i])
            cout<<"true"<<endl;
    }
    int dataRecovered;
    memcpy(&dataRecovered, (const char*)decoded, sizeof(datoToCode));
    cout<<dataRecovered<<endl;
    /* compare the original and decoded data *
    //assert(strcmp(input, decoded) == 0);

    free(encoded);
    free(decoded);*/
    return 0;
}

