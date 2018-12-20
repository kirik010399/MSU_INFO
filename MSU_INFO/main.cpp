#include <iostream>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "solvingManager.hpp"
#include <sys/time.h>

using namespace std;

long double get_full_time();

typedef struct
{
    int n;
    double *a;
    double *b;
    double *x;
    int *index;
    int *retflag;
    int number;
    int count;
    maxelem *max_;
    int flag;
} Args;

void *Solve(void *Arg);

int main(int argc, char **argv)
{
    int i;
    int n, m;
    double *a, *b, *x;
    int *index;
    FILE* fin = NULL;
    long double t;
    int count;
    pthread_t *threads;
    Args *args;
    maxelem *max_;
    int retflag = 1;
    
    int type, flag;
    
    if (argc == 1)
    {
        cout<<"Incorrect mode"<<endl;
        return -2;
    }
    
    if (sscanf(argv[1], "%d", &type) != 1)
    {
        cout<<"Data isn't correct"<<endl;
        return -2;
    }
    
    if (type == 1)
    {
        if (argc != 4)
        {
            cout<<"Data isn't correct"<<endl;
            return -2;
        }
        
        fin = fopen("input.txt", "r");
        
        if (!fin)
        {
            cout<<"File don't exist"<<endl;
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            fclose(fin);
            return -2;
        }
        
        if (sscanf(argv[2], "%d", &count) != 1 || count <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            fclose(fin);
            return -2;
        }
    }
    else if (type == 2)
    {
        if (argc != 5)
        {
            cout<<"Data isn't correct"<<endl;
            return -2;
        }
        
        if (sscanf(argv[2], "%d", &n) != 1 || n <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            return -2;
        }
        
        if (sscanf(argv[3], "%d", &count) != 1 || count <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            return -2;
        }
    }
    else
    {
        cout<<"Input type isn't correct"<<endl;
        return -2;
    }
    
    a = new double [n*n];
    b = new double [n];
    x = new double [n];
    index = new int[n];
    max_ = new maxelem[count];
    threads = new pthread_t[count];
    args = new Args[count];
    
    if (!(a && b && x && threads && index))
    {
        cout<<"No memory, enter a with less dimensions"<<endl;
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []threads;
        delete []args;
        delete []index;
        delete []max_;

        return -2;
    }
    
    flag = enterData(a, b, n, fin);
    
    if (flag == -1)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []threads;
        delete []args;
        delete []index;
        delete []max_;

        return -2;
    }
    
    if (type == 1)
    {
        if (sscanf(argv[3], "%d", &m) != 1 || m <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            
            if (type == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []index;
            delete []max_;
            
            return -2;
        }
    }
    else
    {
        if (sscanf(argv[4], "%d", &m) != 1 || m <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            
            if (type == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []index;
            delete []max_;
            
            return -2;
        }
    }
    
    for (i = 0; i < count; i++)
    {
        args[i].n = n;
        args[i].a = a;
        args[i].b = b;
        args[i].x = x;
        args[i].index = index;
        args[i].max_ = max_;
        args[i].number = i;
        args[i].retflag = &retflag;
        args[i].count = count;
        args[i].flag = 0;
    }
    
    t = get_full_time();
    
    for (i = 0; i < count; i++)
    {
        if (pthread_create(threads + i, 0, Solve, args + i))
        {
            printf("Can't create thread %d!\n", i);
            
            if (type == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []index;
            delete []args;
            delete []max_;
            
            return -1;
        }
    }
    
    for (i = 0; i < count; i++)
    {
        if (pthread_join(threads[i], 0))
        {
            printf("Can't wait thread %d!\n", i);
            
            if (type == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []index;
            delete []max_;
            
            return -1;
        }
    }
    
    t = get_full_time() - t;
    
    for (i = 0; i < count; i++)
    {
        if (args[i].flag != 0)
        {
            cout<<"Error while solving system"<<endl;
            
            if (type == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []index;
            delete []max_;

            return -1;
        }
    }
    
    cout<<"x:"<<endl;
    printResult(x, n, m);
    
    if (type == 1)
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n);
    }

    flag = enterData(a, b, n, fin);
    
    cout<<"Residual norm: "<<residualNorm(a, b, x, n)<<endl;
    
    if (type == 2)
        cout<<"Error norm: "<<errorNorm(x, n)<<endl; ;
    
    cout<<"Solving time = "<<t<<" seconds"<<endl;
    
    if (type == 1)
        fclose(fin);
    
    delete []a;
    delete []b;
    delete []x;
    delete []threads;
    delete []index;
    delete []args;
    delete []max_;
    
    return 0;
}

void *Solve(void *Arg)
{
    Args *arg = (Args*)Arg;
    arg->flag = solve(arg->a, arg->b, arg->x, arg->index, arg->max_, arg->retflag, arg->n, arg->number, arg->count);
    return NULL;
}

long double get_full_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
