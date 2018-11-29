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

double func(int i, int j);
int enterMatrix(double* matrix, int n, FILE* fin);
void printMatrix(double* matrix, int n, int m);
double residualNorm(double* matrix, double* inverseMatrix, int n);

#endif /* matrixUtils_hpp */