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
    FILE* fin = NULL;
  
    scanf("%d", &n);
   
    matrix = new double [n*n];
    vector = new double [n];
    result = new double [n];
    
    enterData(matrix, vector, n, fin);
    solveSystem(matrix, vector, result, n);
    
    cout<<"Result vector:"<<endl;
    printResult(result, n, 10);
        
    fscanf(fin, "%d", &n);
    enterData(matrix, vector, n, fin);
        
    cout<<endl<<"The norm of residual: "<<residualNorm(matrix, vector, result, n)<<endl;
    cout<<"The norm of error: "<<errorFunction(result, n)<<endl;
   
    fclose(fin);
    
    delete []matrix;
    delete []vector;
    delete []result;
    
    return 0;
}
