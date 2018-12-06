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
    double *matrix;
    double *vector;
    double *result;
    int rank;
    int threadsCount;
    int retFlag;
} Args;

void *Inversion(void *Arg)
{
    Args *arg = (Args*)Arg;
    
    arg->retFlag = solveSystem(arg->matrix, arg->vector, arg->result, arg->n, arg->rank, arg->threadsCount);
    
    return NULL;
}

int main()
{
    int i;
    int n, m;
    double *matrix;
    double *vector;
    double *result;
    FILE* fin = NULL;
    long double t;
    int threadsCount;
    pthread_t *threads;
    Args *args;
    int inputType;
    int returnFlag;
    
    cout<<"Choose type of entering data: 1 - from file, 2 - from formula"<<endl;
    
    if (scanf("%d", &inputType) != 1)
    {
        cout<<"Data isn't correct"<<endl;
        return -2;
    }
    
    if (inputType == 1)
    {
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
    }
    else if (inputType == 2)
    {
        cout<<"Enter size: ";
        
        if (scanf("%d", &n) != 1 || n <= 0)
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
    
    cout<<"Enter treads count: ";
    
    if (scanf("%d", &threadsCount) != 1 || threadsCount <= 0)
    {
        cout<<"Data isn't correct"<<endl;
        return -2;
    }
    
    matrix = new double [n*n];
    vector = new double [n];
    result = new double [n];
    threads = new pthread_t[threadsCount];
    args = new Args[threadsCount];
    
    if (!(matrix && vector && result && threads && args))
    {
        cout<<"No memory, enter matrix with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        delete []threads;
        delete []args;
        return -2;
    }
    
    returnFlag = enterData(matrix, vector, n, fin);

    if (returnFlag == -1)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        delete []threads;
        delete []args;

        return -2;
    }
    
    cout<<"Enter size of printing matrix: ";
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        delete []threads;
        delete []args;
        
        return -2;
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        args[i].n = n;
        args[i].matrix = matrix;
        args[i].vector = vector;
        args[i].result = result;
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
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
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
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
            delete []args;
            
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
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
            delete []args;
            
            return -1;
        }
    }
    
    cout<<"Result:"<<endl;
    printResult(result, n, m);
    
    if (inputType == 1)
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n);
    }

    returnFlag = enterData(matrix, vector, n, fin);
    
    cout<<"Residual norm: "<<residualNorm(matrix, vector, result, n)<<endl;
    
    if (inputType == 2)
        cout<<"Error norm: "<<errorNorm(result, n)<<endl; ;
    
    cout<<"Solving time = "<<t<<" milliseconds"<<endl;
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []vector;
    delete []result;
    delete []threads;
    delete []args;
    
    return 0;
}

long double getTime()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
