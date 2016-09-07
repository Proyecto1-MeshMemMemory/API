/* 
 * File:   xReference.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:41 PM
 */

#ifndef XREFERENCE_H
#define	XREFERENCE_H

template <typename dp>
class xReference {
public:
    xReference();
    virtual ~xReference();
    //xReference operator==();
    
private:
    int ID;
    int size;
    char* type;
    dp * m_ptData;
};

#endif	/* XREFERENCE_H */