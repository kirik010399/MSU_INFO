#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

using namespace std;

void print_matrix(double* matrix, int n, FILE *fout);
void print_vector(double* result, int n, FILE *fout);
void solve_system(double* matrix, double* vector, double* result, int n, int thread_num, int threads_count, int *return_flag);
void synchronize(int threads_count);

double f(int k, int n, int i, int j)
{
    switch (k)
    {
        case 1:
            return n-fmax(i, j);
        case 2:
            return fmax(i, j);
        case 3:
            return fabs(i-j);
        case 4:
            if (i == n/2)
                return 0;
            return fabs(i-j);
        default:
            return -1;
    }
}

typedef struct
{
    double *matrix;
    double *vector;
    double *result;
    int n;
    int thread_num;
    int threads_count;
    int *return_flag;
} Args;

void *solve(void *Arg)
{
    Args *arg = (Args*)Arg;

    solve_system(arg->matrix, arg->vector, arg->result, arg->n, arg->thread_num, arg->threads_count, arg->return_flag);
    
    return NULL;
}

int main()
{
    int n, k;
    int i, j;
    double *matrix;
    double *vector;
    double *result;
    FILE *fin, *fout;
    int return_flag = 1;
    
    int threads_count;
    pthread_t *threads;
    Args *args;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    if (fscanf(fin, "%d", &n) != 1 || n <= 0)
    {
        fclose(fin);
        fclose(fout);
        return -1;
    }
    
    if (fscanf(fin, "%d", &threads_count) != 1 || threads_count <= 0)
    {
        fclose(fin);
        fclose(fout);
        return -1;
    }
    
    if (fscanf(fin, "%d", &k) != 1 || k <= 0 || k >= 5)
    {
        fclose(fin);
        fclose(fout);
        return -1;
    }
  
    matrix = new double [n*n];
    vector = new double [n];
    result = new double [n];
    args = new Args [threads_count];
    threads = new pthread_t [threads_count];

    for (i = 0; i < n; ++i)
    {
        vector[i] = 0;
        
        for (j = 0; j < n; ++j)
        {
            matrix[i*n+j] = f(k, n, i, j);
            
            if (j % 2 == 0)
                vector[i] += matrix[i*n+j];
        }
    }
    
    print_matrix(matrix, n, stdout);
    
    for (i = 0; i < threads_count; ++i)
    {
        args[i].matrix = matrix;
        args[i].vector = vector;
        args[i].result = result;
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
            
            fclose(fin);
            fclose(fout);
            delete []matrix;
            delete []vector;
            delete []result;
            delete []args;
            delete []threads;
            
            return -1;
        }
    }
    
    for (i = 0; i < threads_count; ++i)
    {
        if (pthread_join(threads[i], 0))
        {
            printf("Поток не запустился");
            
            fclose(fin);
            fclose(fout);
            delete []matrix;
            delete []vector;
            delete []result;
            delete []args;
            delete []threads;
            
            return -1;
        }
    }
    
    if(!return_flag)
    {
        printf("Матрица вырождена.\n");

        fclose(fin);
        fclose(fout);
        delete []matrix;
        delete []vector;
        delete []result;
        delete []args;
        delete []threads;
        
        return -1;
    }
    
    print_matrix(matrix, n, fout);
    fprintf(fout, "\n");
    print_vector(result, n, fout);
    
    fclose(fin);
    fclose(fout);
    delete []matrix;
    delete []vector;
    delete []result;
    delete []args;
    delete []threads;
    
    return 0;
}

void solve_system(double* matrix, double* vector, double* result, int n, int thread_num, int threads_count, int *return_flag)
{
    int i, j, k, max_index;
    int begin_row, last_row;

    double a;
    
    double eps = 1e-16;
    
    for (i = 0; i < n; ++i)
    {
        synchronize(threads_count);

        if (thread_num == 0)
        {
            a = matrix[i*n+i];
            max_index = i;
            
            for (j = i+1; j < n; ++j)
            {
                if (fabs(matrix[j*n+i]) > fabs(a))
                {
                    a = matrix[j*n+i];
                    max_index = j;
                }
            }
            
            if (fabs(a) < eps)
                *return_flag = 0;
            
            if (*return_flag)
            {
                if (max_index != i)
                {
                    for (j = i; j < n; ++j)
                        swap(matrix[max_index*n+j], matrix[i*n+j]);
                    
                    swap(vector[max_index], vector[i]);
                }
                
                a = 1.0/matrix[i*n+i];
                       
                for (j = i; j < n; ++j)
                    matrix[i*n+j] *= a;
               
                vector[i] *= a;
            }
        }
        
        synchronize(threads_count);

        begin_row = (n - i - 1) * thread_num;
        begin_row = begin_row/threads_count + i + 1;
        last_row = (n - i - 1) * (thread_num + 1);
        last_row = last_row/threads_count + i + 1;
        
        for (j = begin_row; j < last_row; ++j)
        {
            a = matrix[j*n+i];
         
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
           
            vector[j] -= vector[i] * a;
        }
    }
   
    synchronize(threads_count);

    if (thread_num == 0)
    {
        for (i = n-1; i >= 0; --i)
        {
            a = vector[i];
           
            for (j = i+1; j < n; ++j)
                a -= matrix[i*n+j] * result[j];
           
            result[i] = a;
        }
    }
}

void print_matrix(double* matrix, int n, FILE *fout)
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            fprintf(fout, "%.6lf ", matrix[i*n+j]);
        }
        fprintf(fout, "\n");
    }
}

void print_vector(double* result, int n, FILE *fout)
{
    for (int i = 0; i < 10; ++i)
    {
        fprintf(fout, "%.6lf ", result[i]);
    }
    fprintf(fout, "\n");
}

void synchronize(int threads_count)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
    static int threads_in = 0;
    static int threads_out = 0;
    
    pthread_mutex_lock(&mutex);
    
    threads_in++;
    if (threads_in >= threads_count)
    {
        threads_out = 0;
        pthread_cond_broadcast(&condvar_in);
    }
    else
    {
        while (threads_in < threads_count)
            pthread_cond_wait(&condvar_in, &mutex);
    }
    
    threads_out++;
    if (threads_out >= threads_count)
    {
        threads_in = 0;
        pthread_cond_broadcast(&condvar_out);
    }
    else
    {
        while (threads_out < threads_count)
            pthread_cond_wait(&condvar_out,&mutex);
    }
    
    pthread_mutex_unlock(&mutex);
}
