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
 
 
 
#include "ovStr.h"

#ifdef WINDOWS
#define NO_VASPRINTF
#endif

ovStr::ovStr()
{
    vAlloc = 0;

    Alloc(0);
    *vStr = '\0';
    vLen = 0;
}


ovStr::ovStr(ovStr &str)
{
    vAlloc = 0;
    vLen = str.vLen;

    Alloc(vLen);

    memcpy(vStr,str.vStr,vLen + 1);
}


ovStr::ovStr(const ovStr &str)
{
    vAlloc = 0;
    vLen = str.vLen;

    Alloc(vLen);

    memcpy(vStr,str.vStr,vLen + 1);
}


ovStr::ovStr(const char *str)
{

    vAlloc = 0;
    vLen = strlen(str);

    Alloc(vLen);

    memcpy(vStr,str,vLen);

    vStr[vLen] = '\0';
}


ovStr::ovStr(char c)
{

    vAlloc = 0;
    vLen = 1;

    Alloc(vLen);

    vStr[0] = c;

    vStr[vLen] = '\0';
}


ovStr::~ovStr()
{
    Free();
}


void ovStr::Alloc(int n)
{
    if (vAlloc != 0)
    {
        ReAlloc(n);
        return;
    }

    vAlloc = ((n + 1) % OVSTR_ALLOC ? n + ((OVSTR_ALLOC + 1) - ((n + 1) % OVSTR_ALLOC)) : n + 1);

    vStr = (char *)calloc(vAlloc,sizeof(char));

    vStr[n] = '\0';
    vStr[vAlloc - 1] = '\0';
}


void ovStr::ReAlloc(int n)
{
    int t;

    t = ((n + 1) % OVSTR_ALLOC ? n + ((OVSTR_ALLOC + 1) - ((n + 1) % OVSTR_ALLOC)) : n + 1);

    if (t == vAlloc)
        return;
    else
        vAlloc = t;

    vStr = (char *)realloc(vStr,vAlloc);

    vStr[n] = '\0';
    vStr[vAlloc - 1] = '\0';
}


void ovStr::Free()
{
    if (vAlloc != 0)
    {
        free(vStr);

        vAlloc = 0;
        vLen = 0;
        vStr = NULL;
    }
}


ovStr & ovStr::Store(ovStr &str)
{
    Free();

    vLen = str.vLen;

    Alloc(vLen + 1);
    //vStr = (char *)calloc(vLen + 1,sizeof(char));

    memcpy(vStr,str.vStr,vLen + 1);


    return(*this);
}

ovStr & ovStr::Store(const char *str)
{
    Free();

    vLen = strlen(str);

    Alloc(vLen + 1);
    //vStr = (char *)calloc(vLen + 1,sizeof(char));

    memcpy(vStr,str,vLen);
    vStr[vLen] = '\0';


    return(*this);
}

ovStr & ovStr::Store(int n)
{
    char t[32];


    Free();

    snprintf(t, 32, "%d", n);

    vLen = strlen(t);

    Alloc(vLen + 1);
    //vStr = (char *)calloc(vLen + 1,sizeof(char));

    memcpy(vStr,t,vLen + 1);


    return(*this);
}

ovStr & ovStr::Store(double n)
{
    char t[32];


    Free();

    snprintf(t, 32, "%f", n);

    vLen = strlen(t);

    Alloc(vLen + 1);
    //vStr = (char *)calloc(vLen + 1,sizeof(char));

    memcpy(vStr,t,vLen + 1);


    return(*this);
}


#ifdef NO_VASPRINTF
//XXX fucking ugly patch
char _vsn_buffer[1048576];

int ovStr::printf(ovStr str, ...)
{
    char *s;
    int l;

    s = _vsn_buffer;

    va_list argptr;
    va_start(argptr, str);

    l = vsnprintf(s, 1048576, (const char *)str, argptr);

    va_end(argptr);

    l = (l < 0 ? 0 : l);

    this->Free();

    this->Alloc(l);

    vLen = l;

    memcpy(vStr,s,vLen);

    return l;
}

#else

int ovStr::printf(ovStr str, ...)
{
    char *s;
    int l;

    va_list argptr;
    va_start(argptr, str);

    l = vasprintf(&s, (const char *)str, argptr);

    va_end(argptr);

    this->Free();

    this->Alloc(l);

    vLen = l;

    memcpy(vStr,s,vLen);

    free(s);

    return l;
}

#endif

size_t ovStr::Len()
{
    return(vLen);
}

size_t ovStr::Length()
{
    return(vLen);
}

bool ovStr::IsEqual(ovStr &str)
{
    if (vLen != str.vLen)
        return(false);

    if (strncmp(vStr,str.vStr,vLen))
        return(false);

    return(true);
}

bool ovStr::IsEqual(const char *str)
{
    int l;

    l = strlen(str);

    if (vLen != l)
        return(false);

    if (strncmp(vStr,str,vLen))
        return(false);

    return(true);
}

ovStr ovStr::lower()
{
    ovStr r;
    char *d;
    int i;

    r = *this;

    d = r.vStr;

    for (i = 0; i < vLen; i++)
    {
        if (*d > 'A' && *d < 'Z')
            *d = *d + 32;

        if (*d == '[')
            *d = '{';

        if (*d == ']')
            *d = '}';

        if (*d == '\\')
            *d = '|';

        d++;
    }

    return(r);
}

ovStr ovStr::upper()
{
    ovStr r;
    char *d;
    int i;

    r = *this;

    d = r.vStr;

    for (i = 0; i < vLen; i++)
    {
        if (*d > 'a' && *d < 'z')
            *d = *d - 32;

        if (*d == '{')
            *d = '[';

        if (*d == '}')
            *d = ']';

        if (*d == '|')
            *d = '\\';

        d++;
    }

    return(r);

}


void ovStr::trim()
{
    ovStr r;
    char *d;
    int start,end;

    if(vLen <= 0)
       return;

    d = vStr;

    for (start = 0; start < vLen; start++)
    {
        if (*d != ' ' && *d != '\t' && *d != -96)
            break;
        d++;
    }


    d = vStr + (vLen - 1);


    for (end = vLen - 1; end >= 0; end--)
    {
        if (*d != ' ' && *d != '\t' && *d != -96)
        {
            break;
        }
        d--;
    }

    *this = substr(start, end - start + 1);
}

void ovStr::ltrim()
{
    char *d;
    int start;

    if(vLen <= 0)
       return;

    d = vStr;

    for (start = 0; start < vLen; start++)
    {
        if (*d != ' ' && *d != '\t' && *d != -96)
            break;
        d++;
    }

    *this = substr(start);
}


void ovStr::rtrim()
{
    ovStr r;
    char *d;
    int end;

    if(vLen <= 0)
       return;


    d = vStr + vLen - 1;

    for (end = vLen - 1; end >= 0; end--)
    {
        if (*d != ' ' && *d != '\t' && *d != -96)
            break;
        d--;
    }

    *this = substr(0, end + 1);
}

void ovStr::strip_tags()
{

    char *s;
    char chr;
    ovStr r;

    int i;


    s = this->vStr;

    chr = '\0';

    for (i = 0; i < this->vLen; i++) {

        if (chr == '\0' && *s == '<') {
            chr = '>';
        }
        else if (chr == '>' && *s == '"') {
            chr = '"';
        }
        else if (chr == '\"' && *s == '\"') {
            chr = '>';
        }
        else if (chr == '>' && *s == '>') {
            chr = '\0';
        }
        else if (chr != '\0') {
            s++;
            continue;
        }
        else {

            r.strcat(*s);
        }
        s++;
    }

    *this = r;
}

void ovStr::strip_sql()
{
    replace("'","");
    replace("\"","");
    replace("\\","");
}


void ovStr::strcat(ovStr &str)
{
    int i,l;
    char *d,*s;

    i = 0;

    l = str.Len();

    ReAlloc(vLen + l + 1);
    //vStr = (char *)realloc(vStr,(vLen + l + 1));


    s = str.vStr;
    d = vStr;

    d += vLen;


    while (i < l)
    {
        *(d++) = *(s++);
        vLen++;
        i++;
    }

    *d = '\0';

    return;
}

void ovStr::strcat(char c)
{
    char *d;



    ReAlloc(vLen + 1);

    d = this->vStr;

    d += vLen++;

    *(d++) = c;
    *d = '\0';

    return;
}

void ovStr::strcat(const char *str,int n)
{

    int i,l;
    char *d,*s;


    i = 0;


    l = strnlen(str, n);

    ReAlloc(vLen + l + 1);
    //vStr = (char *)realloc(vStr,(vLen + l + 1));


    s = (char *)str;
    d = vStr;

    d += vLen;

    while (i < l)
    {
        *(d++) = *(s++);
        vLen++;
        i++;
    }

    *d = '\0';

    return;

}


ovStr ovStr::substr(int start, int lenght)
{
    ovStr r;
    char *c;

    int s,t;
    int i;

    c = vStr;

    //r = "";

    if (start > vLen)
        return(r);

    if (start < 0)
    {
        if (-start > vLen)
            return(r);

        s = vLen + start;
    }
    else
        s = start;

    c += s;


    if (lenght == 0)
        t = vLen - s;
    else if (lenght < 0)
        t = vLen - s + lenght;
    else
        t = lenght;

    if (t > vLen - s)
        t = vLen - s;


    for (i = 0; i < t; i++)
        r.strcat(*c++);

    return(r);
}


void ovStr::replace(const char search, ovStr &replace)
{
    ovStr r,s;

    int t;
    int l;

    ovStr str;

    str.printf("%c", search);


    l = 1;

    r = *this;

    t = 0;

    while ((t = r.strpos(str, t)) > -1)
    {

        if (t > 0)
            s = r.substr(0,t);
        else
            s = "";

        s += replace;
        s += r.substr(t + l);

        r = s;

        t += str.Len();
    }

    *this = r;
}


void ovStr::replace(const char search, const char *replace)
{
    ovStr r,s;

    int t;
    int l, lr;

    ovStr str;

    str.printf("%c", search);


    l = 1;
    lr = strlen(replace);

    r = *this;

    t = 0;

    while ((t = r.strpos(str, t)) > -1)
    {

        if (t > 0)
            s = r.substr(0,t);
        else
            s = "";

        s += replace;
        s += r.substr(t + l);

        r = s;

        t += lr;
    }

    *this = r;
}


void ovStr::replace(ovStr &search, ovStr &replace)
{
    ovStr r,s;

    int t;
    int l;


    l = search.Len();

    r = *this;

    t = 0;

    while ((t = r.strpos(search, t)) > -1)
    {

        if (t > 0)
            s = r.substr(0,t);
        else
            s = "";

        s += replace;
        s += r.substr(t + l);

        r = s;

        t += search.Len();
    }

    *this = r;
}


void ovStr::replace(ovStr &search, const char *replace)
{
    ovStr r,s;

    int t;
    int l, lr;


    l = search.Len();
    lr = strlen(replace);

    r = *this;

    t = 0;

    while ((t = r.strpos(search, t)) > -1)
    {

        if (t > 0)
            s = r.substr(0,t);
        else
            s = "";

        s += replace;
        s += r.substr(t + l);

        r = s;

        t += lr;
    }

    *this = r;
}

void ovStr::replace(const char *search, const char *replace)
{
    ovStr r,s;

    int t;
    int l, lr;


    l = strlen(search);
    lr = strlen(replace);

    r = *this;

    t = 0;

    while ((t = r.strpos(search, t)) > -1)
    {

        if (t > 0)
            s = r.substr(0,t);
        else
            s = "";

        s += replace;
        s += r.substr(t + l);

        r = s;

        t += lr;
    }

    *this = r;
}


int ovStr::strpos(ovStr &tok,int start)
{
    char *sb,*s,*d;
    int l;
    int i,j,t;
    int r = -1;

    int end;

    l = tok.Len();

    if (l <= 0)
        return(r);

    if (tok == "")
        return(r);

    if (l > vLen)
        return(r);

    if (start < 0 || (start + l) > vLen)
        return(r);

    t = start;
    sb = vStr + start;

    end = vLen - start - l + 1;


    for (i = 0; i < end; i++)
    {
        s = sb;
        d = tok.vStr;

        for (j = 0; j < l; j++)
        {
            if (*s++ != *d++)
                break;
        }

        if (j == l)
        {
            r = t;
            break;
        }

        sb++;
        t++;
    }

    return(r);
}

int ovStr::strpos(const char *tok,int start)
{
    char *sb,*s,*d;
    int l;
    int i,j,t;
    int r = -1;

    int end;


    l = strlen(tok);

    if (l <= 0)
        return(r);

    if (tok == "")
        return(r);

    if (l > vLen)
        return(r);

    if (start < 0 || (start + l) > vLen)
        return(r);

    t = start;
    sb = vStr + start;

    end = vLen - start - l + 1;


    for (i = 0; i < end; i++)
    {
        s = sb;
        d = (char *)tok;

        for (j = 0; j < l; j++)
        {
            if (*s++ != *d++)
                break;
        }

        if (j == l)
        {
            r = t;
            break;
        }

        sb++;
        t++;
    }

    return(r);
}


int ovStr::strpos(const char tok,int start)
{
    char *sb;
    int l;
    int i;
    int r = -1;

    int end;


    l = 1;

    if (tok == '\0')
        return(r);

    if (l > vLen)
        return(r);

    if (start < 0 || (start + l) > vLen)
        return(r);

    sb = vStr + start;

    end = vLen - start - l + 1;


    for (i = 0; i < end; i++)
    {
        if (*sb == tok)
        {
            r = i;
            break;
        }

        sb++;
    }

    return(r);
}


int ovStr::rstrpos(ovStr &tok,int start)
{
    char *sb,*s,*d;
    int l;
    int i,j,t;
    int r = -1;

    int end;


    l = tok.Len();

    if (l <= 0)
        return(r);

    if (tok == "")
        return(r);

    if (l > vLen)
        return(r);

    if (start < 0 || (start + l) > vLen)
        return(r);

    end = vLen - start - l + 1;

    t = end;
    sb = vStr + end;



    for (i = end; i >= 0; i--)
    {
        s = sb;
        d = tok.vStr;

        for (j = 0; j < l; j++)
        {
            if (*s++ != *d++)
                break;
        }

        if (j == l)
        {
            r = t;
            break;
        }

        sb--;
        t--;
    }

    return(r);
}

int ovStr::rstrpos(const char *tok,int start)
{
    char *sb,*s,*d;
    int l;
    int i,j,t;
    int r = -1;

    int end;

    l = strlen(tok);

    if (l <= 0)
        return(r);

    if (tok == "")
        return(r);

    if (l > vLen)
        return(r);

    if (start < 0 || (start + l) > vLen)
        return(r);

    end = vLen - l + 1;

    t = end;
    sb = vStr + end;


    for (i = end; i >= 0; i--)
    {
        s = sb;
        d = (char *)tok;

        for (j = 0; j < l; j++)
        {
            if (*s++ != *d++)
                break;
        }

        if (j == l)
        {
            r = t;
            break;
        }

        sb--;
        t--;
    }

    return(r);
}


int ovStr::rstrpos(const char tok,int start)
{
    char *sb;
    int l;
    int i;
    int r = -1;

    int end;

    l = 1;

    if (tok == '\0')
        return(r);

    if (l > vLen)
        return(r);

    if (start < 0 || (start + l) > vLen)
        return(r);

    end = vLen - l + 1;

    sb = vStr + end;


    for (i = end; i >= 0; i--)
    {
        if (*sb == tok)
        {
            r = i;
            break;
        }

        sb--;
    }

    return(r);
}


ovStr ovStr::strtokl(ovStr &tok)
{
    ovStr r;
    int t;

    t = this->strpos(tok);

    if (t < 0)
        r = *this;
    else if (t == 0)
        r = "";
    else
        r = this->substr(0,t);

    return(r);
}

ovStr ovStr::strtokl(const char *tok)
{
    ovStr r;
    int t;

    t = this->strpos(tok);

    if (t < 0)
        r = *this;
    else if (t == 0)
        r = "";
    else
        r = this->substr(0,t);

    return(r);
}

ovStr ovStr::strtokr(ovStr &tok)
{
    ovStr r;
    int t;

    t = this->strpos(tok);

    if (t < 0)
        r = "";
    else
        r = this->substr(t + tok.Len());

    return(r);
}

ovStr ovStr::strtokr(const char *tok)
{
    ovStr r;
    int t;

    t = this->strpos(tok);

    if (t < 0)
        r = "";
    else
        r = this->substr(t + strlen(tok));

    return(r);
}



ovStr ovStr::rstrtokl(ovStr &tok)
{
    ovStr r;
    int t;

    t = this->rstrpos(tok);

    if (t < 0)
        r = *this;
    else if (t == 0)
        r = "";
    else
        r = this->substr(0,t);

    return(r);
}

ovStr ovStr::rstrtokl(const char *tok)
{
    ovStr r;
    int t;

    t = this->rstrpos(tok);

    if (t < 0)
        r = *this;
    else if (t == 0)
        r = "";
    else
        r = this->substr(0,t);

    return(r);
}

ovStr ovStr::rstrtokr(ovStr &tok)
{
    ovStr r;
    int t;

    t = this->rstrpos(tok);

    if (t < 0)
        r = "";
    else
        r = this->substr(t + tok.Len());

    return(r);
}

ovStr ovStr::rstrtokr(const char *tok)
{
    ovStr r;
    int t;

    t = this->rstrpos(tok);

    if (t < 0)
        r = "";
    else
        r = this->substr(t + strlen(tok));

    return(r);
}


int ovStr::Int()
{
    return(atoi(vStr));
}


double ovStr::Double()
{
    return(atof(vStr));
}



// operators

ovStr & ovStr::operator =(ovStr &str)
{
    return(Store(str));
}

ovStr & ovStr::operator =(const char *str)
{
    return(Store(str));
}

ovStr & ovStr::operator =(int n)
{
    return(Store(n));
}

ovStr & ovStr::operator =(double n)
{
    return(Store(n));
}

ovStr ovStr::operator +(ovStr &str)
{
    ovStr r;
    r = *this;
    r.strcat(str);

    return(r);
}

ovStr ovStr::operator +(const char *str)
{
    ovStr r;
    r = *this;
    r.strcat(str);

    return(r);
}

ovStr ovStr::operator +=(ovStr &str)
{
    this->strcat(str);

    return(*this);
}

ovStr ovStr::operator +=(const char *str)
{
    this->strcat(str);

    return(*this);
}


bool ovStr::operator ==(ovStr str)
{
    char *d,*s;
    int i;
    bool r = true;

    if (vLen != str.vLen)
        return(false);

    s = str.vStr;
    d = vStr;

    for (i = 0; i < vLen; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        r = false;

        break;
    }

    return(r);
}

bool ovStr::operator ==(const char *str)
{
    char *d,*s;
    int i,l;
    bool r = true;

    l = strlen(str);

    if (vLen != l)
        return(false);

    s = (char *)str;
    d = vStr;

    for (i = 0; i < vLen; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        r = false;

        break;
    }

    return(r);
}


bool ovStr::operator >(ovStr str)
{
    char *d,*s;
    int i;
    bool r = false;
    int tl;

    tl = (vLen < str.vLen ? vLen : str.vLen);

    s = str.vStr;
    d = vStr;

    for (i = 0; i < tl; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        if (*d > *s)
            r = true;

        break;
    }

    return(r);
}


bool ovStr::operator >(const char *str)
{
    char *d,*s;
    int i,l;
    bool r = false;
    int tl;

    l = strlen(str);

    tl = (vLen < l ? vLen : l);

    s = (char *)str;
    d = vStr;

    for (i = 0; i < tl; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        if (*d > *s)
            r = true;

        break;
    }

    return(r);
}


bool ovStr::operator <(ovStr str)
{
    char *d,*s;
    int i;
    bool r = false;
    int tl;

    tl = (vLen < str.vLen ? vLen : str.vLen);

    s = str.vStr;
    d = vStr;

    for (i = 0; i < tl; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        if (*d < *s)
            r = true;

        break;
    }

    return(r);
}

bool ovStr::operator <(const char *str)
{
    char *d,*s;
    int i,l;
    bool r = false;
    int tl;

    l = strlen(str);

    tl = (vLen < l ? vLen : l);

    s = (char *)str;
    d = vStr;

    for (i = 0; i < tl; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        if (*d < *s)
            r = true;

        break;
    }

    return(r);
}


bool ovStr::operator !=(ovStr str)
{
    char *d,*s;
    int i;
    bool r = false;

    if (vLen != str.vLen)
        return(true);

    s = str.vStr;
    d = vStr;

    for (i = 0; i < vLen; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        r = true;

        break;
    }

    return(r);
}

bool ovStr::operator !=(const char *str)
{
    char *d,*s;
    int i,l;
    bool r = false;

    l = strlen(str);

    if (vLen != l)
        return(true);

    s = (char *)str;
    d = vStr;

    for (i = 0; i < vLen; i++)
    {
        if (i)
        {
            s++;
            d++;
        }

        if (samechar(*d, *s))
            continue;

        r = true;

        break;
    }

    return(r);
}


ovStr::operator char *()
{
    return(vStr);
}


//misc
void ovStr::ReadFile(ovStr file)
{
    int i, read;
    char *c;

    char buff[1025];
    ovStr s;

    FILE *f;


    if ((f = fopen(file, "r")) == NULL)
        return;

    s = "";

    while (!feof(f)) {

        read = fread(buff, 1, 1024, f);

        c = buff;

        for (i = 0; i < read; i++) {
            if (*c == '\0') {
                break;
            }
            else {
                s.strcat(*c);
            }

            c++;
        }
    }

    fclose(f);
}


//auxiliar functions
int strnlen(const char *s,int n)
{
    int r;
    char *p;

    r = 0;
    p = (char *)s;

    while(r < n)
    {
        if (*p == '\0')
            break;
        p++;
	r++;
    }
    return(r);
}

/*
inline bool samechar(char s, char d)
{
    if (s == d)
        return (true);

    if ((s >= 'a' && s <= 'z') && (d == ((s) - 32)))
        return(true);

    if ((s >= 'A' && s <= 'Z') && (d == ((s) + 32)))
        return(true);

    if (s == '[' && d == '{')
        return(true);

    if (s == ']' && d == '}')
        return(true);

    if (s == '\\' && d == '|')
        return(true);

    if (s == '{' && d == '[')
        return(true);

    if (s == '}' && d == ']')
        return(true);

    if (s == '|' && d == '\\')
        return(true);

    return(false);
}
*/

inline bool samechar(char s, char d)
{
    unsigned int i,j,k;


    if (s == d)
        return (true);

    if ((s >= 'a' && s <= 'z') && (d == ((s) - 32)))
        return(true);

    if ((s >= 'A' && s <= 'Z') && (d == ((s) + 32)))
        return(true);

    for (i = 0; i < sizeof(SAME_CHARS); i++) {
        for (j = 0; j < MAX_SAME_CHARS; j++) {
            if (s == SAME_CHARS[i][j]) {
                for (k = 0; k < MAX_SAME_CHARS; k++) {
                    if (k != j && d == SAME_CHARS[i][k])
                        return(true);
                }
            }
        }
    }

    return(false);
}
