/* 
 * File:   JsonCreator.cpp
 * Author: ellioth
 * 
 * Created on September 8, 2016, 6:38 AM
 */

#include "JsonCreator.h"
#include "libb64-1.2/include/b64/cencode.h"

/**
 * Metodo para codificar una cadena de bytes copiados a un arreglo de chars y 
 * nos devolvera el significativo en codificacion de base64, este metodo se 
 * asegurar la no corrupcion de datos mediante la transferencia.
 * @param input dato del tipo const char* que es arreglo de los bytes que 
 * tenemos que convertir.
 * @param lenght dato del tipo entero que es el largo del arreglo de bytes.
 * @return retorna un arreglo de char* con caracteres visibles de ASCII.
 */
char* encode(const char* input, int lenght){
    /* set up a destination buffer large enough to hold the encoded data */
    char* output = (char*)malloc(lenght+1);
    /* keep track of our encoded position */
    char* c = output;
    /* store the number of bytes encoded by a single call */
    int cnt = 0;
    /* we need an encoder state */
    base64_encodestate s;

    /*---------- START ENCODING ----------*/
    /* initialise the encoder state */
    base64_init_encodestate(&s);
    /* gather data from the input and send it to the output */
    cnt = base64_encode_block(input, lenght, c, &s);
    c += cnt;
    /* since we have encoded the entire input string, we know that 
       there is no more input data; finalise the encoding */
    cnt = base64_encode_blockend(c, &s);
    c += cnt;
    /*---------- STOP ENCODING  ----------*/

    /* we want to print the encoded data, so null-terminate it: */
    (*c) = '\0';

    return output;
}

/**
 * constructor de la clase.
 */
JsonCreator::JsonCreator() {
}

/**
 * destructo de la clase
 */
JsonCreator::~JsonCreator() {
}

/**
 * metodo para crear el mensaje segun los parametros que se pasen.
 * @param pOperation entero de la operacion que queremos realizar.
 * @param pToken char* del token que estamos usando.
 * @param pMessage void* del mensaje que queremos envar a guardar.
 * @param pLenght entero del largo del mensaje que vamos a enviar-
 * @param pId entero del id del vamos a extrañr el daor
 * @return returna el mensaje ya creado.
 */
string JsonCreator::createMessage(int pOperation, string pToken, void* pMessage,
        int pLenght,  int pId) {
    rapidjson::StringBuffer JsonToWrite;
    rapidjson::Writer<rapidjson::StringBuffer> writer(JsonToWrite);
    writer.StartObject();
    //establecemos la operacion que queremos realizar
    writer.String(OPERATION);
    writer.Int(pOperation);
    //establecemos el token que se nos dio, 
    writer.String(TOKEN);
    writer.String(pToken.c_str());
    if(pMessage!=NULL){
        //establecemos el mensaje que queremos enviar
        //codificamos informacion
        char data[pLenght+UNO];
        memcpy(data, (const void*)pMessage, pLenght);
        data[pLenght]='\0';
        char* encodedMsg;
        encodedMsg = encode((const char*)data, pLenght+UNO);
        //ingresamos mensaje en el Json.
        writer.String(MESSAGE);
        writer.String(encodedMsg, pLenght+UNO, CERO);
    }
    if(pLenght>CERO){
        //establecemos el espacio que va a ocupar el mensaje
        writer.String(SIZE);
        writer.String(to_string(pLenght).c_str());
    }
    if(pId>-UNO){
        //establecemos el id que queremos pedir.
        writer.String(ID);
        writer.String(to_string(pId).c_str());
    }
    
    //cerramos el objeto
    writer.EndObject();
    return JsonToWrite.GetString();
}



