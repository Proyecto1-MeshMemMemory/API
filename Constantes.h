/* 
 * File:   Constantes.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:41 PM
 */

#ifndef CONSTANTES_H
#define	CONSTANTES_H
#include <chrono>
#include <iostream>
#include <ctime>

class Constantes {
public:
    /*tipado de datos con los cuales se trabajara*/
    static const int CHAR=1;
    static const int INT=2;
    static const int FLOAT=3;
    static const int DOUBLE=4;
    
    /*numeros de multiproposito*/
    
    static const int CERO=0;
    static const int UNO=1;
    static const int DOS=2;
    static const int TRES=3;
    static const int CUATRO=4;
    static const int CINCO=5;
    static const int SEIS=6;
    static const int SIETE=7;
    static const int DIEZ=10;
    
    /*constantes de uso dentro de las clases*/
    
    static const int BUFFER_SIZE=10;
    static const int TOKE_SIZE=128;
    /*write memory*/
    static const int OPERATION_WR=0;
    /*read memory*/
    static const int OPERATION_RD=1;
    /*delete memory*/
    static const int OPERATION_DL=2;
    /*allocate memory*/
    static const int OPERATION_AL=3;
    /*increment reference counter*/
    static const int OPERATION_IR=4;
    /*decrement reference counter*/
    static const int OPERATION_DR=5;
    static const char* REQUEST_NEW_TOKEN;
    static const char* OPERATION;
    static const char* TOKEN;
    static const char* ID;
    static const char* MESSAGE;
    static const char* CHECK;
    
    /*Errores por parte del cliente que se usara*/
    
    static const char* ERROR1;
    static const char* ERROR2;
    static const char* ERROR3;
    static const char* ERROR4;
    static const char* ERROR5;
    static const char* ERROR6;
    
    void sleep_(double pSeconds){
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds;
        while(pSeconds>elapsed_seconds.count()){
            end = std::chrono::system_clock::now();
            elapsed_seconds= end-start;
        }
        //std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    };
};

#endif	/* CONSTANTES_H */

