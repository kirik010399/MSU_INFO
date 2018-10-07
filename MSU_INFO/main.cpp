#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixFunctions.hpp"
#include "solvingFunctions.hpp"

using namespace std;

int main()
{
    int n, m;
    double *matrix;
    double *vector;
    double *result;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    
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
    
    matrix = new double [n*n];
    vector = new double [n];
    result = new double [n];
    
    if (!(matrix && vector && result))
    {
        printf("No memory, enter matrix with less dimensions\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        
        return -2;
    }

    returnFlag = enterData(matrix, vector, n, fin);
    
    if (returnFlag == -1)
    {
        printf("Data isn't correct\n");

        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        
        return -2;
    }
    
    printf("Enter size of printing: ");

    if (scanf("%d", &m) != 1)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        
        return -2;
    }
        
    printf("\n");
    
    t = clock();
    returnFlag = solveSystem(matrix, vector, result, n);
    t = clock() - t;
    
    if (returnFlag != -1)
    {
        printf("Result:\n");
        printResult(result, n, m);
        
        if (inputType == 1)
            fseek(fin, 1, SEEK_SET);
        
        returnFlag = enterData(matrix, vector, n, fin);
        
        printf("\nResidual norm: %f\n", residualNorm(matrix, vector, result, n));
        
        if (inputType == 2)
            printf("Error norm: %f\n", errorNorm(result, n));
        
        printf("Solving time =  %lu milliseconds", t);
    }
    else
    {
        printf("Error while solving system\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        
        return -1;
    }
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []vector;
    delete []result;
    
    return 0;
}
