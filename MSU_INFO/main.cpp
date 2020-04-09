#include <iostream>
#include <math.h>

class solvingScheme
{
public:
    solvingScheme(int num, double factor)
    {
        schemeNumber = num;
        A = factor;
    }
    
    void printErrors()
    {
        double *x, *y;
        
        for (n = 100; n <= 10000000; n *= 10)
        {
            h = 10.0/n;
           
            x = new double[n+1];
            y = new double[n+1];
           
            fillX(x);
            fillY(y);
            error(x, y);
            
            delete []x;
            delete []y;
        }
    }

private:
    int schemeNumber;
    double A;
    double h;
    int n;
    
    void fillX(double *x)
    {
        for (int i = 0; i < n+1; i++)
            x[i] = i*h;
    }
       
    void fillY(double *y)
    {
        switch (schemeNumber)
        {
            case 1:
                firstScheme(y);
                break;
            case 2:
                secondScheme(y);
                break;
            case 3:
                thirdScheme(y);
                break;
            case 4:
                fourthScheme(y);
                break;
            case 5:
                fifthScheme(y);
                break;
        }
    }

    void firstScheme(double *y)
    {
        y[0] = 1;
        for (int i = 0; i < n; i++)
            y[i+1] = y[i] - h*A * y[i];
    }
    
    void secondScheme(double *y)
    {
        y[0] = 1;
        
        for (int i = 0; i < n; i++)
            y[i+1] = 1/(1 + h*A) * y[i];
    }
    
    void thirdScheme(double *y)
    {
        y[0] = 1;
        for (int i = 0; i < n; i++)
            y[i+1] = (2 - h*A)/(2 + h*A) * y[i];
    }

    void fourthScheme(double *y)
    {
        y[0] = 1;
        y[1] = 1 - A*h;
        
        for (int i = 1; i < n; i++)
            y[i+1] = y[i-1] - 2*h*A * y[i];
    }

    void fifthScheme(double *y)
    {
        y[0] = 1;
        y[1] = 1 - A*h;
        
        for (int i = 1; i < n; i++)
            y[i+1] = 4./3 * y[i] - 1./3 * y[i-1] - 1./3 * 2*h*A * y[i-1];
    }
    
    void error(double *x, double *y)
    {
        double maxDif, dif;

        maxDif = 0;
        
        for (int i = 0; i < n+1; i++)
        {
            dif = fabs(y[i] - exactSolution(x[i]));
            
            if (dif > maxDif)
                maxDif = dif;
        }
        
        printf("%d %.16lf\n", n, maxDif / pow(h, getConvergence()));
    }
    
    double exactSolution(double x)
    {
        return exp(-A*x);
    }
    
    int getConvergence()
    {
        switch(schemeNumber)
        {
            case 1:
            case 2:
            case 5:
                return 1;
            case 3:
            case 4:
                return 2;
        }
        return -1;
    }
    
};


int main()
{
    int schemeNumber;
    double A;
    
    printf("Enter scheme number: ");
    scanf("%d", &schemeNumber);
    
    if (!(schemeNumber >= 1 && schemeNumber <= 5))
    {
        printf("Incorrect scheme number");
        return -1;
    }
    
    printf("Enter factor А: ");
    scanf("%lf", &A);
    
    solvingScheme Scheme(schemeNumber, A);
    Scheme.printErrors();
    
    return 0;
}
