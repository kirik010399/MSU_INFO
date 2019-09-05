#include <stdio.h>
#include <math.h>
#include <time.h>

double myExp (double x);

int main(void)
{
    double x;
    
    x = 1;
    printf("Correct: %.16f\n", exp(x));
    printf("Result : %.16f\n", myExp(x));
    
    x = -15;
    printf("Correct: %.16f\n", exp(x));
    x = 15;
    printf("Result : %.16f\n", 1.0/myExp(x));
}

double myExp (double x)
{
    double elem, sum = 0, sum1;
    int i;
    
    double eps = 1e-16;
    
    elem = x;
    sum1 = 1;
    sum = 1 + x;
    i = 2;
    while(fabs(sum-sum1)/sum > eps)
    {
        sum1 = sum;
        elem *= x/i;
        sum += elem;
        ++i;
    }
    
    return sum;
}
