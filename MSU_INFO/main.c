#include <stdio.h>
#include <math.h>
#define eps 0.0001

double f(double x);// for entering function
double integral ( double (*f)(double),double l, double r);//The calculation of the integral
// l - left edge of the segment  r - right edge of the segment

int main(void)
{
    double l, r, n;
    scanf("%lf%lf", &l, &r);
    n = integral (f,l,r);
    printf ("%lf", n);
}

double integral ( double (*f)(double), double l, double r)
{
    double x, h, S, S0, d, n;

    d=r-l;
    h=f(l);
    S=d*h;
    n=1;
    
    do{
        n*=2;
        d/=2;
        S0=S;
        x=l+d;
        while (x<r)
        {
            h+=f(x);
            x+=2*d;
        }
        S=d*h;
    }
    while (fabs(S-S0)>eps);
    
    return S;
}

double f(double x)
{
    return x*x;
}

