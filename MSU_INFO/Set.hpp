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
    for (int i = 0; i < maxSize; ++i)
    {
        array[i].first = 0;
        array[i].second = false;
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
    return flag;
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
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i].second == false)
        {
            array[i].first = elem;
            array[i].second = true;
        }
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
    
    if(flag)
        throw (false);
    
    int hashIndex = ((int) elem) % arraySize;

    if (array[hashIndex].first == elem && array[hashIndex].second == true)
    {
        array[hashIndex].second = false;
        return;
    }
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i].first==elem && array[i].second == true)
            array[i].second = false;
    }
}

template <typename T>
int Set<T>::inSet(T elem)
{
    int hashIndex = ((int) elem) % arraySize;
    
    if (array[hashIndex].first == elem && array[hashIndex].second != false)
    {
        return 1;
    }
    
    for (int i = 0; i<arraySize; ++i)
    {
        if (array[i].first==elem && array[i].second != false)
            return 1;
    }

    return 0;
}

template <typename T>
T Set<T>::getElement()
{
    return array[arraySize-1].first;
}


#endif /* Set_hpp */
