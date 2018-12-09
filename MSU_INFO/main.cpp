#include <iostream>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "solvingManager.hpp"
#include <sys/time.h>

using namespace std;

long double getTime();

typedef struct
{
    int n;
    double *a;
    double *b;
    double *x;
    int *var;
    int rank;
    int threadsCount;
    int retFlag;
} Args;

void *Inversion(void *Arg)
{
    Args *arg = (Args*)Arg;
    
    arg->retFlag = solveSystem(arg->a, arg->b, arg->x, arg->var, arg->n, arg->rank, arg->threadsCount);
    
    return NULL;
}

int main(int argc, char **argv)
{
    int i;
    int n, m;
    double *a;
    double *b;
    double *x;
    int *var;
    FILE* fin = NULL;
    long double t;
    int threadsCount;
    pthread_t *threads;
    Args *args;
    int inputType;
    int returnFlag;
    
    if (argc == 1)
    {
        cout<<"Incorrect mode"<<endl;
        return -2;
    }
    
    if (sscanf(argv[1], "%d", &inputType) != 1)
    {
        cout<<"Data isn't correct"<<endl;
        return -2;
    }
    
    if (inputType == 1)
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
        
        if (sscanf(argv[2], "%d", &threadsCount) != 1 || threadsCount <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            fclose(fin);
            return -2;
        }
    }
    else if (inputType == 2)
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
        
        if (sscanf(argv[3], "%d", &threadsCount) != 1 || threadsCount <= 0)
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
    var = new int[n];
    threads = new pthread_t[threadsCount];
    args = new Args[threadsCount];
    
    if (!(a && b && x && threads && var))
    {
        cout<<"No memory, enter a with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []threads;
        delete []args;
        delete []var;
        return -2;
    }
    
    returnFlag = enterData(a, b, n, fin);
    
    if (returnFlag == -1)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []threads;
        delete []args;
        delete []var;

        return -2;
    }
    
    if (inputType == 1)
    {
        if (sscanf(argv[3], "%d", &m) != 1 || m <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []var;
            
            return -2;
        }
    }
    else
    {
        if (sscanf(argv[4], "%d", &m) != 1 || m <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []var;
            
            return -2;
        }
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        args[i].n = n;
        args[i].a = a;
        args[i].b = b;
        args[i].x = x;
        args[i].var = var; 
        args[i].rank = i;
        args[i].threadsCount = threadsCount;
        args[i].retFlag = 0;
    }
    
    t = getTime();
    
    for (i = 0; i < threadsCount; i++)
    {
        if (pthread_create(threads + i, 0, Inversion, args + i))
        {
            printf("Can't create thread %d!\n", i);
            
            if (inputType == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []var;
            delete []args;
            
            return -1;
        }
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        if (pthread_join(threads[i], 0))
        {
            printf("Can't wait thread %d!\n", i);
            
            if (inputType == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []var;
            
            return -1;
        }
    }
    
    t = getTime() - t;
    
    for (i = 0; i < threadsCount; i++)
    {
        if (args[i].retFlag != 0)
        {
            cout<<"Error while solving system"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []a;
            delete []b;
            delete []x;
            delete []threads;
            delete []args;
            delete []var;

            return -1;
        }
    }
    
    cout<<"x:"<<endl;
    printResult(x, n, m);
    
    if (inputType == 1)
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n);
    }

    returnFlag = enterData(a, b, n, fin);
    
    cout<<"Residual norm: "<<residualNorm(a, b, x, n)<<endl;
    
    if (inputType == 2)
        cout<<"Error norm: "<<errorNorm(x, n)<<endl; ;
    
    cout<<"Solving time = "<<t<<" seconds"<<endl;
    
    if (inputType == 1)
        fclose(fin);
    
    delete []a;
    delete []b;
    delete []x;
    delete []threads;
    delete []var;
    delete []args;
    
    return 0;
}

long double getTime()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
