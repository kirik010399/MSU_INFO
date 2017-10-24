//
//  ListOneString.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 16.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef ListOneString_hpp
#define ListOneString_hpp

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class ListOneString
{
public:
    ListOneString();
    ListOneString(int size);
    virtual ~ListOneString();
    int curIndex;
    int readIndex;
    int length;
    int arraySize;
    char *array;
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
ListOneString<T>::ListOneString()
{
    //ctor
}

template <typename T>
ListOneString<T>::ListOneString(int maxSize)
{
    array = new char [maxSize];
    for (int i = 0; i<maxSize; ++i)
    {
        array[i] = 0;
    }
    length = 0;
    curIndex = -1;
    readIndex = -1;
    arraySize = maxSize;
}

template <typename T>
ListOneString<T>::~ListOneString()
{
    delete [] array;
}


template <typename T>
void ListOneString<T>::listNull()
{
    curIndex = -1;
    readIndex = -1;
}

template <typename T>
int ListOneString<T>::isNull()
{
    return (curIndex == -1);
}

template <typename T>
void ListOneString<T>::begin()
{
    readIndex = -1;
}

template <typename T>
int ListOneString<T>::isEnd()
{
    return (readIndex==curIndex);
}

template <typename T>
void ListOneString<T>::moveIndex()
{
    cout<<"move"<<endl;
    cout<<readIndex<<' ';
    ++readIndex;
    while (array[readIndex]!='\0'&&readIndex!=curIndex)
    {
        ++readIndex;
    }
    cout<<readIndex<<endl;
}

template <typename T>
void ListOneString<T>::push(T elem)
{
    if (curIndex+elem.size()>=arraySize)
        throw (false);
    
    int tempCurIndex = curIndex;
    int tempReadIndex = readIndex;
    
    cout<<"push"<<endl;
    cout<<curIndex<<' '<<readIndex<<endl;

    cout<<elem<<endl;
    
    for (int j = 0; j < elem.size()+1; ++j)
    {
        for (int i = tempCurIndex+1; i>=tempReadIndex+2; --i)
        {
            array[i] = array[i-1];
        }
        tempCurIndex++;
        tempReadIndex++;
    }
    
    curIndex+=elem.size();
    
    for (int j = 0; j < elem.size(); ++j)
        array[readIndex+1+j] = elem[j];
    
    array[readIndex+1+elem.size()] = '\0';
    
    ++curIndex;
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i]!='\0')
            cout<<array[i];
        else cout<<' '; 
    }
    cout<<endl;
}

template <typename T>
T ListOneString<T>::getElement()
{
    if (readIndex+1>curIndex)
        throw(false);
    
    cout<<"get"<<endl;
    int tempReadIndex = readIndex;
    int tempCurIndex = curIndex;
    
    string res = "";
    
    tempReadIndex++;
    while(array[tempReadIndex]!='\0')
    {
        res += array[tempReadIndex];
        tempReadIndex++;
    }
    
    tempReadIndex = readIndex;
    
    for (int j = 0; j < res.size()+1; ++j)
    {
        for (int i = tempReadIndex+res.size()+1; i<tempCurIndex; ++i)
         {
             array[i] = array[i+1];
         }
        tempReadIndex--;
        tempCurIndex--;
    }
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i]!='\0')
            cout<<array[i];
        else cout<<' ';
    }
    cout<<endl;
    
    curIndex--;
    curIndex-=res.size();
    
    return res;
}

template <typename T>
T ListOneString<T>::readElement()
{
    if (readIndex+1>curIndex)
        throw(false);
    
    cout<<"read"<<endl;
    int tempReadIndex = readIndex;
    
    string res = "";
    
    tempReadIndex++;
    while(array[tempReadIndex]!='\0')
    {
        res += array[tempReadIndex];
        tempReadIndex++;
    }
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i]!='\0')
            cout<<array[i];
        else cout<<' ';
    }
    cout<<endl;
    
    return res;
}

template <typename T>
void ListOneString<T>::deleteElement()
{
    cout<<"delete"<<endl;
    if (readIndex+1>curIndex)
        throw(false);
    
    int tempReadIndex = readIndex;
    int tempCurIndex = curIndex;
    
    string res = "";
    
    tempReadIndex++;
    while(array[tempReadIndex]!='\0')
    {
        res += array[tempReadIndex];
        tempReadIndex++;
    }
    
    tempReadIndex = readIndex;
    
    for (int j = 0; j < res.size()+1; ++j)
    {
        for (int i = tempReadIndex+res.size()+1; i<tempCurIndex; ++i)
        {
            array[i] = array[i+1];
        }
        tempReadIndex--;
        tempCurIndex--;
    }
    
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i]!='\0')
            cout<<array[i];
        else cout<<' ';
    }
    cout<<endl;
    
    curIndex--;
    curIndex-=res.size();
}




#endif /* ListOneString_hpp */
