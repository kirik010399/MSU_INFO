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
        
        for (n = 10; n <= 1e8; n *= 10)
        {
            h = 1.0/n;
           
            x = new double[n+1];
            y = new double[n+1];
           
            fillX(x);
            fillY(y);
            normError(x, y);
            
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
            y[i+1] = 1.0/(1.0+h*A) * y[i];
    }
    
    void thirdScheme(double *y)
    {
        y[0] = 1;
        for (int i = 0; i < n; i++)
            y[i+1] = (2.0-h*A)/(2.0+h*A) * y[i];
    }

    void fourthScheme(double *y)
    {
        y[0] = 1;
        y[1] = 1 - A*h;
        
        for (int i = 1; i < n; i++)
            y[i+1] = y[i-1] - 2.0*h*A * y[i];
    }

    void fifthScheme(double *y)
    {
        y[0] = 1;
        y[1] = 1 - A*h;
        
        for (int i = 1; i < n; i++)
            y[i+1] = 4.0/3.0 * y[i] - (1.0+2.0*h*A)/3.0 * y[i-1];
    }
    
    void normError(double *x, double *y)
    {
        double norm = 0;
        double dif;
        
        for (int i = 0; i < n+1; i++)
        {
            dif = fabs(y[i] - exactSolution(x[i]));
            norm += dif*dif * h;
        }
        
        printf("%d %.16lf\n", n, sqrt(norm)/pow(h, getConvergence()));
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

void calculateErrorsForFactor(double A)
{
    printf("Factor: %lf\n", A);
    for (int schemeNumber = 1; schemeNumber <= 5; ++schemeNumber)
    {
        printf("\nScheme number: %d\nErrors:\n", schemeNumber);
        solvingScheme Scheme(schemeNumber, A);
        Scheme.printErrors();
    }
    printf("\n\n");
}

int main()
{
    calculateErrorsForFactor(1);
    calculateErrorsForFactor(2);
    calculateErrorsForFactor(5);

    return 0;
}
