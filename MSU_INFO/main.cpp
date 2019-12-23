#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "solvingManager.hpp"

using namespace std;

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
    printResult(result, n, 10);
        
    enterData(matrix, vector, n);
        
    cout<<"The norm of residual: "<<residualNorm(matrix, vector, result, n)<<endl;
    
    delete []matrix;
    delete []vector;
    delete []result;
    
    return 0;
}
