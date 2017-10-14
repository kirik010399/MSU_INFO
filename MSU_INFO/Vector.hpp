//
//  Vector.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <stdio.h>

using namespace std;

template <typename T>
class Vector
{
public:
    Vector();
    Vector(int size);
    virtual ~Vector();
    int curIndex;
    int length;
    int arraySize;
    T *array;
    void vectorNull();
    int isNull();
    int size();
    void push (T elem);
    void pop ();
    T getElement (int index);
    
protected:
    
private:
};

template <typename T>
Vector<T>::Vector()
{
    //ctor
}

template <typename T>
Vector<T>::Vector(int maxSize)
{
    array = new T[maxSize];
    length = 0;
    curIndex = -1;
    arraySize = maxSize; 
}

template <typename T>
Vector<T>::~Vector()
{
    delete [] array;
}


template <typename T>
void Vector<T>::vectorNull()
{
    curIndex = -1;
}

template <typename T>
int Vector<T>::isNull()
{
    return (curIndex == -1);
}

template <typename T>
int Vector<T>::size()
{
    return length;
}

template <typename T>
void Vector<T>::push(T elem)
{
    curIndex++;
    
    if (curIndex>=arraySize)
        throw (false);
    
    array[curIndex] = elem;
}

template <typename T>
void Vector<T>::pop()
{
    curIndex--;
}

template <typename T>
T Vector<T>::getElement(int index)
{
    if (index<=-1||index>=arraySize)
        throw(false);
    return array[index];
}


#endif /* Vector_hpp */
