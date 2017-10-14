//
//  DEQ.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#include "DEQ.hpp"


#include <iostream>

using namespace std;

DEQ::DEQ()
{
    //ctor
}

DEQ::DEQ(int maxSize)
{
    array = new int[maxSize];
    
    size = maxSize;
    
    curIndex1 = -1;
    curIndex2 = size;
}

DEQ::~DEQ()
{
    delete [] array;
}

void DEQ::stackNull()
{
    curIndex1 = -1;
    curIndex2 = size;
}

int DEQ::isNull()
{
    return (curIndex1 == -1 && curIndex2 == size);
}

void DEQ::addElement (int elem, int number)
{
    switch (number)
    {
        case 1:
        {
            curIndex1++;
            if (curIndex1 >= size)
                throw (false);
            
            array[curIndex1] = elem;
            
            break;
        }
        case 2:
        {
            curIndex2--;
            if (curIndex2 < 0)
                throw (false);
            
            array[curIndex2] = elem;
            break;
        }
    }
}

int DEQ::getElement (int number)
{
    switch (number)
    {
        case 1:
        {
            if ((curIndex1 == -1 || curIndex1>=size)&&(curIndex2 == size || curIndex2<=-1))
            {
                throw (false);
            }
            else
            {
                if (curIndex1 == -1 || curIndex1>=size)
                {
                    int temp = array[curIndex2];
                    curIndex2++;
                    return temp;
                }
                else
                {
                    int temp = array[curIndex1];
                    curIndex1--;
                    return temp;
                }
            }
            
            break;
        }
        case 2:
        {
            if ((curIndex1 == -1 || curIndex1>=size)&&(curIndex2 == size || curIndex2<=-1))
            {
                throw (false);
            }
            else
            {
                if (curIndex2 == size || curIndex2<=-1)
                {
                    int temp = array[curIndex1];
                    curIndex1--;
                    return temp;
                }
                else
                {
                    int temp = array[curIndex2];
                    curIndex2++;
                    return temp;
                }
            }
            
            break;
        }
    }
    return -1;
}


int DEQ::getVertice (int number)
{
    switch (number)
    {
        case 1:
        {
            if ((curIndex1 == -1 || curIndex1>=size)&&(curIndex2 == size || curIndex2<=-1))
            {
                throw (false);
            }
            else
            {
                if (curIndex1 == -1 || curIndex1>=size)
                {
                    return array[curIndex2];
                }
                else
                {
                    return array[curIndex1];
                }
            }
            
            break;
        }
        case 2:
        {
            if ((curIndex1 == -1 || curIndex1>=size)&&(curIndex2 == size || curIndex2<=-1))
            {
                throw (false);
            }
            else
            {
                if (curIndex2 == size || curIndex2<=-1)
                {
                    return array[curIndex1];
                }
                else
                {
                    return array[curIndex2];
                }
            }
            break;
        }
    }
    return -1;
}

void DEQ::deleteVertice (int number)
{
    switch (number)
    {
        case 1:
        {
            if ((curIndex1 == -1 || curIndex1>=size)&&(curIndex2 == size || curIndex2<=-1))
            {
                throw (false);
            }
            else
            {
                if (curIndex1 == -1 || curIndex1>=size)
                {
                    curIndex2++;
                }
                else
                {
                    curIndex1--;
                }
            }
            
            break;
        }
        case 2:
        {
            if ((curIndex1 == -1 || curIndex1>=size)&&(curIndex2 == size || curIndex2<=-1))
            {
                throw (false);
            }
            else
            {
                if (curIndex2 == size || curIndex2<=-1)
                {
                    curIndex1--;
                }
                else
                {
                    curIndex2++;
                }
            }
            
            break;
        }
    }
}
