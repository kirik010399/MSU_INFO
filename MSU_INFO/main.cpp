#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "invertingManager.hpp"

using namespace std;

int main()
{
    int n, m;
    double *matrix;
    double *inverseMatrix;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    
//    cout<<"Enter size: ";
//    cin>>n;
    
    cout<<"Choosy type of entering data: 1 - from file, 2 - from formula"<<endl;
    cin>>inputType;
    
    if (inputType == 1)
    {
        fin = fopen("input.txt", "r");
        
        if (!fin)
        {
            printf("File don't exist");
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1)
        {
            printf("Data isn't correct");
            fclose(fin);
            return -2;
        }
    }
    else
    {
            cout<<"Enter size: ";
            cin>>n;
    }
    
    matrix = new double [n*n];
    inverseMatrix = new double [n*n];
    
    if (!(matrix && inverseMatrix))
    {
        cout<<"No memory, enter matrix with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        
        return -2;
    }

    returnFlag = enterMatrix(matrix, n, fin);
    
    if (returnFlag == -1)
    {
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []inverseMatrix;
        
        return -2;
    }
    
    cout<<"Enter size of priting matrix: ";
    cin>>m;
    
    cout<<endl<<"Entering matrix:"<<endl;
    printMatrix(matrix, n, m);
    cout<<endl; 
    
    t = clock();
    returnFlag = invertMatrix(matrix, inverseMatrix, n);
    t = clock() - t;
    
    if (returnFlag)
    {
        cout<<"Inverse Matrix:"<<endl; 
        printMatrix(inverseMatrix, n, m);
        
        if (inputType == 1)
            fseek(fin, 1, SEEK_SET);
        
        returnFlag = enterMatrix(matrix, n, fin);
        
        cout<<endl<<"The norm of residual: "<<residualNorm(matrix, inverseMatrix, n)<<endl;
        
        cout<<"Inversion time =  "<< t << " milliseconds"<<endl;
    }
    else
    {
        cout<<"Error while inverting matrix"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        delete []matrix;
        delete []inverseMatrix;
        
        return -1;
    }
    
    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []inverseMatrix;
    
    return 0;
}
