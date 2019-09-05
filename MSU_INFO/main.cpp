#include <stdio.h>
#include <math.h>

double f(double x)
{
    return (x-10*10*10)*(x-1/10*1/10*1/10)
}

int main()
{
    long double a = 1, b = 10*10*10, c = 1;
    
    b += 1.0/(10*10*10);
    
    long double d = b*b-4*a*c;
    long double x1 = (-b+sqrt(d))/2;
    long double x2 = (-b-sqrt(d))/2;
    
//    x1<<2;
//    x2<<2;

    printf("%.16Lf %.16Lf\n", x1, x2);
    return 0;
}

