#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrixFunctions.hpp"
#include "solvingFunctions.hpp"

using namespace std;

int main()
{
    int n, m;
    double *a;
    double *b;
    double *x;
    FILE* fin = NULL;
    clock_t t;
    int type;
    int ret;
    
    printf("Choosy type of data:\n1 - from file, \n2 - from formula\n");
    
    if (scanf("%d", &type) != 1)
    {
        printf("Data isn't correct\n");
        return -2;
    }

    if (type == 1)
    {
        fin = fopen("input.txt", "r");
        
        if (!fin)
        {
            printf("File don't exist\n");
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0)
        {
            printf("Data isn't correct\n");
            fclose(fin);
            return -2;
        }
    }
    else if (type == 2)
    {
        printf("Enter size of matrix: ");
    
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Data isn't correct\n");
            return -2;
        }
    }
    else
    {
        printf("Data isn't correct\n");
        return -2;
    }
    
    a = new double [n*n];
    b = new double [n];
    x = new double [n];
    
    if (!(a && b && x))
    {
        printf("No memory, enter matrix with less dimensions\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        
        return -2;
    }

    ret = enterData(a, b, n, fin);
    
    if (ret == -1)
    {
        printf("Data isn't correct\n");

        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        
        return -2;
    }
    
    printf("Enter size of printing: ");

    if (scanf("%d", &m) != 1)
    {
        printf("Data isn't correct\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        
        return -2;
    }
        
    printf("\n");
    
    t = clock();
    ret = solveSystem(a, b, x, n);
    t = clock() - t;
    
    if (ret != -1)
    {
        printf("Result:\n");
        printResult(x, n, m);
        
        if (type == 1)
            fseek(fin, 1, SEEK_SET);
        
        ret = enterData(a, b, n, fin);
        
        printf("\nInaccuracy norm: %f\n", inaccuracyNorm(a, b, x, n));
        
        if (type == 2)
            printf("Error norm: %f\n", errorNorm(x, n));
        
        printf("Solving time =  %lu seconds\n", t/CLOCKS_PER_SEC);
    }
    else
    {
        printf("Error while solving system\n");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        
        return -1;
    }
    
    if (type == 1)
        fclose(fin);
    
    delete []a;
    delete []b;
    delete []x;
    
    return 0;
}
