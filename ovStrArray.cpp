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


#include "ovStrArray.h"

ovStrArray::ovStrArray()
{
    this->n = 0;
    this->m = 0;

    this->vAlloc = 0;
    this->vArray = NULL;
}


ovStrArray::ovStrArray(ovStr &str)
{
    this->n = 0;
    this->m = 0;

    this->vAlloc = 0;
    this->vArray = NULL;

    if (str.Len() == 0)
        return;

    this->Add(str);
}

ovStrArray::ovStrArray(const char *str)
{
    this->n = 0;
    this->m = 0;

    this->vAlloc = 0;
    this->vArray = NULL;

    if (strlen(str) == 0)
        return;

    this->Add(str);
}


ovStrArray::ovStrArray(ovStrArray &array)
{
    unsigned int i;

    this->n = array.n;
    this->m = array.m;

    this->vAlloc = 0;
    this->vArray = NULL;

    if (!Alloc(array.n))
        return;

    for (i = 0; i < array.n; i++)
    {
        this->vArray[i].raw = array.vArray[i].raw;
        this->vArray[i].index = array.vArray[i].index;

        if (array.vArray[i].key != NULL)
            this->vArray[i].key = new ovStr(*array.vArray[i].key);

        if (array.vArray[i].value != NULL)
            this->vArray[i].value = new ovStr(*array.vArray[i].value);
    }
}


ovStrArray::ovStrArray(const ovStrArray &array)
{
    unsigned int i;

    this->n = array.n;
    this->m = array.m;

    this->vAlloc = 0;
    this->vArray = NULL;

    if (!Alloc(array.n))
        return;

    for (i = 0; i < array.n; i++)
    {
        this->vArray[i].raw = array.vArray[i].raw;
        this->vArray[i].index = array.vArray[i].index;

        if (array.vArray[i].key != NULL)
            this->vArray[i].key = new ovStr(*array.vArray[i].key);

        if (array.vArray[i].value != NULL)
            this->vArray[i].value = new ovStr(*array.vArray[i].value);
    }
}


ovStrArray::~ovStrArray()
{
    Clean();
}


int ovStrArray::_Alloc(int z)
{
    unsigned int i;


    if (z <= 0)
        return(0);

    if (vAlloc != 0)
        return(_ReAlloc(z));

    vAlloc = (z % OVSTRARRAY_ALLOC ? z + (OVSTRARRAY_ALLOC - (z % OVSTRARRAY_ALLOC)) : z);

    vArray = (ovStrArrayElement *)calloc(vAlloc, sizeof(ovStrArrayElement));

    if (vArray == NULL)
        return(0);

    for (i = 0; i < vAlloc; i++)
    {
        vArray[i].raw = i;
        vArray[i].index = -1;
        vArray[i].key = NULL;
        vArray[i].value = NULL;
    }

    return(n);
}


int ovStrArray::_ReAlloc(int z)
{
    int y;
    unsigned int i;
    unsigned int t;


    y = n + z;

    t = (y % OVSTRARRAY_ALLOC ? y + (OVSTRARRAY_ALLOC - (y % OVSTRARRAY_ALLOC)) : y);


    if (t <= vAlloc)
        return(0);
    else
        vAlloc = t;

    vArray = (ovStrArrayElement *)realloc(vArray, vAlloc * sizeof(ovStrArrayElement));

    if (vArray == NULL)
        return(0);

    for (i = y - z; i < vAlloc; i++)
    {
        vArray[i].raw = i;
        vArray[i].index = -1;
        vArray[i].key = NULL;
        vArray[i].value = NULL;
    }

    return(z);
}


int ovStrArray::Add(const char *str)
{
    Alloc(1);

    vArray[n].index = m;
    vArray[n].value = new ovStr(str);

    n++;
    m++;

    return(1);
}


int ovStrArray::Add(const char *str, unsigned int key)
{

    int k;

    if ((k = Key(key)) > -1) {
        *vArray[k].value = str;
        return(0);
    }


    _Alloc(1);

    vArray[n].index = key;
    vArray[n].value = new ovStr(str);

    n++;

    if (key > m)
        m = key + 1;
    else
        m++;

    return(1);
}


int ovStrArray::Add(const char *str, const char *key)
{
    int k;

    if ((k = Key(key)) > -1) {
        if (k < 0 || k > n)
            return(0);

        *vArray[k].value = str;

        return(0);
    }


    _Alloc(1);

    vArray[n].key = new ovStr(key);
    vArray[n].value = new ovStr(str);

    n++;

    return(n);
}


int ovStrArray::Alloc(unsigned int z)
{
    return(_Alloc(z));
}


void ovStrArray::Clean()
{
    unsigned int i;

    for (i = 0; i < n; i++) {
        if (vArray[i].key != NULL)
            delete(vArray[i].key);
        if (vArray[i].value != NULL)
            delete(vArray[i].value);
    }

    if (vAlloc != 0) {
        vAlloc = 0;
        free(vArray);
    }

    n = 0;
    m = 0;
}

int ovStrArray::Count()
{
    return(this->n);
}

bool ovStrArray::IsEmpty()
{
    return(this->Count() ? false : true);
}

int ovStrArray::Store(const char *str, unsigned int key)
{
    int k;


    k = Key(key);

    if (k < 0)
        return(0);

    delete(vArray[k].value);
    vArray[k].value = new ovStr(str);

    return(1);
}


//operatorz

ovStrArray & ovStrArray::operator = (ovStrArray &array)
{
    int i;


    this->Clean();

    this->n = array.n;
    this->m = array.m;

    _Alloc(n);

    for(i = 0; i < n; i++) {
        this->vArray[i].raw = array.vArray[i].raw;
        this->vArray[i].index = array.vArray[i].index;

        if (array.vArray[i].key != NULL)
            this->vArray[i].key = new ovStr(*array.vArray[i].key);

        if (array.vArray[i].value != NULL)
            this->vArray[i].value = new ovStr(*array.vArray[i].value);

    }

    return(*this);
}


ovStrArray & ovStrArray::operator = (const ovStrArray &array)
{
    int i;
    int z;


    this->Clean();

    _Alloc(z);

    this->n = array.n;
    this->m = array.m;


    for(i = 0; i < n; i++) {
        this->vArray[i].raw = array.vArray[i].raw;
        this->vArray[i].index = array.vArray[i].index;

        if (array.vArray[i].key != NULL)
            this->vArray[i].key = new ovStr(*array.vArray[i].key);

        if (array.vArray[i].value != NULL)
            this->vArray[i].value = new ovStr(*array.vArray[i].value);
    }

    return(*this);
}


int ovStrArray::Key(unsigned int index)
{
    int i;


    if (index < 0)
        return(-1);

    //if (index > n)
    //    return(-1);

    if (index < n)
        if (vArray[index].raw == vArray[index].index)
            return (vArray[index].raw);


    // FIXME This can be optimized... binary search ?
    for (i = 0; i < n; i++) {
        if (vArray[i].index == index)
            return (i);
    }

    return(-1);
}


int ovStrArray::Key(const char *key)
{
    int i;


    // FIXME This can be optimized... binary search ?
    for (i = 0; i < n; i++) {

        if (vArray[i].key == NULL)
            continue;

        if (vArray[i].key->Len() == 0)
            continue;

        if (*vArray[i].key == key)
            return (vArray[i].raw);
    }

    return(-1);
}


int ovStrArray::RawKeyInt(unsigned int index)
{


    if (index < 0)
        return(-1);

    if (index > n)
        return(-1);

    return (vArray[index].index);
}

ovStr ovStrArray::RawKey(unsigned int index)
{
    ovStr ret;

    if (index < 0)
        return("");

    if (index > n)
        return("");

    if (vArray[index].index > -1)
        ret.printf("%d", vArray[index].index);
        return (ret);

    return (vArray[index].index);
}


ovStr ovStrArray::Value(unsigned int index)
{
    int i;

    if (Count() == 0)
        return("");

    if (index < 0)
        return("");

    //if (index > n)
    //    return("");

    if (index < n)
        if (vArray[index].raw == vArray[index].index)
            return (*vArray[index].value);

    // FIXME This can be optimized... binary search ?
    for (i = 0; i < n; i++) {
        if (vArray[i].index == index)
            return (*vArray[i].value);
    }

    return("");
}


ovStr ovStrArray::Value(const char *key)
{
    int i;


    // FIXME This can be optimized... binary search ?
    for (i = 0; i < n; i++) {

        if (vArray[i].key == NULL)
            continue;

        if (vArray[i].key->Len() == 0)
            continue;

        if (*vArray[i].key == key)
            return (*vArray[i].value);
    }

    return("");
}


ovStr ovStrArray::RawValue(unsigned int index)
{


    if (index < 0)
        return("");

    if (index > n)
        return("");

    return (*vArray[index].value);
}


ovStr ovStrArray::operator [](unsigned int index)
{
    return(Value(index));
}


ovStr ovStrArray::operator [](const char *key)
{
    return(Value(key));
}


//misc
void ovStrArray::ReadFile(ovStr file)
{
    int i, read;
    char *c;

    char buff[1025];
    ovStr s;

    FILE *f;


    Clean();

    if ((f = fopen(file, "r")) == NULL)
        return;

    s = "";

    while (!feof(f)) {

        read = fread(buff, 1, 1024, f);

        c = buff;

        for (i = 0; i < read; i++) {
            if (*c == '\n') {
                s.replace("\r", "");
                Add(s);

                s = "";
            }
            else {
                s.strcat(*c);
            }

            c++;
        }
    }

    if (s != "") {
        s.replace("\r", "");
        Add(s);
    }

    fclose(f);
}



ovStrArray ovStrArray::QSort()
{
    ovStrArray ret;

    ret = *this;

    quicksort(ret, 0, n - 1, n);

    return(ret);
}


void ovStrArray::quicksort(ovStrArray &array, int low, int high, int order)
{
    int bottom, top;
    ovStr pivot;
    ovStr temp;

    if (high > low)
    {
        pivot = array[high];
        bottom = low - 1;
        top = high;

        while(1)
        {
            while((array[++bottom] < pivot) && (bottom < order));
            while((array[--top] > pivot) && (top > 0));

            if (bottom >= top) break;

            temp = array[bottom];
            array.Store(array[top], bottom);
            array.Store(temp, top);
        }

        temp = array[bottom];
        array.Store(array[high], bottom);
        array.Store(temp, high);

        quicksort(array, low, bottom - 1, order);
        quicksort(array, bottom + 1, high, order);
    }
}
