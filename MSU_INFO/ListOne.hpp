//
//  ListOne.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef ListOne_hpp
#define ListOne_hpp

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;

class ListOne
{
public:
    ListOne();
    ListOne(int size);
    virtual ~ListOne();
    int curIndex;
    int readIndex;
    int arraySize;
    int *array;
    int *array1;
    void listNull();
    int isNull();
    void begin();
    int isEnd();
    void moveIndex();
    int firstElem();
    int lastElem();
    void push(int elem);
    int getElement();
    int readElement();
    void deleteElement();
    
protected:
    
private:
};

#endif /* ListOne_hpp */
