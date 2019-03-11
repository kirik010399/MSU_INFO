//
//  Params.h
//

#ifndef Params_h
#define Params_h

#include <stdio.h>

struct Params;

struct Params
{
    int size;
    int l;
    int formula;
    int verbose;
    char* fin;
    char* fout;
    float eps;
};


#endif /* Params_h */
