#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrixUtils.h"
#include "invertingManager.h"

int main(void)
{
    int n, m;
    double *matrix;
    double *inverseMatrix;
    double *d;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    
    printf("Choose type of entering data: 1 - from file, 2 - from formula\n");
    
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
        printf("Enter size: ");
    
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
    
    matrix = (double*)malloc((n*n) * sizeof(double));
    inverseMatrix = (double*)malloc((n*n) * sizeof(double));
    d = (double*)malloc((n) * sizeof(double));
    
    if (!(matrix && inverseMatrix && d))
    {
        printf("No memory, enter matrix with less dimensions\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(inverseMatrix);
        free(d);
        
        return -2;
    }

    returnFlag = enterMatrix(matrix, n, fin);
    
    if (returnFlag == -1)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(inverseMatrix);
        free(d);
        
        return -2;
    }
    
    printf("Enter size of printing matrix: ");
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(inverseMatrix);
        free(d);
        
        return -2;
    }
    
    t = clock();
    returnFlag = invertMatrix(matrix, inverseMatrix, d, n);
    t = clock() - t;
    
    if (returnFlag)
    {
        printf("\nInverse Matrix:\n");
        printMatrix(inverseMatrix, n, m);
        
        if (inputType == 1)
        {
            fseek(fin, 0, SEEK_SET);
            fscanf(fin, "%d", &n);
        }
        
        returnFlag = enterMatrix(matrix, n, fin);
        
        printf("\nThe norm of residual: %f\n", residualNorm(matrix, inverseMatrix, n));
        printf("Inversion time = %f \n", t*1.0/CLOCKS_PER_SEC);
    }
    else
    {
        printf("Error while inverting matrix\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(inverseMatrix);
        free(d);
        
        return -1;
    }
    
    if (inputType == 1)
        fclose(fin);
    
    free(matrix);
    free(inverseMatrix);
    free(d);
    
    return 0;
}
