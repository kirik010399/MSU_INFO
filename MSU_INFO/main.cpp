#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <algorithm>

double func(double x, double y)
{
    return x * sin(y);
}

double realResult()
{
    double a = 0;
    double b = 1;
    
    return (b*b/2 - a*a/2)*(cos(a) - cos(b));
}

void generateTriangles(FILE *fout, int n)
{
    
}

double integrateTriangles(){return 0;}

int main()
{
    int beginN, endN;
    FILE *fin, *foutTriangles, *finTriangles, *fout;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    
    fscanf(fin, "%d %d", &beginN, &endN);
    
    for (int i = beginN; i <= endN; ++i)
    {
        foutTriangles = fopen("triangles.txt", "w");
        generateTriangles(foutTriangles, i);
        fclose(foutTriangles);
        
        finTriangles = fopen("triangles.txt", "r");
        
        int n;
        fscanf(finTriangles, "%d", &n);
        
        //
        
        double result = integrateTriangles();
        
        printf("%.16lf\n", result);
        fprintf(fout, "%.16lf, ", fabs(realResult() - result));
        
        fclose(finTriangles);
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}
