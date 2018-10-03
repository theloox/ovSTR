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

#include "ovPCRE.h"

ovPCRE::ovPCRE()
{
    pattern = "*";
    flags = 0;
    options = 0;

    error = NULL;
    erroffset = 0;


    re = NULL;

    re = pcre_compile(pattern, flags, &error, &erroffset, NULL);
}

ovPCRE::ovPCRE(ovStr p)
{
    pattern = p;
    flags = 0;
    options = 0;

    error = NULL;
    erroffset = 0;


    re = NULL;

    re = pcre_compile(pattern, flags, &error, &erroffset, NULL);
}


ovPCRE::ovPCRE(ovStr p, int f)
{
    pattern = p;
    flags = PCRE_CASELESS;
    options = 0;

    error = NULL;
    erroffset = 0;


    re = NULL;

    re = pcre_compile(pattern, flags, &error, &erroffset, NULL);
}



ovPCRE::~ovPCRE()
{
    if (re != NULL)
        pcre_free(re);
}


void ovPCRE::SetPattern(ovStr p)
{
    pattern = p;
    flags = 0;

    if (re != NULL)
        pcre_free(re);

    re = pcre_compile(pattern, flags, &error, &erroffset, NULL);
}


int ovPCRE::GetOptions()
{
    return(this->flags);
}


void ovPCRE::SetOptions(int f)
{
    this->flags = f;
}


int ovPCRE::Match(ovStr subject)
{
    int rc;

    if (re == NULL)
        return(0);

    rc = pcre_exec(re, NULL, subject, subject.Len(), 0, this->options, ovector, MAX_VECTORS);

    if (rc < 0)
        return(0);


    return(ovector[0] + 1);

}


int ovPCRE::MatchAll(ovStr subject, ovStrArray &matches, unsigned int index)
{
    int i;
    int count, rc;
    int offset;
    const char **listptr;
    ovStr str;

    i = 0;
    offset = 0;

    if (index < 0)
        index = 0;

    matches.Clean();

    while ((count = pcre_exec(re, NULL, subject, subject.Len(), offset, options, ovector, MAX_VECTORS)) > 0) {

        rc = pcre_get_substring_list(subject, ovector, count, &listptr);

        if (rc < 0)
            return(0);

        str = listptr[0];

        offset = subject.strpos(str, offset) + str.Len();


        str = listptr[index < count ? index : (count - 1)];

        matches.Add(str);

        pcre_free_substring_list(listptr);

        i++;

    }

    //printf("COunt: %d\n", count);

    return(i);
}


ovStr ovPCRE::Replace()
{
}


ovStr ovPCRE::Error()
{
    if (error == NULL)
        return("");
    else
        return(error);
}
