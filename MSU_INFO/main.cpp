#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "solve.hpp"

int main(int argc, char **argv)
{
    int n, m, k;
    double *a;
    double *b;
    double *x;
    int *ind;
    FILE* fin = nullptr;
    clock_t t;
    int flag;
    
    if (argc < 4)
    {
        printf("Некорректный запуск программы. Правильный формат:\n./a.out n m k *filename (если k != 0)");
        return -1;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%d", &k) != 1)
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }
    
    if ((k == 0 && argc != 5) || (k != 0 && argc != 4))
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }
    
    if (n < 0 || m < 0 || m > n || k < 0 || k > 4)
    {
        printf("Данные некорректны.\n");
        return -1;
    }

    if (k == 0)
    {
        fin = fopen(argv[4], "r");
        
        if (!fin)
        {
            printf("Файла не существует.\n");
            fclose(fin);
            return -2;
        }
    }
    
    a = new double [n*n];
    b = new double [n];
    x = new double [n];
    ind = new int [n];
    
    if (!(a && b && x && ind))
    {
        printf("Недостаточно памяти.\n");
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []ind;
        
        return -2;
    }

    flag = enter_matrix(a, b, n, k, fin);
    
    if (flag < 0)
    {
        printf("Матрица некорректна.\n");
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []ind;
        
        return -2;
    }
    
    printf("Изначальная матрица:\n");
    print_matrix(a, n, n, m);
    
    t = clock();
    flag = solve(a, b, x, ind, n);
    t = clock() - t;
    
    if (flag == 0)
    {
        printf("\nРешение системы:\n");
        print_matrix(x, 1, n, m);
        printf("\nВремя: %f с.\n", t*1.0/CLOCKS_PER_SEC);
        
        if (k == 0)
            fseek(fin, 0, SEEK_SET);
        
        flag = enter_matrix(a, b, n, k, fin);
        
        printf("Норма невязки: %10.3e\n", norm(a, b, x, n));
        printf("Норма ошибки: %10.3e\n", error_norm(x, n));
    }
    else
    {
        printf("Матрица вырождена.\n");
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []ind;
        
        return -1;
    }
    
    if (k == 0)
        fclose(fin);
    
    delete []a;
    delete []b;
    delete []x;
    delete []ind;

    return 0;
}
