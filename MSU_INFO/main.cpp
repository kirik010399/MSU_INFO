#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matr.hpp"
#include "oborot.hpp"

int main(int argc, char **argv)
{
    int n, m, k;
    double *a;
    double *a_obr;
    double *d;
    char filename[120];
    FILE* in = NULL;
    clock_t t;
    int val;
    
    if (argc < 4)
    {
        printf("Правильный формат запуска программы: ./a.out n m k filename (опционально)");
        return -1;
    }
    
    val = sscanf(argv[1], "%d", &n);
    if (val != 1)
    {
        printf("Правильный формат запуска программы: ./a.out n m k filename (опционально)");
        return -1;
    }
    val = sscanf(argv[2], "%d", &m);
    if (val != 1)
    {
        printf("Правильный формат запуска программы: ./a.out n m k filename (опционально)");
        return -1;
    }
    val = sscanf(argv[3], "%d", &k);
    if (val != 1)
    {
        printf("Правильный формат запуска программы: ./a.out n m k filename (опционально)");
        return -1;
    }
    
    if (!((argc == 5 && k == 0) || (argc == 4 && k != 0)))
    {
        printf("Правильный формат запуска программы: ./a.out n m k filename (опционально)");
        return -1;
    }
        
    if (k == 0)
    {
        if(sscanf(argv[4], "%s", filename) != 1)
        {
            printf("Правильный формат запуска программы: ./a.out n m k filename (опционально)");
            return -1;
        }
            
        in = fopen(filename, "r");
        
        if (!in)
        {
            fclose(in);
            return -2;
        }
    }
    
    a = (double*)malloc((n*(n+1)/2) * sizeof(double));
    a_obr = (double*)malloc((n*(n+1)/2) * sizeof(double));
    d = (double*)malloc(n * sizeof(double));

    val = vvod_matr(a, n, k, in);
    
    if (val < 0)
    {
        if (k == 0)
            fclose(in);
        free(a);
        free(a_obr);
        free(d);
        return -1;
    }
    
    printf("Матрица:\n");
    pechat_matr(a, n, m);
    
    t = clock();
    val = oborot(a, a_obr, d, n);
    t = clock() - t;
    
    if (val == 0)
    {
        printf("Обратная:\n");
        pechat_matr(a_obr, n, m);
        if (k == 0)
            fseek(in, 0, SEEK_SET);
        val = vvod_matr(a, n, k, in);
        printf("Прошло: %f с.\n", (double)t/CLOCKS_PER_SEC);
        printf("Погрешность: %10.3e\n", norma(a, a_obr, n));
    }
    else
    {
        printf("Матрица вырождена.\n");
        
        if (k == 0)
            fclose(in);
        free(a);
        free(a_obr);
        free(d);
        
        return -1;
    }
    
    if (k == 0)
        fclose(in);
    free(a);
    free(a_obr);
    free(d);

    return 0;
}
