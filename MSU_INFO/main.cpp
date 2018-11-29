#include <iostream>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "invertingManager.hpp"
#include <sys/time.h>

using namespace std;

long double getTime();

typedef struct
{
    int n;
    double *matrix;
    double *inverseMatrix;
    int rank;
    int threadsCount;
    double *d;
} Args;

void *Inversion(void *Arg)
{
    Args *arg = (Args*)Arg;
    int res;
    
    res = invertMatrix(arg->matrix, arg->inverseMatrix, arg-> d, arg->n, arg->rank, arg->threadsCount);
    
    return new int(res);
}

int main()
{
    int i;
    int n, m;
    double *matrix;
    double *inverseMatrix;
    double *d;
    FILE* fin = NULL;
    long double t;
    int threadsCount;
    pthread_t *threads;
    Args *args;
    int inputType;
    int returnFlag;
    void *res;
    int *intRes;
    
    cout<<"Choosy type of entering data: 1 - from file, 2 - from formula"<<endl;
    
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
        
        if (fscanf(fin, "%d", &threadsCount) != 1 || threadsCount <= 0)
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
        
        cout<<"Enter treads count: ";
        
        if (scanf("%d", &threadsCount) != 1 || threadsCount <= 0)
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
    
    matrix = new double [n*n];
    inverseMatrix = new double [n*n];
    threads = new pthread_t[threadsCount];
    args = new Args[threadsCount];
    d = new double [n];
    
    if (!(matrix && inverseMatrix && threads && args))
    {
        cout<<"No memory, enter matrix with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []threads;
        delete []args;
        delete []d;
        return -2;
    }
    
    returnFlag = enterMatrix(matrix, n, fin);
    
    if (returnFlag == -1)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []threads;
        delete []args;
        delete []d;

        return -2;
    }
    
    cout<<"Enter size of printing matrix: ";
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        delete []threads;
        delete []args;
        delete []d;
        
        return -2;
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        args[i].n = n;
        args[i].matrix = matrix;
        args[i].inverseMatrix = inverseMatrix;
        args[i].rank = i;
        args[i].threadsCount = threadsCount;
        args[i].d = d;
    }
    
    t = getTime();
    
    for (i = 0; i < threadsCount; i++)
    {
        if (pthread_create(threads + i, 0, Inversion, args + i))
        {
            printf("Cannot create thread %d!\n", i);
            
            if (inputType == 1)
                fclose(fin);
            
            delete []matrix;
            delete []inverseMatrix;
            delete []threads;
            delete []args;
            delete []d;
            
            return -1;
        }
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        if (pthread_join(threads[i], &res))
        {
            printf("Cannot wait thread %d!\n", i);
            
            if (inputType == 1)
                fclose(fin);
            
            delete []matrix;
            delete []inverseMatrix;
            delete []threads;
            delete []args;
            delete []d;
            
            return -1;
        }
        
        intRes = (int *)res;
        
        if(intRes && *intRes != 0)
        {
            cout<<"Error while inverting matrix"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []matrix;
            delete []inverseMatrix;
            delete []threads;
            delete []args;
            delete []d;
            
            return -1;
        }
    }
    
    t = getTime() - t;
    
    cout<<endl<<"Inverse Matrix:"<<endl;
    printMatrix(inverseMatrix, n, m);
    
    if (inputType == 1)
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n);
        fscanf(fin, "%d", &threadsCount);
    }

    returnFlag = enterMatrix(matrix, n, fin);
    
    cout<<endl<<"The norm of residual: "<<residualNorm(matrix, inverseMatrix, n)<<endl;
    
    cout<<"Inversion time =  "<< t << " seconds"<<endl;
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []inverseMatrix;
    delete []threads;
    delete []args;
    delete []d;
    
    return 0;
}

long double getTime()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
