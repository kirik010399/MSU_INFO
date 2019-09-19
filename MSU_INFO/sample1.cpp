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
//    return sin(M_PI*x) + 2*sin(2*M_PI*x);
//}
////
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
//    generatePoints(fout, n);
//    
//    fclose(fin);
//    fclose(fout);
//}
//
//
