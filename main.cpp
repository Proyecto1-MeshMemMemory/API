/* 
 * File:   main.cpp
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:40 PM
 */

#include <cstdlib>

#include "xReference.h"
#include "xReference.cpp"

using namespace std;

int main(int argc, char** argv) {
    
    
    xReference<int>* object= new xReference<int>(0, 0, 0);
    object->setType(0);
    cout<<object->getType()<<endl;
    
    xReference<int>* object2= new xReference<int>(0, 0, 0);
    object2->setType(1);
    cout<<object2->getType()<<endl;
    
    if ((*object) == (*object2)){
        cout<<"Si"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    
    if ((*object) != (*object2)){
        cout<<"Si"<<endl;
    }
    else{
        cout<<"No"<<endl;
    }
    *(*object);
    cout<<object->getCount()<<endl;
    (*object);
    
    return 0;
}

