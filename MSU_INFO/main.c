#include <stdio.h>

int main(void)
{
    double sum1 = 0;
    
    for (int i = 1; i <= 1000; ++i)
    {
        int temp = i*i;
        sum1 += 1.0/temp;
    }
    
    double sum2 = 0;
    for (int i = 1000; i>=1; --i)
    {
        int temp = i*i;
        sum2 += 1.0/temp;
    }
    
    printf("%.16lf\n%.16lf\n", sum1, sum2);
    
    return 0;
}

