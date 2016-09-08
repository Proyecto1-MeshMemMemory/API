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

template <class T> 

class xReference {
public:
    xReference(int pID, int pSize, int pType);
    virtual ~xReference();
    int getType();
    int getCount();
    void setType(int pType);
    friend bool operator==(const xReference<T>& obj, const xReference<T>& obj2){
        bool rVal = false;      
        if (obj._type==obj2._type){
            rVal = true;
        }     
        return rVal;
    };
    
    friend bool operator!=(const xReference<T>& obj, const xReference<T>& obj2){
        bool rVal = false;      
        if (obj._type!=obj2._type){
            rVal = true;
        }     
        return rVal;     
    };
    
    xReference& operator=(const xReference<T>& obj){
        obj._count++;
        printf("Tome mil :3:\n");
        //return 0;
    }
    
    friend void operator*(const xReference<T>& obj){
        printf("Tome dos mil :3\n");
    }
    
private:
    int _ID;
    int _size;
    int _type;
    int _count;
};

#endif	/* XREFERENCE_H */