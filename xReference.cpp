/* 
 * File:   xReference.cpp
 * Author: ellioth
 * 
 * Created on September 6, 2016, 12:41 PM
 */

#include "xReference.h"

template<class T>
xReference<T>::xReference(int pID, int pSize, int pType) {
    _ID=pID;
    _size=pSize;
    _type=pType;
    _count=0;
}

template <class T>
xReference<T>::~xReference() {}

template<class T>
int xReference<T>::getType(){
    return _type;
}

template<class T>
void xReference<T>::setType(int pType) {
    _type=pType;
}

template<class T>
int xReference<T>::getCount(){
    return _count;
}