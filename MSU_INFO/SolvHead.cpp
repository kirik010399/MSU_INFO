#include "SolvHead.hpp"
#include <math.h>
#include <iostream>
#include "MatFun.hpp"

using namespace std;

#define eps 1e-18

int solveSystem(double* a, double* b, double* x, int n, int *index){
    int i, j, k;
    double value;
    
    int maxstr, maxcol;
    
    for (i = 0; i < n; ++i)
        index[i] = i;
    
    for (i = 0; i < n; ++i){
        value = fabs(a[i*n+i]);
        maxstr = i;
        maxcol = i;
        
        for (j = i; j < n; ++j){
            for (k = i; k < n; ++k){
                if (fabs(a[j*n+k]) > value){
                    value = fabs(a[j*n+k]);
                    maxstr = j;
                    maxcol = k;
                }
            }
        }
        
        if (fabs(value) < eps){
            return -1;
        }
        
        if (maxstr != i){
            for (j = 0; j < n; ++j)
                swap(a[maxstr*n+j], a[i*n+j]);
            
            swap(b[maxstr], b[i]);
        }
        
        swap(index[i], index[maxcol]);
        
        if (maxcol != i){
            for (j = 0; j < n; ++j)
                swap(a[j*n+maxcol], a[j*n+i]);
        }
        
        value = 1.0/a[i*n+i];
        
        for (j = i; j < n; ++j)
            a[i*n+j] *= value;  //делим сразу всю строку
        
        b[i] *= value;
        
        for(j = 0; j < n; ++j){
            if (j != i){
                value = a[j*n+i];
                
                for(k = i; k < n; ++k)
                    a[j*n+k] -= value * a[i*n+k];
                
                b[j] -= value*b[i];
            }
        }
    }
    
    for (i = 0; i < n; ++i)
        x[index[i]] = b[i];
    
    return 0;
}

