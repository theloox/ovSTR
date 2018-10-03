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
#include <stdarg.h>
#include <string.h>

#include <time.h>

#include "ovStr.h"

#ifndef _OVSTRARRAY_H
#define _OVSTRARRAY_H

#ifndef OVSTRARRAY_ALLOC
#define OVSTRARRAY_ALLOC 64
#endif

typedef struct ovStrArrayElement {
    unsigned int raw;
    int index;
    ovStr *key;
    ovStr *value;

};

class ovStrArray {

private:
    //unsigned int n;
    //unsigned int m;
    unsigned int vAlloc;
    ovStrArrayElement *vArray;
    int id;

    int _Alloc(int z);
    int _ReAlloc(int z);
    int _Free();

    void quicksort(ovStrArray &array, int low, int high, int order);


public:
    unsigned int n;
    unsigned int m;

    ovStrArray();
    ovStrArray(ovStr &str);
    ovStrArray(const char *str);
    ovStrArray(ovStrArray &array);
    ovStrArray(const ovStrArray &array);

    ~ovStrArray();

    int Alloc(unsigned int z);

    int Add(const char *str);
    int Add(const char *str, unsigned int index);
    int Add(const char *str, const char *key);

    int Store(const char *str, unsigned int key);
    int Store(const char *str, const char *key);


    void Clean();
    int Count();
    bool IsEmpty();

    int Key(unsigned int index);
    int Key(const char *key);
    int RawKeyInt(unsigned int index);
    ovStr ovStrArray::RawKey(unsigned int index);

    ovStr Value(unsigned int index);
    ovStr Value(const char *key);
    ovStr ovStrArray::RawValue(unsigned int index);


    ovStrArray & operator = (ovStrArray &array);
    ovStrArray & operator = (const ovStrArray &array);

    ovStr operator [](unsigned int index);
    ovStr operator [](const char *key);

    void ReadFile(ovStr file);

    ovStrArray QSort();
};

#endif
