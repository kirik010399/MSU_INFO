#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

void printMatrix(double* matrix, int n, FILE *fout);
int invertMatrix(double* matrix, double* inverseMatrix, int n, FILE *fout);

int main()
{
    int n;
    double *matrix;
    double *inverseMatrix;
    FILE *fin, *fout;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
        
    if (fscanf(fin, "%d", &n) != 1 || n <= 0)
    {
        fclose(fin);
        fclose(fout);
        return -1;
    }
  
    matrix = new double [n*n];
    inverseMatrix = new double [n*n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (fscanf(fin, "%lf", &matrix[i*n+j]) != 1)
            {
                fclose(fin);
                fclose(fout);
                delete []matrix;
                delete []inverseMatrix;
                
                return -1;
            }
        }
    }
    
    int returnFlag = invertMatrix(matrix, inverseMatrix, n, fout);
    
    if (returnFlag != -1)
        printMatrix(inverseMatrix, n, fout);
    else
    {
        fprintf(fout, "Error");

        fclose(fin);
        fclose(fout);
        delete []matrix;
        delete []inverseMatrix;
        
        return -2;
    }
    
    fclose(fin);
    fclose(fout);
    delete []matrix;
    delete []inverseMatrix;
    
    return 0;
}

int invertMatrix(double* matrix, double* inverseMatrix, int n, FILE *fout)
{
    int i, j, k, maxElemIndex;
    double a, maxElem;
    
    double eps = 1e-16;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (i == j)
                inverseMatrix[i*n+j] = 1;
            else
                inverseMatrix[i*n+j] = 0;
        }
    }

    for (i = 0; i < n; ++i)
    {
        maxElem = fabs(matrix[i*n+i]);
        maxElemIndex = i;
        
        for (j = i + 1; j < n; ++j)
        {
            if (maxElem < fabs(matrix[j*n+i]))
            {
                maxElem = fabs(matrix[j*n+i]);
                maxElemIndex = j;
            }
        }
        
        for (j = 0; j < n; ++j)
            swap (matrix[i*n+j], matrix[maxElemIndex*n+j]);
        
        for (j = 0; j < n; ++j)
            swap (inverseMatrix[i*n+j], inverseMatrix[maxElemIndex*n+j]);
        
        if (fabs(matrix[i*n+i]) < eps)
            return -1;
        
        a = 1.0/matrix[i*n+i];
        
        for (j = i; j < n; ++j)
            matrix[i*n+j] *= a;
        
        for (j = 0; j < n; ++j)
            inverseMatrix[i*n+j] *= a;
        
        for (j = 0; j < n; ++j)
        {
            if (i == j)
                continue;
            
            a = matrix[j*n+i];
            
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
            
            for (k = 0; k < n; ++k)
                inverseMatrix[j*n+k] -= inverseMatrix[i*n+k] * a;
        }
    }
    
    printMatrix(matrix, n, fout);
    fprintf(fout, "\n");
    printMatrix(inverseMatrix, n, fout);
    fprintf(fout, "\n");
    
    return 0;
}


void printMatrix(double* matrix, int n, FILE *fout)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fprintf(fout, "%.6lf ", matrix[i*n+j]);
        }
        fprintf(fout, "\n");
    }
}
