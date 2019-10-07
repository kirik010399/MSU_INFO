#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void printScalarMatrix(FILE *fout, int n)
{
    double h = 1.0/n;//заводим переменную h, 1.0 важно, чтобы не было целочисленного деления
    double maxSc = 0;//переменная для максимального скалярного произведения
    int maxScX, maxScY;//переменные для номеров векторов, на которых оно достигается
    double sum = 0;//переменная для хранения временной суммы из скалярного произведения
        
    sum += cos(M_PI*0*0*h) * cos(M_PI*0*0*h) * h/2;
    
    for (int k = 1; k <= n-1; ++k)
        sum += cos(M_PI*k*0*h) * cos(M_PI*k*0*h) * h;
    
    sum += cos(M_PI*n*0*h) * cos(M_PI*n*0*h) * h/2;//блок подсчета скалярного произведения для 0 и 0 вектора, вынесено из цикла, чтобы присвоить изначальное значение максимуму
    
    maxSc = sum;//присваиваем изначально значение максимуму
    maxScX = 0;//присваиваем изначальное значение номеру первого вектора, на котором достигнут максимум
    maxScY = 0;//присваиваем изначальное значение номеру второго вектора, на котором достигнут максимум
        
    for (int i = 0; i <= n; ++i)//бежим по всем векторам из условия
    {
        for (int j = 0; j <= n; ++j)//бежим по всем векторам из условия, итого бежим по всем парам вектором
        {
            sum = 0;
            
            sum += cos(M_PI*0*i*h) * cos(M_PI*0*j*h) * h/2;
            
             for (int k = 1; k <= n-1; ++k)
                   sum += cos(M_PI*k*i*h) * cos(M_PI*k*j*h) * h;//k - номер компоненты вектора, i и j - номера векторов
            
            sum += cos(M_PI*n*i*h) * cos(M_PI*n*j*h) * h/2;//блок подсчета скалярного произведения
        
            if (sum > maxSc)//если нашли скалярное произведение больше максимума - обновляем максимум и номера векторов, на котором он достигнут
            {
                maxSc = sum;
                maxScX = i;
                maxScY = j;
            }
            
            fprintf(fout, "%lf ", sum);//вывели очередное скалярное произведения
        }
        fprintf(fout, "\n");//перевели строку
    }
    //итого в файле получаем диагональную матрицу => вектора ортогональны
    
    fprintf(fout, "\n%lf %d %d\n", maxSc, maxScX, maxScY);//вывели максимальное скалярное проивезедения и вектора, на которых оно достигнуто
}

void generateMatrix(double *a, int n)
{
    int i, j;
    double h = 1.0/n;
    double h2 = h*h;
    int n1 = n+1;
    
    for (i = 0; i <= n; ++i)
    {
        for (j = 0; j <= n; ++j)
        {
            if (i == 0)
            {
                if (j == 0)
                    a[i*n1+j] = -2.0/h2;
                else if (j == 1)
                    a[i*n1+j] = 2.0/h2;
                else
                    a[i*n1+j] = 0.0;
            }
            else if (i == n)
            {
                if (j == n)
                    a[i*n1+j] = -2.0/h2;
                else if (j == n-1)
                    a[i*n1+j] = 2.0/h2;
                else
                    a[i*n1+j] = 0.0;
            }
            else
            {
                if (j == i)
                    a[i*n1+j] = -2.0/h2;
                else if (j == i-1 || j == i+1)
                    a[i*n1+j] = 1.0/h2;
                else
                    a[i*n1+j] = 0.0;
            }
            printf("%lf ", a[i*n1+j]);
        }
        printf("\n");
    }
    printf("\n");
}

double calculateSubNorm(double *a, int m, int n)
{
    int i, j;
    double res = 0;
    double sum;
    double y_j, y_i;
    double h = 1.0/n;
    double h2 = h*h;
    int n1 = n+1;
    
    double lam = 4*sin(M_PI*m*h/2)*sin(M_PI*m*h/2)/h2;

    for (i = 0; i <= n; ++i)
    {
        sum = 0.0;
        
        y_i = cos(M_PI*i*m*h);//m - номер вектора, i - номер компоненты
        
        for (j = 0; j <= n; ++j)
        {
            y_j = cos(M_PI*j*m*h);//m - номер вектора, j - номер компоненты

            sum += a[i*n1+j] * y_j;
        }
        
        sum -= lam * y_i;
        
        printf("%lf ", sum);
        
        res += sum * sum;
    }
    printf("\n"); 
    
    return sqrt(res);
}

double calculateNorm(double *a, int m, int n)
{
    int i, j;
    double res = 0;
    double sum;
    double y_j;
    double h = 1.0/n;
    int n1 = n+1;
    
    for (i = 0; i <= n; ++i)
    {
        sum = 0.0;
            
        for (j = 0; j <= n; ++j)
        {
            y_j = cos(M_PI*j*m*h);//m - номер вектора, j - номер компоненты

            sum += a[i*n1+j] * y_j;
        }
                        
        res += sum * sum;
    }
    
    return sqrt(res);
}

void calculateMaxResidual(double *a, FILE *fout, int n)
{
    int m;
    double subNorm, norm;
    double res;
    double maxNorm;
    int maxNormIndex;
    
    subNorm = calculateSubNorm(a, 0, n);
    norm = calculateNorm(a, 0, n);
    
    maxNorm = subNorm/norm;
    maxNormIndex = 0;
    
    for (m = 1; m <= n; ++m)
    {
        subNorm = calculateSubNorm(a, m, n);
        norm = calculateNorm(a, m, n);
        
        res = subNorm/norm;
        
        if (res > maxNorm)
        {
            maxNorm = res;
            maxNormIndex = m;
        }
    }
    
    fprintf(fout, "%lf %d\n", maxNorm, maxNormIndex);
}

int main(void)
{
    FILE *fin, *fout;//создали переменные для файлов, fin - количество точек, fout - файл, куда мы все будем выводить
    int n;//переменная для количества точек
    double *a;//матрица из условий
        
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");//открыли файлы
    
    fscanf(fin, "%d", &n);//прочитали количество точек
    
    a = (double*)malloc((n+1)*(n+1) * sizeof(int));

    printScalarMatrix(fout, n);//вызвали функцию печати матрицы
    generateMatrix(a, n);//запускаем функцию генерирования матрицы из условия
    calculateMaxResidual(a, fout, n);
        
    free(a);
    fclose(fin);
    fclose(fout);
}


