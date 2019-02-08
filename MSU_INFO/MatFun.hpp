#ifndef MatFun_hpp
#define MatFun_hpp

#include <stdio.h>
#include <algorithm>

using namespace std;

double func(int i, int j, int n);
int enterData(double* a, int n, FILE* fin);
void printResult(double* res, int k);
pair<double, double> residualNorm(double* a, double* res, int n);

#endif /* MatFun_hpp */
