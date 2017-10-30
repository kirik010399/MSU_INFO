//
//  ListOne.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#include "ListOne.hpp"

ListOne::ListOne()
{
    //ctor
}

ListOne::ListOne(int maxSize)
{
    array = new int [maxSize];
    array1 = new int [maxSize];
    
    for (int i = 0; i<maxSize; ++i)
    {
        array[i] = -2;
        array1[i] = -2;
    }
    
    curIndex = -1;
    readIndex = -1;
    arraySize = maxSize;
}

ListOne::~ListOne()
{
    delete [] array;
    delete [] array1;
}


void ListOne::listNull()
{
    curIndex = -1;
    readIndex = -1;
}

int ListOne::isNull()
{
    return (curIndex == -1);
}

int ListOne::firstElem()
{
    int sum=0, sum1=0;
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array1[i]!=-2)
        {
            if (array1[i]!=-1)
                sum += array1[i];
            sum1 += i;
        }
    }
    return (sum1 - sum);
}

void ListOne::begin()
{
    readIndex = -1;
}

int ListOne::isEnd()
{
    if (readIndex==-1)
    {
        return 0;
    }
    return (array1[readIndex] == -1);
}

void ListOne::moveIndex()
{
    if (readIndex == -1)
        readIndex = firstElem();
    else
        readIndex = array1[array1[readIndex]];
}

void ListOne::push(int elem)
{
    if (curIndex+1 >= arraySize)
        throw (false);
    
    if (curIndex+1==0)
    {
        curIndex++;
        array[curIndex] = elem;
        array1[curIndex] = -1;
        return;
    }
    
    if (readIndex == -1)
    {
        array1[curIndex+1] = firstElem();
        array[curIndex+1] = elem;
        
        curIndex++;
        return;
    }
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array1[i] == -2)
        {
            array[i] = elem;
            array1[i] = array1[readIndex];
            array1[readIndex] = i;
            break;
        }
    }
    curIndex++;
}

int ListOne::getElement()
{
    int temp;
    curIndex--;
    
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        temp = array[beginIndex];
        
        if (curIndex == 0)
        {
            array1[beginIndex] = -2;
            array1[firstElem()] = -1;
            return temp ;
        }
        
        array1[beginIndex] = -2;
        return temp ;
    }
    
    int beginIndex = array1[readIndex];
    temp = array[beginIndex];
    int tempIndex = array1[beginIndex];
    array1[readIndex] = tempIndex;
    
    if (curIndex == 0)
    {
        array1[beginIndex] = -2;
        array1[array1[readIndex]] = -1;
        return temp;
    }
    
    array1[beginIndex] = -2;
    return temp;
}

int ListOne::readElement()
{
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        return array[beginIndex];
    }
    
    int beginIndex = array1[readIndex];
    return array[beginIndex];
}

void ListOne::deleteElement()
{
    curIndex--;
    
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        
        if (curIndex == 0)
        {
            array1[beginIndex] = -2;
            array1[firstElem()] = -1;
            return;
        }
        
        array1[beginIndex] = -2;
        return;
    }
    
    int beginIndex = array1[readIndex];
    int tempIndex = array1[beginIndex];
    array1[readIndex] = tempIndex;
    
    if (curIndex == 0)
    {
        array1[beginIndex] = -2;
        array1[array1[readIndex]] = -1;
        return;
    }
    
    array1[beginIndex] = -2;
}
