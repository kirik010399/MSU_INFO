#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "invert.hpp"

int main()
{
    int n, m;
    double *a;
    double *a_inv;
    FILE* fin = nullptr;
    clock_t t;
    int type;
    int flag;
    
    printf("Выберите тип входных данных: 1 - из файла, 2 - из формулы:\n");
    
    if (scanf("%d", &type) != 1)
    {
        printf("Данные некорректны.\n");
        return -2;
    }
         
    if (type == 1)
    {
        fin = fopen("input.txt", "r");
        
        if (!fin)
        {
            printf("Файла не существует.\n");
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0)
        {
            printf("Данные некорректны.\n");
            fclose(fin);
            return -2;
        }
    }
    else if (type == 2)
    {
        printf("Введите размер:\n");
    
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Данные некорректны.\n");
            return -2;
        }
    }
    else
    {
        printf("Некорректный тип ввода.\n");
        return -2;
    }
    
    a = new double [n*n];
    a_inv = new double [n*n];
    
    if (!(a && a_inv))
    {
        printf("Недостаточно памяти.\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []a_inv;
        
        return -2;
    }

    flag = enter_matrix(a, n, fin);
    
    if (flag == -1)
    {
        printf("Данные некорректны.\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []a_inv;
        
        return -2;
    }
    
    printf("Введите размер угла печати:\n");
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        printf("Данные некорректны.\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []a_inv;
        
        return -2;
    }
    
    t = clock();
    flag = invert(a, a_inv, n);
    t = clock() - t;
    
    if (flag == 0)
    {
        printf("\nОбратная матрица:\n");
        print_matrix(a_inv, n, m);
        
        if (type == 1)
        {
            fseek(fin, 0, SEEK_SET);
            fscanf(fin, "%d", &n);
        }
        
        flag = enter_matrix(a, n, fin);
        
        printf("\nПогрешность: %f\n", norm(a, a_inv, n));
        printf("Время: %f с.\n", t*1.0/CLOCKS_PER_SEC);
    }
    else
    {
        printf("Произошла ошибка во время обращения матрицы.\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []a_inv;
        
        return -1;
    }
    
    if (type == 1)
        fclose(fin);
    
    delete []a;
    delete []a_inv;
    
    return 0;
}
