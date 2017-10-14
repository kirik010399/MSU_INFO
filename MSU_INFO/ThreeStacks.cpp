//
//  ThreeStacks.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#include "ThreeStacks.hpp"

#include <iostream>

using namespace std;

ThreeStacks::ThreeStacks()
{
    //ctor
}

ThreeStacks::ThreeStacks(int maxSize)
{
    array = new int[maxSize];
    
    size3 = (int) maxSize/3;
    size = maxSize;

    curIndex1 = -1;
    curIndex2 = maxSize;
    curIndex3 = --size3;
}

ThreeStacks::~ThreeStacks()
{
    delete [] array;
}

void ThreeStacks::stackNull()
{
    curIndex1 = -1;
    curIndex2 = size;
    curIndex3 = size3-1;
}

int ThreeStacks::isNull(int number)
{
    switch (number)
    {
        case 1:
        {
            return (curIndex1 == -1);
        }
        case 2:
        {
            return (curIndex2 == size);
        }
        case 3:
        {
            return (curIndex3 == size3-1);
        }
    }
    return -1;
}

void ThreeStacks::addElement (int elem, int number)
{
    switch (number)
    {
        case 1:
        {
            curIndex1++;
            array[curIndex1] = elem;
        }
        case 2:
        {
            curIndex2++;
            array[curIndex2] = elem;
        }
        case 3:
        {
            curIndex3--;
            array[curIndex3] = elem;
        }
    }
}

int ThreeStacks::getElement (int number)
{
    switch (number)
    {
        case 1:
        {
            int temp = array[curIndex1];
            curIndex1--;
            return temp;
        }
        case 2:
        {
            int temp = array[curIndex2];
            curIndex2--;
            return temp;
        }
        case 3:
        {
            int temp = array[curIndex3];
            curIndex3++;
            return temp;
        }
    }
    return -1;
}


int ThreeStacks::getVertice (int number)
{
    switch (number)
    {
        case 1:
        {
            return array[curIndex1];
        }
        case 2:
        {
            return array[curIndex2];
        }
        case 3:
        {
            return array[curIndex3];
        }
    }
    return -1;
}

void ThreeStacks::deleteVertice (int number)
{
    switch (number)
    {
        case 1:
        {
            curIndex1--;
        }
        case 2:
        {
            curIndex2--;
        }
        case 3:
        {
            curIndex3++;
        }
    }
}
