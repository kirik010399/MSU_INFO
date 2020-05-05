#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

void printMatrix(double* matrix, int n, FILE *fout);
void printVector(double* result, int n, FILE *fout);

int solveSystem(double* matrix, double* vector, double* result, int n, FILE *fout);

int main()
{
    int n;
    double *matrix;
    double *vector;
    double *result;
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
    vector = new double [n];
    result = new double [n];

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (fscanf(fin, "%lf", &matrix[i*n+j]) != 1)
            {
                fclose(fin);
                fclose(fout);
                delete []matrix;
                delete []vector;
                delete []result;
                
                return -1;
            }
        }
        if (fscanf(fin, "%lf", &vector[i]) != 1)
        {
            fclose(fin);
            fclose(fout);
            delete []matrix;
            delete []vector;
            delete []result;
            
            return -1;
        }
    }
    
    int returnFlag = solveSystem(matrix, vector, result, n, fout);
    
    if (returnFlag != -1)
        printVector(result, n, fout);
    else
    {
        fprintf(fout, "Error");

        fclose(fin);
        fclose(fout);
        delete []matrix;
        delete []vector;
        delete []result;
        
        return -2;
    }
    
    fclose(fin);
    fclose(fout);
    delete []matrix;
    delete []vector;
    delete []result;
    
    return 0;
}

int solveSystem(double* matrix, double* vector, double* result, int n, FILE *fout)
{
    int i, j, k, b;
    double a;

    double eps = 1e-16;
    
    for (j = 0; j < n; ++j)
    {
        a = matrix[j*n+j];
        b = j;
        
        for (i = j+1; i < n; ++i)
        {
            if (fabs(matrix[i*n+j]) > fabs(a))
            {
                a = matrix[i*n+j];
                b = i;
            }
        }
        
        if (fabs(a) < eps)
            return -1;
        
        if (b != j)
        {
            for (i = j; i < n; ++i)
                swap(matrix[b*n+i], matrix[j*n+i]);
            
            swap(vector[b], vector[j]);
        }
        
        for(i = 0; i < n; ++i)
        {
            if (i != j && fabs(matrix[i*n+j]) > eps)
            {
                a = matrix[i*n+j]/matrix[j*n+j];
                
                for(k = j; k < n; ++k)
                    matrix[i*n+k] -= a*matrix[j*n+k];
                
                vector[i] -= a*vector[j];
            }
        }
    }
    for (i = 0; i < n; ++i)
        result[i] = vector[i]/matrix[i*n+i];
    
    printMatrix(matrix, n, fout);
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

void printVector(double* result, int n, FILE *fout)
{
    for (int i = 0; i < n; ++i)
    {
        fprintf(fout, "%.6lf ", result[i]);
    }
    fprintf(fout, "\n");
}
