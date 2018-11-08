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

void calculateValues(double* matrix, double* vector, double left, double right, int n);
void values(double *matrix, int n, double *vector, double left, double right);
int n_(double* a, int n, double lam);
void Otr(double* a, int n);


#endif /* calculatingManager_hpp */
