#include "solvingManager.hpp"
#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std; 

void fillTau(double *tau, int n, double m, double M, int N)
{
    int tauIndexes[N];
    
    for (int i = 0; i < N; ++i)
        tauIndexes[i] = n-i;
    
    for (int i = 0; i < N; ++i)
    {
        tau[i] = 1.0/((M+m)/2 + (M-m)/2 * cos(M_PI*(2*tauIndexes[i]-1)/(2*N)));
    }
}

void matrixVectorProduct(double* matrix, double* vector, double *resultVector, int n)
{
    for (int i = 0; i < n; ++i)
    {
        resultVector[i] = 0;
        for (int j = 0; j < n; ++j)
        {
            resultVector[i] += matrix[i*n+j] * vector[j];
        }
    }
}

void makeIteration(double* matrix, double* resultMatrix, double tau, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            resultMatrix[i*n+j] = int(i == j) - tau * matrix[i*n+j];
        }
    }
}

void sumVectors(double* vector1, double* vector2, double k, int n)
{
    for (int i = 0; i < n; ++i)
        vector1[i] += k * vector2[i];
}

double errorFunction(double *x, int n)
{
    int i;
    double error, maxError = 0;
    
    for (i = 0; i < n; i++)
    {
        if (i % 2)
            error = fabs(x[i]);
        else
            error = fabs(x[i]-1);
        
        if (error > maxError)
            maxError = error;
    }
    
    return maxError;
}

void solveSystem(double* matrix, double* vector, double* result, int n)
{
    double h = 1.0/(n+1);
    double m = 4.0, M = 4.0/(h*h);
    int N = 64;
    
    FILE *fout;
    fout = fopen("output.txt", "w"); 
    
    double *tempResult, *tempVector1, *tempVector2;
    
    tempResult = new double[n];
    tempVector1 = new double[n];
    tempVector2 = new double[n];

    double *tau;
    tau = new double [N];
    
    fillTau(tau, n, m, M, N);
    
    for (int i = 0; i < n; ++i)
        tempResult[i] = 1.0;
    
    for (int iteration = 0; iteration <= 2500; ++iteration)
    {
        for(int i = 0; i < n; ++i)//t1 = Ax
            for(int j = 0; j < n; ++j)
                tempVector1[i] += matrix[i*n+j] * tempResult[j];
        
        for(int i = 0; i < n; ++i)//t2 = tau*Ax
            tempVector2[i] = tau[iteration%N] * tempVector1[i];
        
        for(int i = 0; i < n; ++i)//x' = tau*b
            result[i] = tau[iteration%N] * vector[i];
        
        for(int i = 0; i < n; ++i)//t1 = x' - t2 = tau*b - tau*Ax
            tempVector1[i] = result[i] - tempVector2[i];
        
        for(int i = 0; i < n; ++i)//x' = x + tau*b - tau*Ax
            result[i] = tempResult[i] + tempVector1[i];
        
        for(int i = 0; i < n; ++i)//x = x'
            tempResult[i] = result[i];
        
        for (int i = 0; i < n; ++i)
        {
            tempVector1[i] = 0;
            tempVector2[i] = 0;
        }
        
        fprintf(fout, "%d %.16lf\n", iteration, errorFunction(result, n));
        printf("%d %.16lf\n", iteration, errorFunction(result, n));
    }
    
    free(tau);
    free(tempResult);
    free(tempVector1);
    free(tempVector2);

    fclose(fout);
}
