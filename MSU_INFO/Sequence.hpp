//
//  Sequence.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>
#include <algorithm>
#include <iostream>

#include <stdio.h>

using namespace std;

template <typename T>
class Sequence
{
public:
    Sequence();
    Sequence(int size);
    virtual ~Sequence();
    int curIndex;
    int readIndex;
    int length;
    int arraySize;
    pair<T, bool> *array;
    void sequenceNull();
    int isNull();
    void push (T elem);
    void begin();
    int isUnread();
    T read();
    T element();
    void skip();
    
protected:
    
private:
};

template <typename T>
Sequence<T>::Sequence()
{
    //ctor
}

template <typename T>
Sequence<T>::Sequence(int maxSize)
{
    array = new pair<T, bool> [maxSize];
    for (int i =0; i<maxSize; ++i)
    {
        array[i].second = false; 
    }
    length = 0;
    curIndex = -1;
    readIndex = -1;
    arraySize = maxSize;
}

template <typename T>
Sequence<T>::~Sequence()
{
    delete [] array;
}


template <typename T>
void Sequence<T>::sequenceNull()
{
    curIndex = -1;
    readIndex = -1;
}

template <typename T>
int Sequence<T>::isNull()
{
    return (curIndex == -1);
}

template <typename T>
void Sequence<T>::push(T elem)
{
    curIndex++;
    
    if (curIndex>=arraySize)
        throw (false);
    
    array[curIndex].first = elem;
    array[curIndex].second = false;
}

template <typename T>
void Sequence<T>::begin()
{
    readIndex=-1;
}

template <typename T>
int Sequence<T>::isUnread()
{
    int flag = 0;
    for (int i = 0; i<=curIndex; ++i)
    {
        if (!array[i].second) flag = 1;
    }
    return flag;
}

template <typename T>
T Sequence<T>::read()
{
    if (readIndex+1>curIndex)
        throw (false);
    
    readIndex++;
    array[readIndex].second = true;
    return array[readIndex].first;
}

template <typename T>
T Sequence<T>::element()
{    
    if (readIndex+1>curIndex)
        throw (false);
    
    return array[readIndex+1].first;
}

template <typename T>
void Sequence<T>::skip()
{
    readIndex++;
    array[readIndex].second = true;
}



#endif /* Sequence_hpp */
