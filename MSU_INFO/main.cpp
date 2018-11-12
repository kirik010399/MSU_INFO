#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "calculatingManager.hpp"
#include <algorithm>

using namespace std;

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
    myPair p;
    double left, right;
    
    printf("Choosy type of entering data: 1 - from file, 2 - from formula\n");
    
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
    
    matrix = new double [n*n];
    vector = new double [n];
    
    if (!(matrix && vector))
    {
        printf("No memory, enter matrix with less dimensions\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
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
        delete []vector;
        
        return -2;
    }
    
    printf("Enter size of printing vector: ");
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }
    
    printf("Enter left and right borders:\n") ;

    if (scanf("%lf", &left) != 1 || scanf("%lf", &right) != 1 || right < left || fabs(right - left) < 1e-100)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }

    printf("Enter accuracy: \n");
    
    if (scanf("%lf", &eps) != 1 || eps <= 0)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }
    
    t = clock();
    calculateValues(matrix, vector, left, right, eps, n);
    t = clock() - t;
    
    printf("\nValues vector:\n");
    printVector(vector, n, m);
    
    if (inputType == 1)
        fseek(fin, 1, SEEK_SET);
    
    returnFlag = enterMatrix(matrix, n, fin);
    p = residualNorm(matrix, vector, n);
    
    printf("\nThe norm of residual: in first inv: %lf, in second inv: %lf\n", p.inv1, p.inv2);
    
    printf("Calculating time =  %lu milliseconds\n", t);

    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []vector;
    
    return 0;
}
