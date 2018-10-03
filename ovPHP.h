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


#ifndef _OVPHP_H
#define _OVPHP_H

int count(ovStrArray arr);

void echo(ovStr str, ...);

ovStr htmlentities(ovStr str);

int max(int x, int y);


// string

ovStr str_replace(ovStr search, ovStr replace, ovStr &str, int length = -1);

int strlen(ovStr str);

int strpos(ovStr str, ovStr tok, int start = 0);

int strrpos(ovStr str, ovStr tok, int start = 0);

ovStr strtolower(ovStr str);

ovStr substr(ovStr str, int start,int lenght = 0);

ovStr substr_replace(ovStr str, ovStr replace, int start, int length = 0);

ovStr trim(ovStr str);


#endif
