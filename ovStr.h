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

#ifndef _OVSTR_H
#define _OVSTR_H


#ifndef OVSTR_MAX_LENGHT
#define OVSTR_MAX_LENGHT 1048000 
#endif

#ifndef OVSTR_ALLOC
#define OVSTR_ALLOC 128
#endif

#define MAX_SAME_CHARS 4

char SAME_CHARS[][MAX_SAME_CHARS] = {
                        { 'A', 'a', 'Á', 'á'},
                        { 'E', 'e', 'É', 'é'},
                        { 'I', 'i', 'í', 'í'},
                        { 'O', 'o', 'Ó', 'ó'},
                        { 'U', 'u', 'Ú', 'ú'},
};

class ovStr {
private:
    char *vStr;
    int vLen;
    int vAlloc;

    void Alloc(int n);
    void ReAlloc(int n);
    void Free();


public:
    ovStr();
    ovStr(ovStr &str);
    ovStr(const ovStr &str);
    ovStr(const char *str);
    ovStr(char c);
    ~ovStr();


    ovStr & Store(ovStr &str);
    ovStr & Store(const char *str);
    ovStr & Store(int n);
    ovStr & Store(double n);


    //char *xstr(ovStr str);
    int printf(ovStr str, ...);

    size_t Len();
    size_t Length();

    //case insensitive comparisson
    bool IsEqual(ovStr &str);
    bool IsEqual(const char *str);

    ovStr lower();
    ovStr upper();

    void trim();
    void ltrim();
    void rtrim();

    void strip_tags();
    void strip_sql();

    void strcat(ovStr &str);
    void strcat(char c);
    void strcat(const char *str,int n=OVSTR_MAX_LENGHT);

    ovStr substr(int start,int lenght = 0);

    void replace(const char search, ovStr &replace);
    void replace(const char search, const char *replace);
    void replace(ovStr &search, ovStr &replace);
    void replace(ovStr &search, const char *replace);
    void replace(const char *search, ovStr &replace);
    void replace(const char *search, const char *replace);

    int strpos(ovStr &tok, int start = 0);
    int strpos(const char *tok, int start = 0);
    int strpos(const char tok, int start = 0);

    int rstrpos(ovStr &tok, int start = 0);
    int rstrpos(const char *tok, int start = 0);
    int rstrpos(const char tok, int start = 0);

    ovStr strtokl(ovStr &tok);
    ovStr strtokl(const char *tok);
    ovStr strtokr(ovStr &tok);
    ovStr strtokr(const char *tok);
    ovStr rstrtokl(ovStr &tok);
    ovStr rstrtokl(const char *tok);
    ovStr rstrtokr(ovStr &tok);
    ovStr rstrtokr(const char *tok);

    int Int();
    double Double();


    ovStr & operator = (ovStr &str);
    ovStr & operator = (const char *str);
    ovStr & operator = (int n);
    ovStr & operator = (double n);

    ovStr operator + (ovStr &str);
    ovStr operator + (const char *str);
    ovStr operator += (ovStr &str);
    ovStr operator += (const char *str);


    //this are case insensitive!
    //for case sensitive use IsEqual()

    bool operator == (ovStr str);
    bool operator == (const char *str);
    bool operator != (ovStr str);
    bool operator != (const char *str);

    bool operator > (ovStr str);
    bool operator > (const char *str);

    bool operator < (ovStr str);
    bool operator < (const char *str);

    operator char *();

    void ReadFile(ovStr file);

};


//auxiliar functions
int strnlen(const char *s,int n=OVSTR_MAX_LENGHT);
inline bool samechar(char s, char d);


#endif

