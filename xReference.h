/* 
 * File:   xReference.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:41 PM
 */

#ifndef XREFERENCE_H
#define	XREFERENCE_H
#include <string>

template <class dp>
class xReference {
public:
    xReference();
    virtual ~xReference();
private:
    int ID;
    int size;
    char* type;
    dp * m_ptData;
};

#endif	/* XREFERENCE_H */