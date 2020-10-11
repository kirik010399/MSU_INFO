#include <stdio.h>
#include <time.h>
#include <math.h>
#include "func.hpp"
#include "solve.hpp"

int main(int argc, char **argv)
{
int n, m, k;
double *a;
double *b;
double *x;
int *ind;
char filename[120];
FILE* in = nullptr;
clock_t t;
int q;

if(argc < 4)
    {
    printf("Программа запущена неверно. Правильно: ./a.out n m k filename");
    return -1;
    }
    
q=sscanf(argv[1], "%d", &n);
if (q!=1)
    {
    printf("Программа запущена неверно. Правильно: ./a.out n m k filename");
    return -1;
    }
    
q=sscanf(argv[2], "%d", &m);
if (q!=1)
    {
    printf("Программа запущена неверно. Правильно: ./a.out n m k filename");
    return -1;
    }
    
q=sscanf(argv[3], "%d", &k);
if (q!=1)
    {
    printf("Программа запущена неверно. Правильно: ./a.out n m k filename");
    return -1;
    }
    
if (k==0 && argc<5)
    {
    printf("Программа запущена неверно. Правильно: ./a.out n m k filename");
    return -1;
    }

if (k==0)
    {
    if(sscanf(argv[4], "%s", filename) != 1)
        {
        printf("Программа запущена неверно. Правильно: ./a.out n m k filename");
        return -1;
        }
        
    in = fopen(filename, "r");
    if(in==NULL)
        {
        printf("Нет файла");
        return -1;
        }
    }

a = new double [n*n];
b = new double [n];
x = new double [n];
ind = new int [n];
q = enter(a,b,n,k,in);

if (q<0)
    {
    printf("Некорректные данные.\n");
    if (k==0)
        fclose(in);
    delete []a;
    delete []b;
    delete []x;
    delete []ind;
    return -2;
    }

printf("Матрица:\n");
print(a,n,n,m);
t = clock();
q = solve(a, b, x, ind, n);
t = clock() - t;
    
if (q==0)
    {
    printf("Решение:\n");
    print(x, 1, n, m);
    printf("\nВремя: %f\n", t*1.0/CLOCKS_PER_SEC);
    if (k==0)
        fseek(in, 0, SEEK_SET);
    q = enter(a,b,n,k,in);
    printf("Невязка: %10.3e\n", norm(a,b,x,n));
    printf("Ошибка: %10.3e\n", error(x, n));
    }
else
    {
    printf("Вырожденная матрица\n");
    if (k==0)
        fclose(in);
    delete []a;
    delete []b;
    delete []x;
    delete []ind;
    return -1;
    }

if (k==0)
    fclose(in);
delete []a;
delete []b;
delete []x;
delete []ind;

return 0;
}
