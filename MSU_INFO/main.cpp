#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "invertingManager.hpp"

using namespace std;

int main()
{
    int n;
    double *matrix;
    double *inverseMatrix;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    
    cout<<"Choosy type of entering data: 1 - from file, 2 - from formula"<<endl;
    cin>>inputType;
    
    if (inputType == 1)
    {
        fin = fopen("input.txt", "r");//TODO
        
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
        cin>>n; //TODO
    }
    
    matrix = new double [n*n];
    inverseMatrix = new double [n*n];
    
    //TODO CHECKING OF MEMORY

    returnFlag = enterMatrix(matrix, n, fin);
    
    cout<<"Entering matrix:"<<endl;
    printMatrix(matrix, n);
    cout<<endl; 
    
    t = clock();
    returnFlag = invertMatrix(matrix, inverseMatrix, n);
    t = clock() - t;
    
    if (returnFlag)
    {
        printMatrix(inverseMatrix, n);
        cout<<"Inversion time= %.2f sec"<< (double)t/CLOCKS_PER_SEC;
    }
    else
    {
        cout<<"error while inverting matrix";
    }
    
    delete []matrix;
    delete []inverseMatrix;
    
    return 0;
}
