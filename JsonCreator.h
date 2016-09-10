/* 
 * File:   JsonCreator.h
 * Author: ellioth
 *
 * Created on September 8, 2016, 6:38 AM
 */

#ifndef JSONCREATOR_H
#define	JSONCREATOR_H
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "Constantes.h"

/**
 * metodo para hacer Jsons segun los parametro que se le proporcionen.
 */
using namespace std;
class JsonCreator : public Constantes{
public:
    JsonCreator();
    virtual ~JsonCreator();
    std::string createMessage(int pOperation, std::string pToken, void* pMessage,
    int pLenght,  int pId);

};

#endif	/* JSONCREATOR_H */

