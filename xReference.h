/* 
 * File:   xReference.h
 * Author: ellioth
 *
 * Created on September 6, 2016, 12:41 PM
 */

#ifndef XREFERENCE_H
#define	XREFERENCE_H

template <typename jojo>
class xReference {
public:
    xReference();
    xReference(const xReference& orig);
    virtual ~xReference();
    xReference operator==();
    
private:
    int ID;
    int size;
    char* type;
    jojo *m_ptData;
};

#endif	/* XREFERENCE_H */