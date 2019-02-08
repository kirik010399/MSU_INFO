#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "MatFun.hpp"
#include "SolvHead.hpp"

using namespace std;

int main(){
    int n;
    double *a;
    double *res;
    FILE* fin = NULL;
    clock_t t;
    int type;
    int retflag;
    double eps;
    int k;
    pair<double, double> p;
    
    cout<<"____Выберите тип ввода:____"<<endl<<"1 ____- из файла____," <<endl<<"2 ____- из формулы____"<<endl;
    
    if (scanf("%d", &type) != 1)  {
        cout<<"____Ошибка ввода____"<<endl;
        return -2;
    }
    
    if (type == 1)  {
        fin = fopen("input.txt", "r");
        
        if (!fin)  {
            cout<<"____Возникла проблема с файлом____"<<endl;
            fclose(fin);
            return -1;
        }
        
        if (fscanf(fin, "%d", &n) != 1 || n <= 0)  {
            cout<<"____Введено некорректное значение размера матрицы____"<<endl;
            fclose(fin);
            return -2;
        }
    }
    else if (type == 2)  {
        cout<<"____Введите размер матрицы: "<<endl;
        
        if (scanf("%d", &n) != 1 || n <= 0)  {
            cout<<"____Введено некорректное значение размера матрицы____"<<endl;
            return -2;
        }
    }
    else  {
        cout<<"____Выбран неверный тип задания матрицы____"<<endl;
        return -2;
    }
    
    a = new double [n*n];
    res = new double [n];
    
    if (!(a && res))  {
        cout<<"____Маловато памяти, введите матрицу поменьше____"<<endl;
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []res;
        
        return -2;
    }
    
    retflag = enterData(a, n, fin);
    
    if (retflag == -1)  {
        cout<<"____Данные не верны____"<<endl;
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []res;
        
        return -2;
    }
    
    cout<<"____Введите номер собственного значения: "<<endl;
    
    if (scanf("%d", &k) != 1 || k <= 0 || k > n)  {
        cout<<"____Данные не верны____"<<endl;
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []res;
        
        return -2;
    }
    
    cout<<"____Введите точность: ";
    
    if (scanf("%lf", &eps) != 1 || eps <= 0)  {
        cout<<"____Данные не верны____"<<endl;
        
        if (type == 1)
            fclose(fin);
        
        delete []a;
        delete []res;
        
        return -2;
    }
    
    t = clock();
    calculateValues(a, res, eps, k, n);
    t = clock() - t;
    
    cout<<endl<<"____K-ое собственное значение:"<<endl;
    printResult(res, k);
    
    if (type == 1)
    {
        fseek(fin, 0, SEEK_SET);
        fscanf(fin, "%d", &n);
    }
    
    retflag = enterData(a, n, fin);
    p = residualNorm(a, res, n);
    
    cout<<endl<<"____Норма погрешности:"<<endl<<"____В первом инварианте : "<<p.first<<endl<<"____Во втором инварианте: "<<p.second<<endl;
    
    cout<<"____Время решения  = "<<t*1.0/CLOCKS_PER_SEC<<" секунд"<<endl;
    
    if (type == 1)
        fclose(fin);
    
    delete []a;
    delete []res;
    
    return 0;
}
