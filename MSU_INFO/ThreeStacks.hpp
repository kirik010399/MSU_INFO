//
//  ThreeStacks.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef ThreeStacks_hpp
#define ThreeStacks_hpp

#include <stdio.h>

using namespace std;

class ThreeStacks
{
public:
    ThreeStacks();
    ThreeStacks(int size);
    virtual ~ThreeStacks();
    int curIndex1;
    int curIndex2;
    int curIndex3;
    int count3; 
    int size3; 
    int size;
    int *array;
    void stackNull();
    int isNull(int number);
    void addElement (int elem, int number);
    int getElement (int number);
    int getVertice (int number);
    void deleteVertice (int number);
    
protected:
    
private:
};

#endif /* ThreeStacks_hpp */
