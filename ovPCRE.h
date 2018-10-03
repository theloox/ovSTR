/***************************************************************************
 *   2005 by Axel Gonzalez                                                 *
 *   loox@e-shell.net                                                      *
 *                                                                         *
 *   This software is in the public domain. Permission to use, copy,       *
 *   modify, and distribute this software and its documentation for any    *
 *   purpose and without fee is hereby granted, without any conditions or  *
 *   restrictions. This software is provided "as is" without express or    *
 *   implied warranty.                                                     *
 *                                                                         *
 ***************************************************************************/

#include <ovStr/ovStr.h>
#include <ovStr/ovStrArray.h>

#include <pcre.h>

#ifndef _OVPCRE_H
#define _OVPCRE_H


#define MAX_VECTORS 384
#define MAX_VECTORS_2 768


class ovPCRE {

private:
    ovStr pattern;
    int flags;
    int options;

    const char *error;
    int erroffset;

    pcre *re;

    int ovector[MAX_VECTORS];
    int wspace[MAX_VECTORS_2];

public:

    ovPCRE();
    ovPCRE(ovStr p);
    ovPCRE(ovStr p, int f);
    ~ovPCRE();

    void SetPattern(ovStr p);

    int GetOptions();
    void SetOptions(int f);

    int Match(ovStr subject);
    int MatchAll(ovStr subject);
    int MatchAll(ovStr subject, ovStrArray &matches, unsigned int index=0);
    ovStr Replace();

    ovStr Error();
};

#endif
