#include "calculatingManager.h"
#include <math.h>
#include <stdlib.h>

int k = 0;//количество в итоге посчитанных собственных значений и указатель на текущее место в массиве

int calculateValues(double* matrix, double* vector, double left, double right, double eps, int n)
{
    int i;
    
    for (i = 0; i < n; ++i)
        vector[i] = 0;//обнулили вектор сз
    
    eps = fmax(1e-10, eps);

    Rotation(matrix, n);//привели к трехдиагональному виду методом вращений
    values(matrix, n, vector, left, right, eps);//посчитали сз
    
    return k; //вернули их количество
}

void values(double *matrix, int n, double *vector, double left, double right, double eps)
{
    int c, j;
    
    c = n_(matrix, n, right) - n_(matrix, n, left);//см описание n_; количество собвенных значений от left до right
        
    if (right - left > eps && c != 0)//если left и right достаточно далеко и количество сз больше 0
    {
        values(matrix, n, vector, left, (left+right)/2, eps);//вызываем ее же от left до (left+right)/2
        values(matrix, n, vector, (left+right)/2, right, eps);//вызываем ее же от (left+right)/2 до right
    }
    else if (c != 0)//если left и right уже близко и количество сз не равно 0
    {
        for (j = 0; j < c; ++j)//кратность сз раз положить в массив сз это сз
            vector[k + j] = (left+right)/2;
        
        k += c;//увелеичили указатель на кратность раз
    }//95
}

void Rotation(double* matrix, int n)
{
    int i, j, k;
    double x, y, r, matrix_ik, matrix_jk, cosPhi, sinPhi;
    double matrix_ii, matrix_ij, matrix_ji, matrix_jj;
    
    for (i = 0; i < n-2; ++i)
    {
        for (j = i+2; j < n; ++j)
        {
            x = matrix[(i+1)*n+i];//берем первый под диагональю
            y = matrix[j*n+i];//берем все начиная со второго под диагональю, формулы в итоге будут обнулять его
            
            if (fabs(y) < 1e-100)
                continue;
            
            r = sqrt(x*x+y*y);
            
            if (r < 1e-100)
                continue;
            
            cosPhi = x/r;
            sinPhi = -y/r;//посчитали угол из формул
            
            for (k = i; k < n; ++k)
            {
                matrix_ik = matrix[(i+1)*n+k];
                matrix_jk = matrix[j*n+k];
                
                matrix[(i+1)*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                matrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;//*Tij
                
                if (k != i+1 && k != j)
                {
                    matrix[k*n+i+1] = matrix[(i+1)*n+k];//k i+1 = i+1 k
                    matrix[k*n+j] = matrix[j*n+k];//k j = j k
                }//from sym
            }
            
            matrix_ii = matrix[(i+1)*n+i+1];
            matrix_ji = matrix[j*n+i+1];
            matrix_ij = matrix[(i+1)*n+j];
            matrix_jj = matrix[j*n+j];
            
            matrix[(i+1)*n+i+1] = matrix_ii * cosPhi - matrix_ij * sinPhi;
            matrix[j*n+i+1] = matrix_ji * cosPhi - matrix_jj * sinPhi;
            matrix[(i+1)*n+j] = matrix_ii * sinPhi + matrix_ij * cosPhi;
            matrix[j*n+j] = matrix_ji * sinPhi + matrix_jj * cosPhi;//63 *Tij^T
        }
    }
}

int n_(double* matrix, int n, double lam)//количество собтвенных значений от минус бексонечности до lam методом LU разложения
{
    int i;
    int res;
    double elem;
    
    elem = matrix[0] - lam;
    
    if (elem < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)
    {
        elem = matrix[i*n+i] - matrix[i*n + i-1] * matrix[(i-1)*n+i]/elem - lam;//из LU разложения
        
        if (elem < 0)
            ++res;
    }
    
    return res;
}
