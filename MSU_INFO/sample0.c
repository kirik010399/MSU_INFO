#include <stdio.h>
#include <stdlib.h>

double inc(double a);

int main(void)
{
    double a, b;
    
    a = 0;
    b = inc(a);
    
    printf("%lf %lf\n", a, b);
    
    return 0;
}

double inc(double a)
{
    double b;
    ++a;
    b = a;
    return b;
}

