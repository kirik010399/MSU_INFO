//
//  ListOne.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef ListOne_hpp
#define ListOne_hpp

#include <stdio.h>

#include <algorithm>
#include <iostream>

#include <stdio.h>

using namespace std;

template <typename T>
class ListOne
{
public:
    ListOne();
    ListOne(int size);
    virtual ~ListOne();
    int curIndex;
    int readIndex;
    int length;
    int arraySize;
    T *array;
    int *array1;
    void listNull();
    int isNull();
    void begin();
    int isEnd();
    void moveIndex();
    int firstElem();
    void push(T elem);
    T getElement();
    T readElement();
    void deleteElement();
    
protected:
    
private:
};

template <typename T>
ListOne<T>::ListOne()
{
    //ctor
}

template <typename T>
ListOne<T>::ListOne(int maxSize)
{
    array = new T [maxSize];
    array1 = new int [maxSize];
    
    for (int i = 0; i<maxSize; ++i)
        array[i]=-2;
    
    for (int i = 0; i<maxSize; ++i)
        array1[i]=-2;
    cout<<endl;
    length = 0;
    curIndex = -1;
    readIndex = -1;
    arraySize = maxSize;
}

template <typename T>
ListOne<T>::~ListOne()
{
    delete [] array;
    delete [] array1;
}


template <typename T>
void ListOne<T>::listNull()
{
    curIndex = -1;
    readIndex = -1;
}

template <typename T>
int ListOne<T>::isNull()
{
    return (curIndex == -1);
}

template <typename T>
void ListOne<T>::begin()
{
    readIndex = -1;
}

template <typename T>
int ListOne<T>::firstElem()
{
    int sum=0, sum1=0;

    for (int i = 0; i <= curIndex; ++i)
        if (array1[i]!=-1)
        {
            sum += array1[i];
            sum1 += i;
        }
    
    return (sum1 - sum);
}

template <typename T>
int ListOne<T>::isEnd()
{
    if (readIndex==-1)
    {
        return 0;
    }
    return (array1[readIndex] == -1);
}

template <typename T>
void ListOne<T>::moveIndex()
{
    if (readIndex == -1)
        readIndex = firstElem();
    else
        readIndex = array1[array1[readIndex]];
    
    cout<<readIndex<<endl; 
}

// 9 7 4 2 7 8
//-1 3 0 5 1 2

//after 3

//0  1 2 3 4 5 6
//-1 3 0 6 1 2 5
template <typename T>
void ListOne<T>::push(T elem)
{
    if (curIndex+1>=arraySize)
        throw (false);
    // 1 2 3
    //-1 0 1
    array[curIndex+1] = elem;
    if (curIndex+1 == 0)
    {
        array1[curIndex+1] = -1;
        curIndex++;
        
        for (int i = 0; i<arraySize; ++i)
            cout<<array[i]<<' ';
        cout<<endl;
        for (int i = 0; i<arraySize; ++i)
            cout<<array1[i]<<' ';
        cout<<endl;
        return;
    }
    if (readIndex == -1)
    {
        array1[curIndex+1] = firstElem();
        array[curIndex+1] = elem;
        curIndex++;
        for (int i = 0; i<arraySize; ++i)
            cout<<array[i]<<' ';
        cout<<endl;
        for (int i = 0; i<arraySize; ++i)
            cout<<array1[i]<<' ';
        cout<<endl;
        return;
    }
    
    if (array1[readIndex] == -1)
    {
        curIndex++;
        array1[readIndex] = curIndex;
        array1[curIndex] = -1;
        
        for (int i = 0; i<arraySize; ++i)
            cout<<array[i]<<' ';
        cout<<endl;
        for (int i = 0; i<arraySize; ++i)
            cout<<array1[i]<<' ';
        cout<<endl;
        return;
    }
    
    curIndex++;
    
    int tempIndex = array1[readIndex];
    array1[readIndex] = curIndex;
    array1[curIndex] = tempIndex;
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
    for (int i = 0; i<arraySize; ++i)
        cout<<array1[i]<<' ';
    cout<<endl;
}

//0  1 2 3 4 5
//-1 3 0 5 1 2

//delete after 4

//0  1 2 3 4 5
//-1 3 0 5 3 2

//0  2 3 4 5
//-1 0 5 3 2

//0  2 3 4 5
//-1 0 4 2 1

// 1 2 3 4
//-1 0 1 2

template <typename T>
T ListOne<T>::getElement()
{
    T temp;
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        temp = array[beginIndex];
        
        for (int i = beginIndex; i<curIndex; ++i)
        {
            array[i] = array[i+1];
            array1[i] = array1[i+1];
        }
        curIndex--;
        
        for (int i = 0; i<arraySize; ++i)
            cout<<array[i]<<' ';
        cout<<endl;
        for (int i = 0; i<arraySize; ++i)
            cout<<array1[i]<<' ';
        cout<<endl;
        
        return temp ;
    }
    
    temp = array[array1[readIndex]];
    cout<<"temp "<<temp<<endl;
    
    int tempReadIndex = array1[readIndex];
    
    cout<<"tempReadIndex "<<tempReadIndex<<endl;
    
    int tempIndex = array1[array1[readIndex]];
    cout<<"tempIndex "<<tempIndex<<endl;

    array1[readIndex] = tempIndex;
    
    for (int i = tempReadIndex; i<curIndex; ++i)
    {
        array[i] = array[i+1];
        array1[i] = array1[i+1];
    }
    
    for (int i = 0; i < curIndex; ++i)
    {
        if (array1[i] > tempReadIndex)
            array1[i]--;
    }
    
    curIndex--;
    
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
    for (int i = 0; i<arraySize; ++i)
        cout<<array1[i]<<' ';
    cout<<endl;
    
    return temp ;
}

template <typename T>
T ListOne<T>::readElement()
{
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        return array[beginIndex];
    }
    return array[array1[readIndex]];
}

template <typename T>
void ListOne<T>::deleteElement()
{
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        
        for (int i = beginIndex; i<curIndex; ++i)
        {
            array[i] = array[i+1];
            array1[i] = array1[i+1];
        }
        curIndex--;
        
        for (int i = 0; i<arraySize; ++i)
            cout<<array[i]<<' ';
        cout<<endl;
        for (int i = 0; i<arraySize; ++i)
            cout<<array1[i]<<' ';
        cout<<endl;
        
        return;
    }
    
    int tempReadIndex = array1[readIndex];
    
    int tempIndex = array1[array1[readIndex]];
    array1[readIndex] = tempIndex;
    
    for (int i = tempReadIndex; i<curIndex; ++i)
    {
        array[i] = array[i+1];
        array1[i] = array1[i+1];
    }
    
    for (int i = 0; i < curIndex; ++i)
    {
        if (array1[i] > tempReadIndex)
            array1[i]--;
    }
    
    curIndex--;
    
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
    for (int i = 0; i<arraySize; ++i)
        cout<<array1[i]<<' ';
    cout<<endl;
}




#endif /* ListOne_hpp */
