#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrixUtils.h"
#include "calculatingManager.h"

int main()
{
    int n, m;
    double *matrix;
    double *vector;
    FILE* fin = NULL;
    clock_t t;
    int inputType;
    int returnFlag;
    int retSize = 0;
    double eps;
    struct myPair p;
    double left, right;
    
    printf("Choose type of data:\n1 - from file, \n2 - from formula\n");

    if (scanf("%d", &inputType) != 1)//считываем тип ввода
    {
        printf("Data isn't correct\n");
        return -2;
    }
         
    if (inputType == 1)//если из файла - 1
    {
        fin = fopen("input.txt", "r");
        
        if (!fin)
        {
            printf("File don't exist\n");
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0)//считываем размер матрицы
        {
            printf("Data isn't correct\n");
            fclose(fin);
            return -2;
        }
    }
    else if (inputType == 2)//если из формулы - 2
    {
        printf("Enter size: \n");
    
        if (scanf("%d", &n) != 1 || n <= 0)//считываем размер матрицы
        {
            printf("Data isn't correct\n");
            return -2;
        }
    }
    else//если ввели некорректный тип ввода
    {
        printf("Input type isn't correct\n");
        return -2;
    }
    
    matrix = (double*)malloc(n * n * sizeof(double));//завели матрицу
    vector = (double*)malloc(n * sizeof(double));//завели массив сз
    
    if (!(matrix && vector))//не хватило памяти на выделение
    {
        printf("No memory, enter matrix with less dimensions\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }

    returnFlag = enterMatrix(matrix, n, fin);//ввели матрицы (из файла или из формулу) <returnFlag> - если некорректные данные
    
    if (returnFlag == -1)//если некорректные данные
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }
    
    printf("Enter size of printing vector: ");
    
    if (scanf("%d", &m) != 1 || m <= 0)//размер вывода (если ввели 1000 то выведет первые m)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }
    
    printMatrix(matrix, n, m);//печать матрицы
    
    printf("Enter left and right borders:\n") ;

    if (scanf("%lf", &left) != 1 || scanf("%lf", &right) != 1 || right < left || fabs(right - left) < 1e-100)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }

    printf("Enter accuracy: \n");
    
    if (scanf("%lf", &eps) != 1 || eps <= 0)
    {
        printf("Data isn't correct\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }

    t = clock();//сняли время
    retSize = calculateValues(matrix, vector, left, right, eps, n);//сама функция подсчета сз
    t = clock() - t;//вычли из нового предыдущее
    
    if (retSize == 0)
    {
        printf("No values on this interval\n");
        
        if (inputType == 1)
            fclose(fin);
        
        free(matrix);
        free(vector);
        
        return -2;
    }
    
    printf("\nValues vector:\n");
    printVector(vector, n, m, retSize);
    
    if (inputType == 1)//курсор в файле установили в начало чтобы заново считать матрицу, потому что та испорчена во время подсчета сз
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n); //считали n еще раз так как оно есть в файле(сдвинуть курсор)
    }
    
    returnFlag = enterMatrix(matrix, n, fin);//ввели заново матрицу
    p = residualNorm(matrix, vector, n);//посчитали норму погрешности
    
    printf("\nThe norm of residual: in first inv: %e, in second inv: %e\n", p.inv1, p.inv2);//вывели ее
    
    printf("Calculating time =  %lu milliseconds\n", t);//вывели время

    if (inputType == 1)
        fclose(fin);
    
    free(matrix);
    free(vector);
    
    return 0;
}
