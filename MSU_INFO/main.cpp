#include <iostream>
#include <stdio.h>
#include <math.h>

int n = 10;
double h = 1.0/(n-1);

double eigenValue(int m)
{
    return 4/(h*h) * sin(M_PI*h*(2*m-1)/4)*sin(M_PI*h*(2*m-1)/4);
}

int main()
{
    double maxValue = 0;
    double maxValueIndex = 0;
    double tau = 1.0/n;
    
    for (int m = 1; m <= n-1; ++m)
    {
        printf("%lf %lf %lf\n", eigenValue(m), tau*1.0/2 * eigenValue(m), fabs(1 - tau*1.0/2 * eigenValue(m)));
               
        if (fabs(1 - tau*1.0/2 * eigenValue(m)) > maxValue)
        {
            maxValue = fabs(1 - tau*1.0/2 * eigenValue(m));
            maxValueIndex = m;
        }
    }
    
    printf("%lf\n", tau*1.0/2 * eigenValue(n-1));
    return 0;
}
