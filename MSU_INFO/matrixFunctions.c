#include "matrixFunctions.h"
#include <stdio.h>
#include <math.h>

double func0(int i, int j, int n){
    return i+j == n-1 ?1 :0;
}

double func1(int i, int j, int n){
    n = n;
    return 1.0/(1.0+i+j);
}

double func2(int i, int j, int n){
    n = n;
    return fabs((i-j)*1.0);
}

int enterData(double* matrix, double *vector, int n, FILE* fin, int functionNumber){
    int i, j;
    
    if (fin){
        for (i = 0; i < n; ++i){
            for (j = 0; j < n; ++j){
                if (fscanf(fin, "%lf", &matrix[i*n+j]) != 1)
                    return -1;
            }
            
            if (fscanf(fin, "%lf", &vector[i]) != 1)
                return -1;
        }
    }
    else{
        for (i = 0; i < n; ++i){
            vector[i] = 0;
            
            for (j = 0; j < n; ++j){
                
                switch(functionNumber){
                    case 0: {
                        matrix[i*n+j] = func0(i, j, n);
                        break;
                    }
                    case 1: {
                        matrix[i*n+j] = func1(i, j, n);
                        break;
                    }
                    case 2: {
                        matrix[i*n+j] = func2(i, j, n);
                        break;
                    }
                }
                
                if (j % 2 == 0)
                    vector[i] += matrix[i*n+j];
            }
        }
    }
    
    return 0;
}

void printResult(double* result, int n, int m, FILE *fout)
{
    int i;
    int min_ = fmin(n,m);
    
    if (fout){
        for (i = 0; i < min_; ++i)
            fprintf(fout, "%f ", result[i]);
        if (min_ < n-1)
            fprintf(fout, "... ");
        if (min_ != n)
             fprintf(fout, "%f ", result[n-1]);
    }
    else{
        for (i = 0; i < min_; ++i)
            printf("%f ", result[i]);
        if (min_ < n-1)
            printf("... ");
        if (min_ != n)
            printf("%f ", result[n-1]);
    }
}

void printMatrix(double *matrix, int n, int m, FILE *fout){
    int i, j;
    int min_ = fmin(n,m);

    if(fout){
        for(i = 0; i < min_; ++i){
            for(j = 0; j < min_; ++j){
                fprintf(fout,"%f ", matrix[i*n+j]);
            }
            
            if (min_ < n-1)
                fprintf(fout,"... ");
            if (min_ != n)
                fprintf(fout, "%f ", matrix[i*n+n-1]);
            
            fprintf(fout,"\n");
        }
        
        if (min_ < n-1){
            fprintf(fout, "... ");
            fprintf(fout, "\n");
        }
        
        if (min_ != n){
            for(j = 0; j < min_; j++){
                fprintf(fout, "%f ", matrix[(n-1)*n+j]);
            }
        }
        
        if (min_ < n-1)
            fprintf(fout,"... ");
        
        if (min_ != n)
            fprintf(fout,"%f\n",matrix[(n-1)*n+n-1]);
    }
    else
    {
        for(i = 0; i < min_; ++i){
            for(j = 0; j < min_; ++j){
                printf("%f ", matrix[i*n+j]);
            }
            
            if (min_ < n-1)
                printf("... ");
            if (min_ != n)
                printf("%f ", matrix[i*n+n-1]);
            
            printf("\n");
        }
        
        if (min_ < n-1){
            printf("... ");
            printf("\n");
        }
        
        if (min_ != n){
            for(j = 0; j < min_; j++){
                printf("%f ", matrix[(n-1)*n+j]);
            }
        }
        
        if (min_ < n-1)
            printf("... ");
        
        if (min_ != n)
            printf("%f\n",matrix[(n-1)*n+n-1]);
    }
}

float residualNorm(double* matrix, double* vector, double* result, int n){
    int i, j;
    float res = 0;
    double a;
    
    for (i = 0; i < n; ++i){
        a = 0.0;
        
        for (j = 0; j < n; ++j)
            a += matrix[i*n+j] * result[j];
        
        a -= vector[i];
        
        res += a*a;
    }
    
    return sqrt(res);
}

float errorNorm(double *result, int n){
    float error = 0;
    int i;
    
    for (i = 0; i < n; ++i)
    {
        if (i % 2)
            error += result[i]*result[i];
        else
            error += (result[i]-1)*(result[i]-1);
    }
    
    return sqrt(error);
}
