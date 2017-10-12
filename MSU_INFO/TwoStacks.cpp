#include "TwoStacks.h"
#include <string>
#include <iostream>

using namespace std;

TwoStacks::TwoStacks()
{
    //ctor
}

TwoStacks::TwoStacks(int maxSize)
{
    array = new char[maxSize];
    
    for (int i=0; i<maxSize; ++i)
        array[i] = '0'+i%10;
    
    curIndex1 = -1;
    curIndex2 = maxSize;
    size = maxSize;
}

TwoStacks::~TwoStacks()
{
    delete [] array;
}

void TwoStacks::stackNull()
{
    this->curIndex1 = -1;
    this->curIndex2 = this->size;
}

int TwoStacks::isNull(int number)
{
    switch (number)
    {
    case 1:
    {
        return (this->curIndex1 == -1);
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
    cout<<str<<endl;
    int index;
    
    if (number == 1)
        index = ++curIndex1;
    else
        index = --curIndex2;
    
    cout<<index<<endl;
    
    for (int i = 0; i < str.size(); ++i)
    {
        array[index] = str[i];
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
    array[index] = '\0';
    
    for (int i = 0; i < size; ++i)
    {
        if (array[i]=='\0')
            cout<<' ';
        else
            cout<<array[i];
    }
    cout<<endl;
    
    cout<<curIndex1<<' '<<curIndex2<<endl;
}

string TwoStacks::getElement (int number)
{
    string res = "";
    
    if (number==1)
    {
        if (curIndex1==-1)
            throw (false);
        
        curIndex1--;
        
        while (array[curIndex1]!='\0')
        {
            res+= array[curIndex1];
            curIndex1--;
            
            if (curIndex1 == -1)
                break;
        }
    }
    else
    {
        if (curIndex2==-size)
            throw (false);
     
        curIndex2++;
        
        while (array[curIndex2]!='\0')
        {
            res += array[curIndex2];
            curIndex2++;
            
            if (curIndex2 == size)
                break;
        }
    }
    
    cout<<curIndex1<<' '<<curIndex2<<endl;
    
    cout<<res<<endl;
    
    string result;

    for (int i = res.size()-1; i >= 0; --i)
        result += res[i];
    
    cout<<result<<endl; 
    
    return result;
}


string TwoStacks::getVertice (int number)
{
    string res = "";
    int index;
    
    if (number==1)
    {
        if (curIndex1==-1)
            throw (false);
        
        index = curIndex1;
        
        index--;
        
        while (array[index]!='\0')
        {
            res+= array[index];
            index--;
            
            if (index == -1)
                break;
        }
    }
    else
    {
        if (curIndex2==-size)
            throw (false);
        
        index = curIndex2;
        
        index++;
        
        while (array[index]!='\0')
        {
            res += array[index];
            index++;
            
            if (index == size)
                break;
        }
    }
    
    cout<<curIndex1<<' '<<curIndex2<<endl;
    
    cout<<res<<endl;
    
    string result;
    
    for (int i = res.size()-1; i >= 0; --i)
        result += res[i];
    
    cout<<result<<endl;
    
    return result;
}

void TwoStacks::deleteVertice (int number)
{    
    if (number==1)
    {
        curIndex1--;
        
        while (array[curIndex1]!='\0')
        {
            curIndex1--;
            
            if (curIndex1 == -1)
                break;
        }
    }
    else
    {
        curIndex2++;
        
        while (array[curIndex2]!='\0')
        {
            curIndex2++;
            
            if (curIndex2 == size)
                break;
        }
    }
}
