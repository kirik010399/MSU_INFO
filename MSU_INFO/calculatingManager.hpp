//
//  calculatingManager.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#ifndef calculatingManager_hpp
#define calculatingManager_hpp

#include <stdio.h>

void calculateValues(double* matrix, double* vector, double eps, int k, int n);
void values(double *matrix, int n, double *vector, double left, double right, int k, double eps);
int n_(double* a, int n, double lambda);
void Rotation(double* a, int n);
double MatrixNorm(double* a, int n);


#endif /* calculatingManager_hpp */
