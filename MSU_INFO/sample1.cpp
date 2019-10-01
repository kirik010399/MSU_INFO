//#include <stdio.h>
//#include <math.h>
//#include <time.h>
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//double f (double x)
//{
//    return x*(x-1);
//}
//
//void generatePoints(FILE *fout, int n)
//{
//    double a = 0;
//    double b = 1;
//    
//    double dt = fabs(b-a)/(n);
//    
//    for (double i = a; i <= b; i+=dt)
//    {
//        fprintf(fout, "%f ", f(i));
//    }
//}
//
//void generatePointsWithDoubleShift(FILE *fout, int n)
//{
//    double a = 0;
//    double b = 1;
//    
//    double dt = fabs(b-a)/(n);
//    double newDt = (1.0 + dt)/n;
//
//    fprintf(fout, "%f ", -f(-dt/2 + newDt));
//    
////    printf("%f %f\n", dt, newDt);
////    printf("%f ", -dt/2);
//    
//    for (double i = -dt/2 + newDt; i <= 1+dt/2-newDt; i+=newDt)
//    {
////        printf("%f ", i);
//        fprintf(fout, "%f ", f(i));
//    }
//    
////    printf("%f/n", 1+dt/2);
//
//    fprintf(fout, "%f ", f(1+dt/2-newDt));
//}
//
//int main(void)
//{
//    FILE *fin, *fout;
//    int n;
//    
//    fin = fopen("input.txt", "r");
//    fout = fopen("input1.txt", "w");
//    
//    fscanf(fin, "%d", &n);
//    
//    generatePointsWithDoubleShift(fout, n);
//    
//    fclose(fin);
//    fclose(fout);
//}
//
//
