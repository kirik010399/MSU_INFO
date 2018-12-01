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
#include <algorithm>

using namespace std; 

double func(int i, int j, int n);
int enterMatrix(double* matrix, int n, FILE* fin);
void printVector(double* vector, int k);
pair<double, double> residualNorm(double* matrix, double* vector, int n);

#endif /* matrixUtils_hpp */
