#include "TwoStacks.h"
#include <string>

using namespace std;

TwoStacks::TwoStacks()
{
    //ctor
}

TwoStacks::TwoStacks(int maxSize)
{
    this->array = new char[maxSize];
    this->curIndex1 = 0;
    this->curIndex2 = maxSize-1;
    this->size = maxSize-1;
}

TwoStacks::~TwoStacks()
{
    delete [] array;
}

//functions
void TwoStacks::stackNull()
{
    this->curIndex1 = 0;
    this->curIndex2 = this->size;
}

int TwoStacks::isNull(int number)
{
    switch (number)
    {
    case 1:
    {
        return (this->curIndex1 == 0);
    }
    case 2:
    {
        return (this->curIndex2 == this->size);
    }
    }
    return -1;
}

void TwoStacks::addElement (string str, int number)
{
    int index;
    if (number==1) index = this->curIndex1;
    else index = this->curIndex2;

    for (int i = 0; i < str.size(); ++i)
    {
        this->array[index] = str[i];
        if (number==1)
        {
            ++this->curIndex1;
            ++index;
        }
        else
        {
            --this->curIndex2;
            --index;
        }
    }
    this->array[index] = '\0';
    if (number==1) ++this->curIndex1;
    else --this->curIndex2;
}

string TwoStacks::getElement (int number)
{
    string res;
    if (number==1)
    {
        while (this->array[this->curIndex1]!='\0')
        {
            res+= this->array[this->curIndex1];
            this->curIndex1--;
        }
        this->curIndex1--;
    }
    else
    {
        while (this->array[this->curIndex2]!='\0')
        {
            res += this->array[this->curIndex2];
            this->curIndex2++;
        }
        this->curIndex2++;
    }
    string result;

    for (int i = res.size()-1; i>=0; --i)
        result += res[i];

    return result;
}
string TwoStacks::getVertice (int number)
{
    string res;
    if (number==1)
    {
        int index = this->curIndex1;
        while (this->array[index]!='\0')
        {
            res+= this->array[index];
            index--;
        }
    }
    else
    {
        int index = this->curIndex2;
        while (this->array[index]!='\0')
        {
            res += this->array[index];
            index++;
        }
    }
    string result;

    for (int i = res.size()-1; i>=0; --i)
        result += res[i];

    return result;
}

void TwoStacks::deleteVertice (int number)
{
    if (number==1)
    {
        while (this->array[this->curIndex1]!='\0')
        {
            this->curIndex1--;
        }
        this->curIndex1--;
    }
    else
    {
        while (this->array[this->curIndex2]!='\0')
        {
            this->curIndex2++;
        }
        this->curIndex2++;
    }
}
