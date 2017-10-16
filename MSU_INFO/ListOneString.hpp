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
    readIndex=-1;
}

template <typename T>
int ListOneString<T>::isEnd()
{
    return (readIndex==curIndex);
}

template <typename T>
void ListOneString<T>::moveIndex()
{
    readIndex++;
}

template <typename T>
void ListOneString<T>::push(T elem)
{
    if (curIndex>=arraySize)
        throw (false);
    
    for (int j = 0; j < elem.size(); ++j)
        for (int i = curIndex; i>=readIndex+2; i--)
        {
            array[i] = array[i-1];
        }
    
    curIndex+=elem.size();
    
    for (int j = 0; j < elem.size(); ++j)
        array[readIndex+1+j] = elem[j];
    
    array[readIndex+1+elem.size()] = '\0';
    
    cout<<"push"<<endl; 
    
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
    
    string temp = " " + array[readIndex+1];
    
    for (int i = readIndex+1; i<curIndex; ++i)
        array[i] = array[i+1];
    
    for (int i = 0; i < arraySize; ++i)
    {
        cout<<array[i]<<' ';
    }
    cout<<endl;
    
    curIndex--;
    
    return temp ;
}

template <typename T>
T ListOneString<T>::readElement()
{
    if (readIndex+1>=curIndex)
        throw(false);
    
    return " "+array[readIndex+1];
}

template <typename T>
void ListOneString<T>::deleteElement()
{
    cout<<readIndex<<' '<<curIndex<<endl;
    if (readIndex+1>curIndex)
        throw(false);
    
    for (int i = readIndex+1; i<curIndex; ++i)
        array[i] = array[i+1];
    
    curIndex--;
}




#endif /* ListOneString_hpp */
