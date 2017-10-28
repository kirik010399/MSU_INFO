//
//  ListTwoString.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 28.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef ListTwoString_hpp
#define ListTwoString_hpp

#include <stdio.h>
#include "TwoStacks.h"

#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class ListTwoString
{
public:
    ListTwoString();
    ListTwoString(int size);
    virtual ~ListTwoString();
    TwoStacks* stack;
    int curIndex;
    int readIndex;
    int length;
    int arraySize;
    void listNull();
    int isNull();
    void begin(int number);
    int isEnd(int number);
    void moveIndex(int number);
    void push(T elem, int number);
    T getElement(int number);
    T readElement(int number);
    void deleteElement(int number);
    
protected:
    
private:
};

template <typename T>
ListTwoString<T>::ListTwoString()
{
    //ctor
}

template <typename T>
ListTwoString<T>::ListTwoString(int maxSize)
{
    stack = new TwoStacks(maxSize);
}

template <typename T>
ListTwoString<T>::~ListTwoString()
{
}


template <typename T>
void ListTwoString<T>::listNull()
{
    stack->stackNull();
}

template <typename T>
int ListTwoString<T>::isNull()
{
    return (stack->isNull(1)&&stack->isNull(2));
}

template <typename T>
void ListTwoString<T>::begin(int number)
{
    if (number==0)
    {
        while (!stack->isNull(1))
        {
            string elem = stack->getElement(1);
            cout<<elem<<endl;
            stack->addElement(elem, 2);
        }
    }
    else
    {
        while (!stack->isNull(2))
        {
            string elem = stack->getElement(2);
            cout<<elem<<endl;
            stack->addElement(elem, 1);
        }
    }
}

template <typename T>
int ListTwoString<T>::isEnd(int number)
{
    if (number == 0)
        return stack->isNull(1);
    else
        return stack->isNull(2);
}

template <typename T>
void ListTwoString<T>::moveIndex(int number)
{
    if (number == 0)
    {
        if (!stack->isNull(2))
        {
            string elem = stack->getElement(2);
            stack->addElement(elem, 1);
        }
    }
    else
    {
        if (!stack->isNull(1))
        {
            string elem = stack->getElement(1);
            stack->addElement(elem, 2);
        }
    }
}

template <typename T>
void ListTwoString<T>::push(T elem, int number)
{
    if (number == 0)
    {
        try
        {
            stack->addElement(elem, 1);
        }
        catch (bool a)
        {
            throw (false);
        }
    }
    else
    {
        try
        {
            stack->addElement(elem, 2);
        }
        catch (bool a)
        {
            throw (false);
        }
    }
}


template <typename T>
T ListTwoString<T>::getElement(int number)
{
    if (number == 0)
    {
        if (stack->isNull(1))
            throw (false);
        
        return stack->getElement(1);
    }
    else
    {
        if (stack->isNull(2))
            throw (false);
        
        return stack->getElement(2);
    }
}

template <typename T>
T ListTwoString<T>::readElement(int number)
{
    if (number == 0)
    {
        if (stack->isNull(1))
            throw (false);
        
        return stack->getVertice(1);
    }
    else
    {
        if (stack->isNull(2))
            throw (false);
        
        return stack->getVertice(2);
    }
}

template <typename T>
void ListTwoString<T>::deleteElement(int number)
{
    if (number == 0)
    {
        if (stack->isNull(1))
            throw (false);
        
        return stack->deleteVertice(1);
    }
    else
    {
        if (stack->isNull(2))
            throw (false);
        
        return stack->deleteVertice(2);
    }
}

#endif /* ListTwoString_hpp */
