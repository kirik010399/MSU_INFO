#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "solvingManager.hpp"

using namespace std;

int main()
{
    int n, m;
    double *matrix;
    double *vector;
    double *result;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    
    cout<<"Choosy type of entering data: 1 - from file, 2 - from formula"<<endl;
    cin>>inputType;
    
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
    
    matrix = new double [n*n];
    vector = new double [n];
    result = new double [n];
    
    if (!(matrix && vector && result))
    {
        cout<<"No memory, enter matrix with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        
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
        
        return -2;
    }
    
    cout<<"Enter size of printing result: ";
    cin>>m;
    cout<<endl; 
    
    t = clock();
    returnFlag = solveSystem(matrix, vector, result, n);
    t = clock() - t;
    
    if (returnFlag)
    {
        cout<<"Result vector:"<<endl;
        printResult(result, n, m);
        
        if (inputType == 1)
            fseek(fin, 1, SEEK_SET);
        
        returnFlag = enterData(matrix, vector, n, fin);
        
        cout<<endl<<"The norm of residual: "<<residualNorm(matrix, vector, result, n)<<endl;
        
        if (inputType == 2)
            cout<<"The norm of error: "<<errorFunction(result, n)<<endl;
        
        cout<<"Solving time =  "<< t << " milliseconds"<<endl;
    }
    else
    {
        cout<<"Error while solving system"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        delete []result;
        
        return -1;
    }
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []vector;
    delete []result;
    
    return 0;
}
