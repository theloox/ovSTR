/***************************************************************************
 *   2008 by Axel Gonzalez                                                 *
 *   loox@e-shell.net                                                      *
 *                                                                         *
 *   This software is in the public domain. Permission to use, copy,       *
 *   modify, and distribute this software and its documentation for any    *
 *   purpose and without fee is hereby granted, without any conditions or  *
 *   restrictions. This software is provided "as is" without express or    *
 *   implied warranty.                                                     *
 *                                                                         *
 ***************************************************************************/


#include "ovPHP.h"

int count(ovStrArray arr)
{
    return(arr.Count());
}

int max(int x, int y)
{
    return(x > y ? x : y);
}

ovStr str_replace(ovStr search, ovStr replace, ovStr str, int count)
{
    str.replace(search, replace);
    return(str);
}

int strlen(ovStr str)
{
    return(str.strlen());
}

int strpos(ovStr str, ovStr tok, int start = 0);
{
    return(str.strpos(tok, start));
}

int strrpos(ovStr str, ovStr tok, int start = 0);
{
    return(str.rstrpos(tok, start));
}

ovStr strtolower(ovStr str)
{
    return(str.lower);
}

ovStr substr(ovStr str, int start,int lenght = 0)
{
    return(str.substr(start, lenght));
}

ovStr substr_replace(ovStr str, ovStr replace, int start, int length)
{
    FIXME
    ovStr x;
    if (start != 0)
        x.strcat(str.substr(0, start - 1);
    x.strcat(replace);
    x.strcat(str.substr(0, start - 1);
    if (length != 0)
        x.substr(start + length);
    return(x);
}

ovStr trim(ovStr str)
{
    return(str.trim());
}
