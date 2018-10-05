//
//  matrixUtils.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#ifndef matrixUtils_hpp
#define matrixUtils_hpp

#include <stdio.h>

int enterData(double* matrix, double* vector, int n, FILE* fin);
void printResult(double* matrix, int n, int m);
double residualNorm(double* matrix, double* vector, double* result, int n); 
double errorFunction(double *result, int n);

#endif /* matrixUtils_hpp */
