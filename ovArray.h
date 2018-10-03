/***************************************************************************
 *   2004-2006 by Axel Gonzalez                                            *
 *   loox@e-shell.net                                                      *
 *                                                                         *
 *   This software is in the public domain. Permission to use, copy,       *
 *   modify, and distribute this software and its documentation for any    *
 *   purpose and without fee is hereby granted, without any conditions or  *
 *   restrictions. This software is provided "as is" without express or    *
 *   implied warranty.                                                     *
 *                                                                         *
 ***************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "ovStr.h"

#ifndef _OVARRAY_H
#define _OVARRAY_H

#ifndef OVARRAY_ALLOC
#define OVARRAY_ALLOC 64
#endif


//#define X int
template <class X>
class ovArrayElement {
public:
    unsigned int raw;
    int index;
    ovStr *key;
    X *value;
};

template <class X>
class ovArray {

private:
    unsigned int n;
    unsigned int m;
    unsigned int vAlloc;
    ovArrayElement<X> *vArray;
    int id;

    int _Alloc(int z);
    int _ReAlloc(int z);
    int _Free();


public:

    ovArray();
    ovArray(ovArray &array);
    ovArray(const ovArray &array);

    ~ovArray();

    int Alloc(unsigned int z);

    int Add(X x);

    int Store(X x, unsigned int key);
    int Store(X x, ovStr key);


    void Clean();
    int Count();
    bool IsEmpty();

    int Key(unsigned int index);
    int Key(ovStr key);
    X Value(unsigned int index);
    X Value(ovStr key);

    ovArray & operator = (ovArray &array);
    ovArray & operator = (const ovArray &array);

    X operator [](unsigned int index);
    X operator [](const char *key);

};

#endif
