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

#include <stdio.h>

using namespace std;

template <typename T>
class ListOne
{
public:
    ListOne();
    ListOne(int size);
    virtual ~ListOne();
    int curIndex;
    int readIndex;
    int length;
    int arraySize;
    T *array;
    void listNull();
    int isNull();
    void begin();
    int isEnd();
    void moveIndex();
    void push(T elem);
    T getElement();
    T readElement();
    void deleteElement();
    
protected:
    
private:
};

template <typename T>
ListOne<T>::ListOne()
{
    //ctor
}

template <typename T>
ListOne<T>::ListOne(int maxSize)
{
    array = new T [maxSize];
    length = 0;
    curIndex = -1;
    readIndex = -1;
    arraySize = maxSize;
}

template <typename T>
ListOne<T>::~ListOne()
{
    delete [] array;
}


template <typename T>
void ListOne<T>::listNull()
{
    curIndex = -1;
    readIndex = -1;
}

template <typename T>
int ListOne<T>::isNull()
{
    return (curIndex == -1);
}

template <typename T>
void ListOne<T>::begin()
{
    readIndex=-1;
}

template <typename T>
int ListOne<T>::isEnd()
{
    return (readIndex==curIndex);
}

template <typename T>
void ListOne<T>::moveIndex()
{
    readIndex++;
}

template <typename T>
void ListOne<T>::push(T elem)
{
    curIndex++;
    cout<<curIndex<<' '<<readIndex<<endl;
    
    if (curIndex>=arraySize)
        throw (false);
    
    for (int i = curIndex; i>=readIndex+2; i--)
    {
        array[i] = array[i-1];
    }
    array[readIndex+1] = elem;
    
    for (int i = 0; i < arraySize; ++i)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;
}

template <typename T>
T ListOne<T>::getElement()
{
    if (readIndex+1>curIndex)
        throw(false);
    
    T temp = array[readIndex+1];
    
    for (int i = readIndex+1; i<curIndex; ++i)
        array[i] = array[i+1];
    
    for (int i = 0; i < arraySize; ++i)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;
    
    curIndex--; 
    
    return temp ;
}

template <typename T>
T ListOne<T>::readElement()
{
    if (readIndex+1>=curIndex)
        throw(false);
    
    return array[readIndex+1];
}

template <typename T>
void ListOne<T>::deleteElement()
{
    cout<<readIndex<<' '<<curIndex<<endl; 
    if (readIndex+1>curIndex)
        throw(false);
    
    for (int i = readIndex+1; i<curIndex; ++i)
        array[i] = array[i+1];
    
    curIndex--;
}




#endif /* ListOne_hpp */
