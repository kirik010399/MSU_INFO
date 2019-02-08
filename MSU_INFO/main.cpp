#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "MatFun.hpp"
#include "SolvHead.hpp"

using namespace std;

int main(){
    int n, m;
    double *a;
    double *b;
    double *x;
    FILE* fin = NULL;
    clock_t t;
    int type;
    int retflag;
    int *index;
    
    cout<<"____Выберите тип ввода:____"<<endl<<"1 ____- из файла____," <<endl<<"2 ____- из формулы____"<<endl;
    
    if (scanf("%d", &type) != 1){
        cout<<"____Ошибка ввода____"<<endl;
        return -2;
    }
    
    if (type == 1){
        fin = fopen("input.txt", "r");
        
        if (!fin){
            cout<<"____Возникла проблема с файлом____"<<endl;
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0){
            cout<<"____Введено некорректное значение размера матрицы____"<<endl;
            fclose(fin);
            return -2;
        }
    }
    else if (type == 2){
        cout<<"____Введите размер матрицы: "<<endl;
        
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            cout<<"____Введено некорректное значение размера матрицы____"<<endl;
            return -2;
        }
    }
    else{
        cout<<"____Выбран неверный тип задания матрицы____"<<endl;
        return -2;
    }
    
    a = new double [n*n];
    b = new double [n];
    x = new double [n];
    index = new int[n];
    if (!(a && b && x && index)){
        cout<<"____Маловато памяти, введите матрицу поменьше____"<<endl;

        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []index;
        return -2;
    }
    
    retflag = enterData(a, b, n, fin);
    
    if (retflag == -1){
        cout<<"____Данные не верны____"<<endl;

        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []index;
        return -2;
    }
    
    cout<<"____Введите размер угла печати:____ "<<endl;
    
    if (scanf("%d", &m) != 1){
        cout<<"____Данные не верны____"<<endl;

        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete[]index;
        return -2;
    }
    
    printf("\n");
    
    t = clock();
    retflag = solveSystem(a, b, x, n, index);
    t = clock() - t;
    
    if (retflag != -1){
        cout<<"____Решение: "<<endl;
        printResult(x, n, m);
        
        if (type == 1){
            fseek(fin, 0, SEEK_SET);
            fscanf(fin,"%d", &n);
        }
        
        retflag = enterData(a, b, n, fin);
        
        cout<<"____Норма погрешности: "<<residualNorm(a, b, x, n)<<endl;
        
        if (type == 2)
            cout<<"____Норма ошибки: "<<errorNorm(x, n)<<endl;
        
        cout<<"____Время решения  = "<<t*1.0/CLOCKS_PER_SEC<<" секунд"<<endl;
    }
    else{
        printf("____Ошибка при решении системы____");
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []b;
        delete []x;
        delete []index;
        return -1;
    }
    
    if (type == 1)
        fclose(fin);
    
    delete []a;
    delete []b;
    delete []x;
    delete []index;
    return 0;
}
