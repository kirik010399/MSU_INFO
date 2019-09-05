#include <stdio.h>

int main(void)
{
    double sum1 = 0;
    
    for (int i = 2; i <= 1000; ++i)
    {
        int temp = (i-1)*(i+1);
        sum1 += 1.0/temp;
    }
    
    double sum2 = 0;
    for (int i = 1000; i>=2; --i)
    {
        int temp = (i-1)*(i+1);
        sum2 += 1.0/temp;
    }
    
    double res = 3001*1.0/4004;
    printf("Correct: %.16lf\nLeft->Right: %.16lf\nRight->left: %.16lf\n", res, sum1, sum2);
    
    return 0;
}

