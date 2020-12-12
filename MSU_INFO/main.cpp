#include <iostream>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "values.hpp"

int main(int argc, char **argv)
{
    int n, m, k;
    double *a;
    double *x;
    FILE* fin = NULL;
    clock_t t;
    int flag;
    double eps;
    double left, right;
    double norm1, norm2;
    int values_count = 0;
        
    if (argc < 7)
    {
        printf("Некорректный запуск программы. Правильный формат:\n./a.out n m eps left right k *filename (если k != 0)");
        return -1;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1
        || sscanf(argv[3], "%lf", &eps) != 1 || sscanf(argv[4], "%lf", &left) != 1
        || sscanf(argv[5], "%lf", &right) != 1 || sscanf(argv[6], "%d", &k) != 1)
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }
    
    if ((k == 0 && argc != 8) || (k != 0 && argc != 7))
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }
    
    if (n < 0 || m < 0 || m > n || k < 0 || k > 4
        || right < left || eps < 1e-16 || fabs(right - left) < 1e-16)
    {
        printf("Данные некорректны.\n");
        return -1;
    }

    if (k == 0)
    {
        fin = fopen(argv[7], "r");
        
        if (!fin)
        {
            printf("Файла не существует.\n");
            fclose(fin);
            return -2;
        }
    }
    
    a = new double [n*n];
    x = new double [n];
    
    if (!(a && x))
    {
        printf("Недостаточно памяти.\n");
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []x;
        
        return -2;
    }

    flag = enter_matrix(a, n, k, fin);
    
    if (flag < 0)
    {
        printf("Матрица некорректна.\n");
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []x;
        
        return -2;
    }
    
    printf("Изначальная матрица:\n");
    print_matrix(a, n, n, m);
    
    t = clock();
    calculate_values(a, x, &values_count, left, right, eps, n);
    t = clock() - t;
        
    if (values_count != 0)
    {
        printf("Собственные значения:\n");
        
        if (values_count < m)
            print_matrix(x, 1, n, values_count);
        else
            print_matrix(x, 1, n, m);
    }
    else
    {
        printf("На отрезке нет собственных значений.\n");
    }
    
    printf("\nВремя: %f с.\n", t*1.0/CLOCKS_PER_SEC);
    
    if (values_count == n)
    {
        if (k == 0)
            fseek(fin, 0, SEEK_SET);
        
        flag = enter_matrix(a, n, k, fin);
        
        residual(a, x, &norm1, &norm2, n);
        
        printf("Невязка в первом инварианте: %10.3e\n", norm1);
        printf("Невязка во втором инварианте: %10.3e\n", norm2);
    }
    
    if (k == 0)
        fclose(fin);
    
    delete []a;
    delete []x;
    
    return 0;
}
