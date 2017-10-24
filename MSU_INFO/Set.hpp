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

using namespace std;

template <typename T>
class Set
{
public:
    Set();
    Set(int size);
    virtual ~Set();
    int curIndex;
    int length;
    int arraySize;
    T *array;
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
    array = new T[maxSize];
    for (int i = 0; i < maxSize; ++i)
    {
        array[i] = -1;
    }
    length = 0;
    curIndex = -1;
    arraySize = maxSize;
}

template <typename T>
Set<T>::~Set()
{
    delete [] array;
}


template <typename T>
void Set<T>::setNull()
{
    curIndex = -1;
}

template <typename T>
int Set<T>::isNull()
{
    return (curIndex == -1);
}

template <typename T>
void Set<T>::push(T elem)
{
    curIndex++;
    
    if (curIndex>=arraySize)
        throw (false);
    
    bool flag = true;
    for (int i = 0; i < curIndex; ++i)
    {
        if (array[i] == elem)
            flag = false;
    }
    if (flag)
    {
        array[curIndex] = elem;
    }
    
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
}

template <typename T>
void Set<T>::deleteElem(T elem)
{
    if (curIndex==-1)
        throw (false);
    
    int readIndex = -1;
    for (int i = 0; i<=curIndex; ++i)
    {
        if (array[i]==elem)
            readIndex = i;
    }
    cout<<readIndex<<endl; 
    
    for (int i = readIndex; i<curIndex; ++i)
        array[i] = array[i+1];
    
    curIndex--;
    
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
}

template <typename T>
int Set<T>::inSet(T elem)
{
    int flag = 0;
    for (int i = 0; i<=curIndex; ++i)
    {
        if (array[i]==elem)
            flag = 1;
    }
    return flag;
    
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
}

template <typename T>
T Set<T>::getElement()
{
    return array[curIndex];
}


#endif /* Set_hpp */
