#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "solvingManager.hpp"

using namespace std;

double func(int i, int j, int n);
void enterData(double* matrix, double *vector, int n);
void printResult(double* result, int n);
void fillTau(double *tau, int n, double m, double M, int N);
double errorFunction(double *x, int n);
double calculateNorm(double *tau, int iteration, int N, int n);
void solveSystem(double* matrix, double* vector, double* result, int n);

void fillTau(double *tau, int n, double m, double M, int N)
{
    int tauIndexes[N];
    
    int l = int(log2(N));
    
    tauIndexes[0] = 1;
    tauIndexes[N/2] = 2;
       
    for(int k = 2; k <= l; ++k)
    {
        for(int i = pow(2, l-k); i < N; i += pow(2, l+1-k))
            tauIndexes[i] = pow(2, k) + 1 - tauIndexes[int(i-pow(2, l-k))];
    }
    
    for (int i = 0; i < N; ++i)
    {
        --tauIndexes[i];
        printf("%d ", tauIndexes[i]);
    }
    printf("\n");
    
//    for (int i = 0; i < N; ++i)
//    {
//        tauIndexes[i] = i;
//    }
    
    for (int i = 0; i < N; ++i)
    {
        tau[i] = 1.0/((M+m)/2 + (M-m)/2 * cos(M_PI*(2*tauIndexes[i]+1)/(2*N)));
    }
}

double errorFunction(double *x, int n)
{
    int i;
    double error, maxError = 0;
    
    for (i = 0; i < n; i++)
    {
        if (i % 2 == 1)
            error = fabs(x[i]);
        else
            error = fabs(x[i]-1);
        
        if (error > maxError)
            maxError = error;
    }
    
    return maxError;
}

double calculateNorm(double *tau, int iteration, int N, int n)
{
    double maxProd = 0;
    double h = 1.0/(n-1);
    
    for (int m = 1; m < n; ++m)
    {
        double prod = 1;
        
        for (int i = 0; i < iteration; ++i)
        {
            double lam = 4*sin(0.5*M_PI*m*h)*sin(0.5*M_PI*m*h)/(h*h);
            prod *= fabs(1 - tau[i%N] * lam);
        }

        if (prod > maxProd)
        {
            maxProd = prod;
        }
    }
    
    return maxProd;
}

void solveSystem(double* matrix, double* vector, double* result, int n)
{
    double h = 1.0/(n-1);
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
    {
        result[i] = 0.0;
        tempResult[i] = 1.0;
        tempVector1[i] = 0;
        tempVector2[i] = 0;
    }
    
    for (int iteration = 0; iteration <= 2000; ++iteration)
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
                
        fprintf(fout, "%.16lf,", calculateNorm(tau, iteration, N, n));
        printf("%d %.16lf %.16lf\n", iteration, errorFunction(result, n), calculateNorm(tau, iteration, N, n));
    }
    
    delete []tau;
    delete []tempResult;
    delete []tempVector1;
    delete []tempVector2;

    fclose(fout);
}

int main()
{
    int n;
    double *matrix;
    double *vector;
    double *result;
    
    printf("Enter size: "); 
    scanf("%d", &n);
   
    matrix = new double [n*n];
    vector = new double [n];
    result = new double [n];
    
    enterData(matrix, vector, n);
    solveSystem(matrix, vector, result, n);
    
    cout<<"Result vector:"<<endl;
    printResult(result, n);
                    
    delete []matrix;
    delete []vector;
    delete []result;
    
    return 0;
}

double func(int i, int j, int n)
{
    double h = 1.0/(n-1);
    
    if (i == j)
        return 2.0/(h*h);
    else if (i == j+1 || i == j-1)
        return -1.0/(h*h);
    else
        return 0;
}

void enterData(double* matrix, double *vector, int n)
{
    for (int i = 0; i < n; ++i)
    {
        vector[i] = 0;
        
        for (int j = 0; j < n; ++j)
        {
            matrix[i*n+j] = func(i, j, n);
            
            if (j % 2 == 0)
                vector[i] += matrix[i*n+j];
        }
    }
}

void printResult(double* result, int n)
{
    int i;
    int min_ = min(n, 10);
    
    for (i = 0; i < min_; ++i)
        cout<<result[i]<<' ';
    
    cout<<endl;
}
