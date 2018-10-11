#include <time.h>
#include <math.h>
#include "matrixFunctions.hpp"
#include "invertingFunctions.hpp"

int main()
{
    int n, m;
    double *matrix, *inverseMatrix, *vector;
    FILE* fin = NULL;
    clock_t t;
    int inputType, returnFlag;
    
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
        printf("Enter size of matrix: ");

        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Data isn't correct\n");
            return -2;
        }
    }
    else
    {
        printf("Data isn't correct\n");
        return -2;
    }
    
    matrix = new double [n*(n+1)/2];
    inverseMatrix = new double[n*(n+1)/2];
    vector = new double [n];
    
    if (!(matrix && inverseMatrix && vector))
    {
        printf("No memory, enter matrix with less dimensions\n");

        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []vector;
        
        return -2;
    }

    returnFlag = enterMatrix(matrix, n, fin);
    
    if (returnFlag == -1)
    {
        printf("Data isn't correct\n");

        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []vector;
        
        return -2;
    }
    
    printf("Enter size of printing: ");

    if (scanf("%d", &m) != 1 || m <= 0)
    {
        printf("Data isn't correct\n");

        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []vector;
        
        return -2;
    }
    
    t = clock();
    returnFlag = invertMatrix(matrix, inverseMatrix, vector, n);
    t = clock() - t;
    
    if (returnFlag != -1)
    {
        printf("\nInverse Matrix:\n");
        printMatrix(inverseMatrix, n, m);
        
        if (inputType == 1)
            fseek(fin, 1, SEEK_SET);
        
        returnFlag = enterMatrix(matrix, n, fin);
        
        printf("\nResidual norm: %f\n", residualNorm(matrix, inverseMatrix, n));
        
        printf("Solving time:  %lu milliseconds", t);
    }
    else
    {
        printf("Error while inverting matrix\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []vector;
        
        return -1;
    }
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []inverseMatrix;
    delete []vector;
    
    return 0;
}
