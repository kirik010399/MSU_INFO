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
    
    count3 = 0;
    
    curIndex1 = -1;
    curIndex2 = size;
    curIndex3 = size3-1;
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
            
            if (curIndex1 >= size)
                throw (false);
            
            if (curIndex1==curIndex3)
            {
                int temp = curIndex3;
                for (int i = count3; i >=1; --i)
                {
                    array[curIndex3+i] = array[curIndex3+i-1];
                    temp++;
                }
                curIndex3 = temp;
            }
            
            array[curIndex1] = elem;
            
            break;
        }
        case 2:
        {
            curIndex2--;
            
            if (curIndex2 < 0)
                throw (false);
            
            if (curIndex2==curIndex3+count3)
            {
                int temp = curIndex3;
                for (int i = 0; i <= count3; ++i)
                {
                    array[curIndex3+i-1] = array[curIndex3+i];
                    temp--;
                }
                curIndex3 = temp;
            }
            
            array[curIndex2] = elem;
            break;
        }
        case 3:
        {
            curIndex3++;
            if (curIndex1 >= size)
                throw (false);
            
            array[curIndex3] = elem;
            count3++;
            break;
        }
    }
}

int ThreeStacks::getElement (int number)
{
    switch (number)
    {
        case 1:
        {
            if (curIndex1 == -1 || curIndex1>=size)
            {
                throw (false);
            }
            else
            {
                int temp = array[curIndex1];
                curIndex1--;
                return temp;
            }
            
            break;
        }
        case 2:
        {
            if (curIndex2 == size || curIndex2<=-1)
            {
                throw (false);
            }
            else
            {
                int temp = array[curIndex2];
                curIndex2++;
                return temp;
            }
            
            break;
        }
        case 3:
        {
            if (curIndex3 == size3-1 || curIndex3>=size)
            {
                throw (false);
            }
            else
            {
                int temp = array[curIndex3];
                curIndex3--;
                return temp;
            }
            break;
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
            if (curIndex1 == -1 || curIndex1>=size)
            {
                throw (false);
            }
            else
            {
                return array[curIndex1];
            }
            break;
        }
        case 2:
        {
            if (curIndex2 == size || curIndex2<=-1)
            {
                throw (false);
            }
            else
            {
                return array[curIndex2];
            }
            break;
        }
        case 3:
        {
            if (curIndex3 == size3-1 || curIndex3>=size)
            {
                throw (false);
            }
            else
            {
                return array[curIndex3];
            }
            break;
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
            if (curIndex1 == -1 || curIndex1>=size)
            {
                throw (false);
            }
            else
            {
                curIndex1--;
            }
            break;
        }
        case 2:
        {
            if (curIndex2 == size || curIndex2<=-1)
            {
                throw (false);
            }
            else
            {
                curIndex2++;
            }
            break;
        }
        case 3:
        {
            if (curIndex3 == size3-1 || curIndex3>=size)
            {
                throw (false);
            }
            else
            {
                curIndex3--;
            }
            break;
        }
    }
}

