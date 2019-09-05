#include <stdio.h>
#include <math.h>

int main()
{
    long double a = 1, b = 10, c = -20;
    
    long double d = b*b-4*a*c;
    long double x1 = (-b+sqrt(d))/2;
    long double x2 = (-b-sqrt(d))/2;
    
//    x1<<2;
//    x2<<2;

    printf("%.16Lf %.16Lf\n", x1, x2);
    return 0;
}

