/* 
 * File:   JsonCreator.h
 * Author: ellioth
 *
 * Created on September 7, 2016, 11:31 PM
 */

#ifndef JSONCREATOR_H
#define	JSONCREATOR_H
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "Constantes.h"

using namespace std;
class JsonCreator: public Constantes {
public:
    JsonCreator();
    virtual ~JsonCreator();
    string createMessage(int pOperation, string pToken, void* pMessage,
    int pLenght,  int pId);
    
private:

};

#endif	/* JSONCREATOR_H */

