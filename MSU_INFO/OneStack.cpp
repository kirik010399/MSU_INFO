#include "OneStack.h"
#include <algorithm>
#include <iostream>

using namespace std;

OneStack::OneStack()
{
    //ctor
}

OneStack::OneStack(int maxSize)
{
    array = new int[maxSize];
    curIndex = -1;
    arraySize = maxSize;
}

OneStack::~OneStack()
{
    delete [] array;
}

//functions
void OneStack::stackNull()
{
    curIndex = -1;
}

int OneStack::isNull()
{
    return (this->curIndex==-1);
}

void OneStack::addElement (int elem)
{
    this->curIndex++;
    if (curIndex < arraySize)
        this->array[this->curIndex] = elem;
}

int OneStack::getElement ()
{
    if (this->curIndex == -1 || curIndex>=arraySize)
    {
        throw (false);
    }
    else
    {
        int temp = this->array[this->curIndex];
        curIndex--;
        return temp;
    }
}

int OneStack::getVertice ()
{
    if (this->curIndex == -1 || curIndex>=arraySize)
    {
        throw (false);
    }
    else
    {
        return this->array[this->curIndex];
    }
}

void OneStack::deleteVertice ()
{
    this->curIndex--;
}

