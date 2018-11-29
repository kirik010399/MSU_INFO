//
//  invertingManager.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#ifndef invertingManager_hpp
#define invertingManager_hpp

#include <stdio.h>

int invertMatrix(double* matrix, double* inverseMatrix, double *d,  int n, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* invertingManager_hpp */
