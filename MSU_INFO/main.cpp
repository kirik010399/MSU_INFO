#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "calculatingManager.hpp"
#include <algorithm>

using namespace std;

int main()
{
    int n, m;
    double *matrix;
    double *vector;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    double eps;
    double left, right;
    int k = 0;
    pair<double, double> p;
    
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
    
    if (!(matrix && vector))
    {
        cout<<"No memory, enter matrix with less dimensions"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }

    returnFlag = enterMatrix(matrix, n, fin);
    
    if (returnFlag == -1)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }
    
    cout<<"Enter size of printing vector: ";
    
    if (scanf("%d", &m) != 1 || m <= 0)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }
    
    printf("Enter left and right borders:\n") ;
    
    if (scanf("%lf", &left) != 1 || scanf("%lf", &right) != 1 || right < left || fabs(right - left) < 1e-100)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }
    
    cout<<"Enter accuracy: ";
    
    if (scanf("%lf", &eps) != 1 || eps <= 0)
    {
        cout<<"Data isn't correct"<<endl;
        
        if (inputType == 1)
            fclose(fin);
        
        delete []matrix;
        delete []vector;
        
        return -2;
    }
    
    t = clock();
    calculateValues(matrix, vector, left, right, eps, n, &k);
    t = clock() - t;
    
    cout<<endl<<"Values vector:"<<endl;
    printVector(vector, n, m, k);
    
    if (inputType == 1)
        fseek(fin, 1, SEEK_SET);
    
    returnFlag = enterMatrix(matrix, n, fin);
    p = residualNorm(matrix, vector, n);
    
    cout<<endl<<"The norm of residual: in first inv: "<<p.first<<", in second inv: "<<p.second<<endl;
    
    cout<<"Calculating time =  "<< t << " milliseconds"<<endl;

    if (inputType == 1)
        fclose(fin);
    
    delete []matrix;
    delete []vector;
    
    return 0;
}
