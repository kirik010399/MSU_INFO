#ifndef SolvHead_hpp
#define SolvHead_hpp

#include <stdio.h>

void calculateValues(double* a, double* res, double eps, int k, int n);
void values(double *a, int n, double *res, double left, double right, int k, double eps);
int n_(double* a, int n, double lambda);
void Rotation(double* a, int n);
double MatrixNorm(double* a, int n);


#endif /* SolHead_hpp */
