#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrixUtils.h"
#include "calculatingManager.h"

int main()
{
    int n, m;
    double *matrix;
    double *vector;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    double eps;
    struct myPair p;
    
    printf("Choosy type of data:\n1 - from file, \n2 - from formula\n");

    if (scanf("%d", &inputType) != 1)
    {
        printf("Data isn't correct\n");
        return -2;
    }
         
    if (inputType == 1)
    {
        fin = fopen("input.txt", "r");
        
        if (!fin)
        {
            printf("File don't exist\n");
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0)
        {
            printf("Data isn't correct\n");
            fclose(fin);
            return -2;
        }
    }
    else if (inputType == 2)
    {
        printf("Enter size: \n");
    
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Data isn't correct\n");
            return -2;
        }
    }
    else
    {
        printf("Input type isn't correct\n");
        return -2;
    }
    
    matrix = (double*)malloc(n * n * sizeof(double));
    vector = (double*)malloc(n * sizeof(double));
    
    if (!(matrix && vector))
    {
        printf("No memory, enter matrix with less dimensions\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }

    returnFlag = enterMatrix(matrix, n, fin);
    
    if (returnFlag == -1)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }
    
    printf("Enter size of printing vector: ");
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }

    printf("Enter accuracy: \n");
    
    if (scanf("%lf", &eps) != 1 || eps <= 0)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }

    t = clock();
    calculateValues(matrix, vector, eps, n);
    t = clock() - t;
    
    printf("\nValues vector:\n");
    printVector(vector, n, m);
    
    if (inputType == 1)
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n);
    }
    
    returnFlag = enterMatrix(matrix, n, fin);
    p = residualNorm(matrix, vector, n);
    
    printf("\nThe norm of residual: in first inv: %lf, in second inv: %lf\n", p.inv1, p.inv2);
    
    printf("Calculating time =  %lu seconds\n", t/CLOCKS_PER_SEC);

    if (inputType == 1)
        fclose(fin);
    
    free(matrix);
    free(vector);
    
    return 0;
}
