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
    double *matrix;
    double *vector;
    double *result;
    int *var;
    maxElem *maxx;
    int n;
    int rank;
    int threadsCount;
    int retFlag;
    int *flag;
    double norm;
    FILE *fin;
    int inputType;
} Args;

void *Solving(void *Arg)
{
    int returnFlag, nn = 0;
    Args *arg = (Args*)Arg;
    
    arg->retFlag = solveSystem(arg->matrix, arg->vector, arg->result, arg->var, arg->maxx, arg->flag, arg->n, arg->rank, arg->threadsCount);
    
    synchronize(arg->threadsCount);

    if (arg->rank == 0)
    {
        if (arg->inputType == 1)
        {
            fseek(arg->fin, 0, SEEK_SET);
            fscanf(arg->fin, "%d", &nn);
        }
        
        returnFlag = enterData(arg->matrix, arg->vector, arg->n, arg->fin);
    }
    
    synchronize(arg->threadsCount);
    
    arg->norm =  residualNorm(arg->matrix, arg->vector, arg->result, arg->n, arg->rank, arg->threadsCount);
    
    return NULL;
}

int main(int argc, char **argv)
{
    int i;
    int n, m;
    double *matrix;
    double *vector;
    double *result;
    int *var;
    maxElem *maxx;
    int flag = 1;
    FILE* fin = NULL;
    long double t;
    int threadsCount;
    pthread_t *threads;
    Args *args;
    int inputType;
    double residualNorm = 0;
    int returnFlag;
    
    if (argc == 1)
    {
        cout<<"Incorrect mode"<<endl;
        return -2;
    }
    
    if (sscanf(argv[1],"%d", &inputType) != 1)
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
        
        if (sscanf(argv[2], "%d", &threadsCount) != 1 || threadsCount <= 0 || threadsCount > n)
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
        
        if (sscanf(argv[3], "%d", &threadsCount) != 1 || threadsCount <= 0 || threadsCount > n)
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
    vector = new double [n];
    result = new double [n];
    var = new int[n];
    threads = new pthread_t[threadsCount];
    args = new Args[threadsCount];
    maxx = new maxElem[threadsCount];
    
    if (!(matrix && vector && result && threads && var && maxx))
    {
        cout<<"No memory, enter matrix with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        delete []threads;
        delete []args;
        delete []var;
        delete []maxx;
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
        delete []var;
        delete []maxx;

        return -2;
    }
    
    if (inputType == 1)
    {
        if (sscanf(argv[3], "%d", &m) != 1 || m <= 0)
        {
            cout<<"Data isn't correct"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
            delete []args;
            delete []var;
            delete []maxx;
            
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
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
            delete []args;
            delete []var;
            delete []maxx;
            
            return -2;
        }
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        args[i].n = n;
        args[i].matrix = matrix;
        args[i].vector = vector;
        args[i].result = result;
        args[i].var = var; 
        args[i].rank = i;
        args[i].threadsCount = threadsCount;
        args[i].retFlag = 0;
        args[i].flag = &flag;
        args[i].maxx = maxx;
        args[i].norm = 0;
        args[i].fin = fin;
        args[i].inputType = inputType;
    }
    
    t = getTime();
    
    for (i = 0; i < threadsCount; i++)
    {
        if (pthread_create(threads + i, 0, Solving, args + i))
        {
            cout<<"Can't create thread"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
            delete []var;
            delete []args;
            delete []maxx;
            
            return -1;
        }
    }
    
    for (i = 0; i < threadsCount; i++)
    {
        if (pthread_join(threads[i], 0))
        {
            cout<<"Can't wait thread"<<endl;
            
            if (inputType == 1)
                fclose(fin);
            
            delete []matrix;
            delete []vector;
            delete []result;
            delete []threads;
            delete []args;
            delete []var;
            delete []maxx;
            
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
            delete []var;
            delete []maxx;

            return -1;
        }
    }
    
    cout<<"Result:"<<endl;
    printResult(result, n, m);
    
    for (i = 0; i < threadsCount; ++i)
        residualNorm += args[i].norm;
    
    cout<<"Residual norm: "<<sqrt(residualNorm)<<endl;
    
    if (inputType == 2)
        cout<<"Error norm: "<<errorNorm(result, n)<<endl; ;
    
    cout<<"Solving time = "<<t<<" seconds"<<endl;
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []vector;
    delete []result;
    delete []threads;
    delete []var;
    delete []args;
    delete []maxx;
    
    return 0;
}

long double getTime()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
