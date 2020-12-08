#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "solve.hpp"
#include <sys/time.h>
#include <pthread.h>

using namespace std;

long double get_time();

typedef struct
{
    double *a;
    double *b;
    double *x;
    int *ind;
    max_elem *max_; 
    int n;
    int thread_num;
    int threads_count;
    int *return_flag;
    long double time;
} Args;

void *solve(void *Arg)
{
    Args *arg = (Args*)Arg;
    
    long double t;
    
    synchronize(arg->threads_count);
    t = get_time();

    solve(arg->a, arg->b, arg->x, arg->ind, arg->max_, arg->n, arg->thread_num, arg->threads_count, arg->return_flag);
    
    synchronize(arg->threads_count);
    arg->time = get_time() - t;
    
    return NULL;
}

int main(int argc, char **argv)
{
    int n, m, k, i;
    double *a;
    double *b;
    double *x;
    int *ind;
    max_elem *max_;
    int return_flag = 1;
    FILE* fin = nullptr;
    long double t;
    int threads_count;
    pthread_t *threads;
    Args *args;
    int flag;
    
    if (argc < 5)
    {
        printf("Некорректный запуск программы. Правильный формат:\n./a.out n m threads k *filename (если k != 0)");
        return -1;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%d", &threads_count) != 1 || sscanf(argv[4], "%d", &k) != 1)
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }
    
    if ((k == 0 && argc != 6) || (k != 0 && argc != 5))
    {
        printf("Данные запуска некорректны.\n");
        return -1;
    }
    
    if (n < 0 || m < 0 || m > n || k < 0 || k > 4 || threads_count < 1)
    {
        printf("Данные некорректны.\n");
        return -1;
    }

    if (k == 0)
    {
        fin = fopen(argv[5], "r");
        
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
    max_ = new max_elem[threads_count];
    args = new Args [threads_count];
    threads = new pthread_t [threads_count];
    
    if (!(a &&b && x && ind && max_ && args && threads))
    {
        printf("Недостаточно памяти.\n");
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []ind;
        delete []args;
        delete []threads;
        delete []max_;
        
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
        delete []args;
        delete []threads;
        delete []max_;
        
        return -2;
    }
    
    printf("\nИзначальная матрица:\n");
    print_matrix(a, n, n, m);
    
    for (i = 0; i < threads_count; ++i)
    {
        args[i].a = a;
        args[i].b = b;
        args[i].x = x;
        args[i].ind = ind;
        args[i].max_ = max_;
        args[i].n = n;
        args[i].thread_num = i;
        args[i].threads_count = threads_count;
        args[i].return_flag = &return_flag;
    }
        
    for (i = 0; i < threads_count; ++i)
    {
        if (pthread_create(threads+i, 0, solve, args+i))
        {
            printf("Поток не создался.\n");
            
            if (k == 0)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []ind;
            delete []args;
            delete []threads;
            delete []max_;
            
            return -1;
        }
    }
    
    for (i = 0; i < threads_count; ++i)
    {
        if (pthread_join(threads[i], 0))
        {
            printf("Поток не запустился");
            
            if (k == 0)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []ind;
            delete []args;
            delete []threads;
            delete []max_;
            
            return -1;
        }
    }
    
    t = args[0].time;
    
    for (i = 1; i < threads_count; ++i)
    {
        if (t < args[i].time)
            t = args[i].time;
    }

    if(!return_flag)
    {
        printf("Матрица вырождена.\n");
        
        if (k == 0)
            fclose(fin);
        
        if (k == 0)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []ind;
        delete []args;
        delete []threads;
        delete []max_;
        
        return -1;
    }
    
    printf("\nРешение системы:\n");
    print_matrix(x, 1, n, m);
    printf("\nВремя: %Lf с.\n", t);
    
    if (k == 0)
        fseek(fin, 0, SEEK_SET);
    
    flag = enter_matrix(a, b, n, k, fin);
    
    printf("Норма невязки: %10.3e\n", norm(a, b, x, n));
    printf("Норма ошибки: %10.3e\n", error_norm(x, n));
    
    if (k == 0)
        fclose(fin);
    
    delete []a;
    delete []b;
    delete []x;
    delete []ind;
    delete []args;
    delete []threads;
    delete []max_;

    return 0;
}

long double get_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
