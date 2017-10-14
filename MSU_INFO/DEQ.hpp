//
//  DEQ.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef DEQ_hpp
#define DEQ_hpp

#include <stdio.h>

using namespace std;

class DEQ
{
public:
    DEQ();
    DEQ(int size);
    virtual ~DEQ();
    int curIndex1;
    int curIndex2;
    int size;
    int *array;
    void stackNull();
    int isNull();
    void addElement (int elem, int number);
    int getElement (int number);
    int getVertice (int number);
    void deleteVertice (int number);
    
protected:
    
private:
};

#endif /* DEQ_hpp */
