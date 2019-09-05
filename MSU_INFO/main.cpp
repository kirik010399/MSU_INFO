#include <stdio.h>
#include <math.h>
#include <time.h>

double myExp (double x, int n);

int main(void)
{
    double x;
    int n;
    
    printf("Enter n: ");
    scanf("%d", &n);

    x = 1;
    printf("Correct: %.16f\n", exp(x));
    printf("Result : %.16f\n", myExp(x, n));
    
    x = -15;
    printf("Correct: %.16f\n", exp(x));
    printf("Result : %.16f\n", myExp(x, n));
}

double myExp (double x, int n)
{
    double elem, sum = 0;
    int i;
    
    elem = x;
    sum = 1 + x;
    
    for (i = 2; i <= n; ++i)
    {
        elem *= x/i;
        sum += elem;
    }
    
    return sum;
}
