#include <stdio.h>
#include <math.h>

int main(void)
{
    double a = 1, b = 10, c = -20;
    
    double d = b*b-4*a*c;
    double x1 = (-b+sqrt(d))/2;
    double x2 = (-b-sqrt(d))/2;
    
    printf("%.16lf %.16lf\n", x1, x2);
    return 0;
}

