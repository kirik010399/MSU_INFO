#include <stdio.h>
#include <math.h>

long double f(double x)
{
    return (x-1000)*(x-0.001);
}

int main()
{
    long double a = 1, b = -1000.001, c = 1;
    
    long double d = b*b-4*a*c;
    double x1 = (b*b-d)/(2*a*(-b+sqrt(d)));
    double x2 = (b*b-d)/(2*a*(-b-sqrt(d)));
    
    printf("%.16lf %.16Lf\n%.16lf %.16Lf\n", x1, f(x1), x2, f(x2));
    return 0;
}

