#include <stdio.h>

int main(void)
{
    double a;
    int i;
    
    scanf("%lf", &a);
    
    i = 0;
    
    while (i < 10)
    {
        a += 2;
        ++i;
    }
    
    if (i == 10)
    {
        i = 3;
    }
    else if (i != 5)
    {
        i = 5;
    }
    
    printf("%lf %d\n", a, i);
    
    return 0;
}
