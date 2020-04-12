#include <iostream>
#include <math.h>

class solvingScheme
{
public:
    solvingScheme(int num, double factor)
    {
        schemeNumber = num;
        A = factor;
        previousNorm = 0;
    }
    
    void printErrors()
    {
        double *y_exact, *y_scheme;
        
        for (n = 100; n <= 1e6; n *= 10)
        {
            h = 10.0/n;
           
            y_scheme = new double[n+1];
            y_exact = new double[n+1];
           
            fillSchemeY(y_scheme);
            fillExactY(y_exact);
            
            normError(y_scheme, y_exact);
            
            delete []y_scheme;
            delete []y_exact;
        }
    }

private:
    int schemeNumber;
    double A;
    double h;
    int n;
    double previousNorm;
       
    void fillSchemeY(double *y)
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
        
        for (int i = 0; i < n; ++i)
            y[i+1] = y[i] - h*A * y[i];
    }
    
    void secondScheme(double *y)
    {
        y[0] = 1;
        
        for (int i = 0; i < n; ++i)
            y[i+1] = 1.0/(1.0+h*A) * y[i];
    }
    
    void thirdScheme(double *y)
    {
        y[0] = 1;
        
        for (int i = 0; i < n; ++i)
            y[i+1] = (2.0-h*A)/(2.0+h*A) * y[i];
    }

    void fourthScheme(double *y)
    {
        y[0] = 1;
        y[1] = 1 - A*h;
        
        for (int i = 1; i < n; ++i)
            y[i+1] = y[i-1] - 2.0*h*A * y[i];
    }

    void fifthScheme(double *y)
    {
        y[0] = 1;
        y[1] = 1 - A*h;
        
        for (int i = 1; i < n; ++i)
            y[i+1] = 4.0/3.0 * y[i] - (1.0+2.0*h*A)/3.0 * y[i-1];
    }
    
    double exactSolution(double x)
    {
        return exp(-A*x);
    }
    
    void fillExactY(double *y)
    {
        for (int i = 0; i < n+1; ++i)
            y[i] = exactSolution(i*h);
    }
    
    void normError(double *y1, double *y2)
    {
        double norm = 0;
        double dif;
        
        for (int i = 0; i < n+1; ++i)
        {
            dif = fabs(y1[i] - y2[i]);
            norm += dif*dif * h;
        }
        
        double currentNorm = sqrt(norm)/pow(h, getConvergence());
        
        if (previousNorm != 0)
            printf("%lf\n", currentNorm/previousNorm);
        
        previousNorm = currentNorm;
        
        printf("%d %.16lf\n", n, currentNorm);
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
    calculateErrorsForFactor(10);

    return 0;
}
