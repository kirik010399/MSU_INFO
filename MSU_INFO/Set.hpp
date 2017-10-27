//
//  Set.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 24.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Set
{
public:
    Set();
    Set(int size);
    virtual ~Set();
    int arraySize;
    int length;
    int curIndex;
    pair<T, bool> *array;
    T *array1;
    void setNull();
    int isNull();
    int size();
    void push (T elem);
    void deleteElem (T elem);
    T getElement ();
    int inSet (T elem);
    
protected:
    
private:
};

template <typename T>
Set<T>::Set()
{
    //ctor
}

template <typename T>
Set<T>::Set(int maxSize)
{
    array = new pair <T, bool> [maxSize];
    array1 = new T [maxSize-1];
    for (int i = 0; i < maxSize; ++i)
    {
        array[i].first = 0;
        array[i].second = false;
    }
    for (int i = 0; i < maxSize-1; ++i)
    {
        array1[i] = 0; 
    }
    
    length = 0;
    curIndex = -1;
    arraySize = maxSize;
}

template <typename T>
Set<T>::~Set()
{
}


template <typename T>
void Set<T>::setNull()
{
    for (int i = 0; i < arraySize; i++)
    {
        array[i].first = 0;
        array[i].second = false;
    }
    curIndex = -1;
}

template <typename T>
int Set<T>::isNull()
{
    int flag = 1;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i].second != false)
        {
            flag = 0;
        }
    }
    return (flag && curIndex == -1);
}

template <typename T>
void Set<T>::push(T elem)
{
    int hashIndex = ((int) (elem)) % arraySize;
    
    if (array[hashIndex].second == false)
    {
        array[hashIndex].first = elem;
        array[hashIndex].second = true;
    
        return;
    }
    
    if (array[hashIndex].first == elem && array[hashIndex].second == true)
        return;
    
    ++curIndex;
    bool flag = true;
    for (int i = 0; i <= curIndex; ++i)
    {
        if (array1[i] == elem)
            flag = false;
    }
    if (flag)
    {
        array1[curIndex] = elem;
    }
}

template <typename T>
void Set<T>::deleteElem(T elem)
{
    bool flag = true;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i].second != false)
        {
            flag = false;
        }
    }
    
    if(flag&&curIndex==-1)
        throw (false);
    
    int hashIndex = ((int) elem) % arraySize;

    if (array[hashIndex].first == elem && array[hashIndex].second == true)
    {
        array[hashIndex].second = false;
        return;
    }
    
    int readIndex = -1;
    for (int i = 0; i<=curIndex; ++i)
    {
        if (array1[i]==elem)
            readIndex = i;
    }
    
    for (int i = readIndex; i<curIndex; ++i)
        array1[i] = array1[i+1];
    
    curIndex--;
    
    
}

template <typename T>
int Set<T>::inSet(T elem)
{
    int hashIndex = ((int) elem) % arraySize;
    
    if (array[hashIndex].first == elem && array[hashIndex].second != false)
    {
        return 1;
    }
    
    int flag = 0;
    for (int i = 0; i<=curIndex; ++i)
    {
        if (array1[i]==elem)
            flag = 1;
    }
    return flag;
}

template <typename T>
T Set<T>::getElement()
{
    return array[arraySize-1].first;
}


#endif /* Set_hpp */
