#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "matrixFunctions.h"
#include "solvingFunctions.h"
#include "Params.h"

int main(int argc, char** argv)
{
    int n, m;
    int opt;
    float eps;
    int functionNumber;
    double *matrix;
    double *result;
    double *cos, *sin;
    FILE* fin = NULL;
    FILE* fout = NULL;
    float residualFirst, residualSecond;
    
    struct timespec t1, t2;
    double t;
    struct Params params;
    
    params.formula = 1;
    params.fin = NULL;
    params.fout = NULL;
    params.size = 0;
    params.debug = 0;
    params.l = 4;
    params.eps = 1e-18;
    
    functionNumber = 0;
    
    int inputType;
    int returnFlag;
    
    while ((opt = getopt(argc, argv, "n:e:f:l:i:o:d")) != -1){
        switch (opt){
            case 'n': {
                sscanf(optarg, "%d", &params.size);
                break;
            }
            case 'f': {
                sscanf(optarg, "%d", &params.formula);
                break;
            }
            case 'l': {
                sscanf(optarg, "%d", &params.l);
                break;
            }
            case 'i': {
                params.fin = optarg;
                break;
            }
            case 'e': {
                sscanf(optarg, "%e", &params.eps);
                break;
            }
            case 'o': {
                params.fout = optarg;
                break;
            }
            case 'd': {
                params.debug = 1;
                break;
            }
        }
    }
    
    if (argc == 1){
        printf("Choose type of data:\n1 - from file, \n2 - from formula\n");
        
        if (scanf("%d", &inputType) != 1){
            printf("Data isn't correct\n");
            return -2;
        }
        
        if (inputType == 1){
            printf("Enter -i input.txt\n");
            printf("Enter extra parametrs:\n");
            printf("-l <int>  - size of printing\n");
            printf("-e {float}  - epsilon\n");
            printf("-o {string}  - printing to file\n");
            printf("-d <01>  - debug\n");
            return 0;
        }
        else if (inputType == 2){
            printf("Enter -n 100\n");
            printf("Enter extra parametrs:\n");
            printf("-f <012>  - choose formula\n");
            printf("-l <int>  - size of printing\n");
            printf("-e {float}  - epsilon\n");
            printf("-o {string}  - printing to file\n");
            printf("-d <01>  - debug\n");
            return 0;
        }
        else{
            printf("Data isn't correct\n");
            return -2;
        }
    }
    
    if (params.fin){
        inputType = 1;
    }
    else if (params.size > 0){
        inputType = 2;
    }
    else{
        printf("Data isn't correct\n");
        return -2;
    }
    
    if (inputType == 1){
        fin = fopen(params.fin, "r");
        
        if (!fin){
            printf("File doesn't exist");
            return -2;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0){
            printf("Data isn't correct\n");
            fclose(fin);
            return -2;
        }
    }
    else{
        if (params.formula < 0 || params.formula > 2){
            printf("Formula number isn't correct");
            return -2;
        }
        
        functionNumber = params.formula;
        n = params.size;
    }
    
    if (params.l < 1 || params.l > n){
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        return -2;
    }
    
    m = params.l;
    eps = params.eps;
    
    if (params.fout)
        fout = fopen(params.fout, "w");
    
    matrix = (double*)malloc(n*n * sizeof(double));
    result = (double*)malloc(n * sizeof(double));
    cos = (double*)malloc((n-1) * sizeof(double));
    sin = (double*)malloc((n-1) * sizeof(double));
    
    returnFlag = enterData(matrix, n, fin, functionNumber);
    
    if (returnFlag == -1){
        printf("Data isn't correct\n");

        if (inputType == 1)
            fclose(fin);
        
        if (fout)
            fclose(fout);
        
        free(matrix);
        free(result);
        free(cos);
        free(sin);

        return -2;
    }
    
    if (fout)
        fprintf(fout, "Matrix:\n");
    else
        printf("Matrix:\n");
    
    printMatrix(matrix, n, m, fout);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    calculateValues(matrix, result, cos, sin, n, eps, params.debug);
    clock_gettime(CLOCK_MONOTONIC, &t2);
    
    t =(t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec)/(1000000000.);
    
    if (returnFlag != -1){
        if (fout)
            fprintf(fout, "Result:\n");
        else
            printf("Result:\n");

        printResult(result, n, m, fout);
        
        if (inputType == 1){
            fseek(fin, 0, SEEK_SET);
            fscanf(fin, "%d", &n);
        }
        
        returnFlag = enterData(matrix, n, fin, functionNumber);
        
        residualNorm(matrix, result, &residualFirst, &residualSecond, n);
        
        if (fout)
            fprintf(fout, "\nResidual norm:\nFirst inv: %e\nSecond inv: %e\n", residualFirst, residualSecond);
        else
            printf("\nResidual norm:\nFirst inv: %e\nSecond inv: %e\n", residualFirst, residualSecond);
        
        if (fout)
            fprintf(fout, "Solving time =  %f milliseconds", t);
        else
            printf("Solving time =  %f milliseconds", t);
    }
    else{
        printf("Error while solving system\n");
        
        if (inputType == 1)
            fclose(fin);
        
        if (fout)
            fclose(fout);
        
        free(matrix);
        free(result);
        free(cos);
        free(sin);
        
        return -1;
    }
    
    if (inputType == 1)
        fclose(fin);
    
    if (fout)
        fclose(fout);
    
    free(matrix);
    free(result);
    free(cos);
    free(sin);
    
    return -2;
    
    return 0;
}
