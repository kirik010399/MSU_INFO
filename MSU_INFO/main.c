#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double getScalarComponent(double k, double m, int n);
void printScalarMatrix(FILE *fout, int n);
void generateMatrix(double *a, int n);
double calculateSubNorm(double *a, int m, int n);
double calculateNorm(double *a, int m, int n);
void calculateMaxResidual(double *a, FILE *fout, int n);

double getScalarComponent(double k, double m, int n)
{
    double h = 1.0/n;
    
    if (k == 0 || k == n)
        return cos(M_PI*k*m*h)*sqrt(h/2);
    else
        return cos(M_PI*k*m*h)*sqrt(h);//модифицированное скалярное произведение
}

int main(void)
{
    FILE *fin, *fout;//создали переменные для файлов, fin - количество точек, fout - файл, куда мы все будем выводить
    int n;//переменная для количества точек
    double *a;//матрица из условий
        
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");//открыли файлы
    
    fscanf(fin, "%d", &n);//прочитали количество точек
    
    a = (double*)malloc((n+1)*(n+1) * sizeof(double));//выделили память под матрицу условий

    printScalarMatrix(fout, n);//вызвали функцию печати матрицы
    generateMatrix(a, n);//запускаем функцию генерирования матрицы из условия
    calculateMaxResidual(a, fout, n);//запускаем функцию подсчета максимальной нормы
        
    free(a);
    fclose(fin);
    fclose(fout);
}


void printScalarMatrix(FILE *fout, int n)
{
    double maxSc = 0;//переменная для максимального скалярного произведения
    int maxScX, maxScY;//переменные для номеров векторов, на которых оно достигается
    double sum = 0;//переменная для хранения временной суммы из скалярного произведения
    int k, i, j;
    
    for (k = 0; k <= n; ++k)
        sum += getScalarComponent(k, 0, n) * getScalarComponent(k, 0, n);//блок подсчета скалярного произведения для 0 и 0 вектора, вынесено из цикла, чтобы присвоить изначальное значение максимуму
    
    maxSc = sum;//присваиваем изначально значение максимуму
    maxScX = 0;//присваиваем изначальное значение номеру первого вектора, на котором достигнут максимум
    maxScY = 0;//присваиваем изначальное значение номеру второго вектора, на котором достигнут максимум
        
    for (i = 0; i <= n; ++i)//бежим по всем векторам из условия
    {
        for (j = 0; j <= n; ++j)//бежим по всем векторам из условия, итого бежим по всем парам вектором
        {
            sum = 0;
            
             for (k = 0; k <= n; ++k)
                   sum += getScalarComponent(k, i, n) * getScalarComponent(k, j, n);//k - номер компоненты вектора, i и j - номера векторов, блок подсчета скалярного произведения
        
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
    
    fprintf(fout, "\nMax scalar product: %lf, index of first vector: %d, index of second vector: %d\n", maxSc, maxScX, maxScY);//вывели максимальное скалярное проивезедения и вектора, на которых оно достигнуто
}

void generateMatrix(double *a, int n)
{
    int i, j;
    double h = 1.0/n;
    double h2 = h*h;//хранит h^2
    int n1 = n+1;//хранит n+1 для удобной работы с матрицами
    
    for (i = 0; i <= n; ++i)//бежим по строкам матрицы, i - номер строки
    {
        for (j = 0; j <= n; ++j)//бежим по столбцам матрицы, j - номер столбца
        {
            if (i == 0)//заполняем отдельно первую строку
            {
                if (j == 0)//заполняем ее первый элемент
                    a[i*n1+j] = -2.0/h2;
                else if (j == 1)//заполняем ее второй элемент
                    a[i*n1+j] = 2.0/h2;
                else//заполняем остальные элементы
                    a[i*n1+j] = 0.0;
            }
            else if (i == n)//заполняем отдельно последнюю строку
            {
                if (j == n)//заполянем последний элемент
                    a[i*n1+j] = -2.0/h2;
                else if (j == n-1)//заполняем предпоследний элемент
                    a[i*n1+j] = 2.0/h2;
                else//заполняем остальные элементы
                    a[i*n1+j] = 0.0;
            }
            else
            {
                if (j == i)//заполняем диагональный элемент
                    a[i*n1+j] = -2.0/h2;
                else if (j == i-1 || j == i+1)//заполняем элемент левее диагонального и правее диагонального
                    a[i*n1+j] = 1.0/h2;
                else//заполняем остальные элементы
                    a[i*n1+j] = 0.0;
            }
            printf("%lf ", a[i*n1+j]);
        }
        printf("\n");
    }
    printf("\n");
}

void calculateMaxResidual(double *a, FILE *fout, int n)
{
    int m;
    double subNorm, norm;//norm - норма матрицы Ay, subNorm - норма матрицы Ay-lam*y
    double temp;//частное этих норм
    double maxNorm;//максимальная норма
    int maxNormIndex;//номер вектора, на котором она достигается
    //далее выносим из цикла подсчет для нулевого вектора, чтобы присвоить изначальное значение максимум
    subNorm = calculateSubNorm(a, 0, n);//считаем норму Ay-lam*y
    norm = calculateNorm(a, 0, n);//считаем нормм Ay
    
    maxNorm = subNorm/norm;//инициализурем максимум их частным
    maxNormIndex = 0;//на данный момент максимум будет как раз на 0 вектора
    
    printf("%lf ", maxNorm);
    
    for (m = 1; m <= n; ++m)//запускаем цикл по остальным векторам, внутри него делаем то же самое
    {
        subNorm = calculateSubNorm(a, m, n);
        norm = calculateNorm(a, m, n);
        
        temp = subNorm/norm;
        printf("%lf ", temp);
        if (temp > maxNorm)//если новое частное больше максимального, то обновляем максимальный и индекс на котором он достигается
        {
            maxNorm = temp;
            maxNormIndex = m;
        }
    }
    printf("\n");
    
    fprintf(fout, "Max norm: %lf, index of vector: %d\n", maxNorm, maxNormIndex);
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
    
    double lam = 4 * sin(M_PI*m*h/2) * sin(M_PI*m*h/2)/h2;//заполнили lam

    for (i = 0; i <= n; ++i)//бежим по всем строкам матрицы
    {
        sum = 0.0;
        
        y_i = getScalarComponent(i, m, n);//m - номер вектора, i - номер компоненты
        
        //считаем Ay
        for (j = 0; j <= n; ++j)
        {
            y_j = getScalarComponent(j, m, n);//m - номер вектора, j - номер компоненты
            
            sum += a[i*n1+j] * y_j;//поэлементно умножаем строку A на y
        }
        
        sum += lam * y_i;//прибавляем lam*y
        res += sum * sum;//берем квадрат полученной компоненты итогового вектора
    }
    
    return sqrt(res);//возвращаем корень из суммы квадратов
}

double calculateNorm(double *a, int m, int n)
{
    int i, j;
    double res = 0;
    double sum;
    double y_j;
    int n1 = n+1;
    
    for (i = 0; i <= n; ++i)//бежим по строкам матрицы
    {
        sum = 0.0;
        //считаем Ay
        for (j = 0; j <= n; ++j)
        {
            y_j = getScalarComponent(j, m, n);//m - номер вектора, j - номер компоненты

            sum += a[i*n1+j] * y_j;//поэлементно умножаем строку A на y
        }
                        
        res += sum * sum;//берем квадрат полученной компоненты итогового вектора
    }
    
    return sqrt(res);//возвращаем корень из суммы квадратов
}
