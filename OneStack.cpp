#include "OneStack.h"

using namespace std;

OneStack::OneStack()
{
    //ctor
}

OneStack::OneStack(int maxSize)
{
    array = new int[maxSize];
    curIndex = -1;
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
    this->array[this->curIndex] = elem;
}

int OneStack::getElement ()
{
    int temp = this->array[this->curIndex];
    this->curIndex--;
    return temp;
}

int OneStack::getVertice ()
{
    return this->array[this->curIndex];
}

void OneStack::deleteVertice ()
{
    this->curIndex--;
}
