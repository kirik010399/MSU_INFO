//
//  Params.h
//

#ifndef Params_h
#define Params_h

#include <stdio.h>

struct Params;

struct Params{
    int size;
    int l;
    int formula;
    int debug;
    char* fin;
    char* fout;
    float eps;
    int threadsCount; 
};


#endif /* Params_h */
