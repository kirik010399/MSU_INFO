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
    int arraySize;
    T *array;
    int *array1;
    void listNull();
    int isNull();
    void begin();
    int isEnd();
    void moveIndex();
    int firstElem();
    int lastElem();
    void push(T elem);
    void print();
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
    {
        array[i] = -2;
        array1[i] = -2;
    }
    
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
int ListOne<T>::firstElem()
{
    int sum=0, sum1=0;
    for (int i = 0; i < arraySize; ++i){
        if (array1[i]!=-2)
        {
            if (array1[i]!=-1)
                sum += array1[i];
            sum1 += i;
        }
    }
    return (sum1 - sum);
}

template <typename T>
void ListOne<T>::begin()
{
    readIndex = -1;
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
}

template <typename T>
void ListOne<T>::push(T elem)
{
    if (curIndex+1>=arraySize)
        throw (false);
    
    if (curIndex+1==0)
    {
        curIndex++;
        array[curIndex] = elem;
        array1[curIndex] = -1;
        print(); 
        return;
    }
 
    if (readIndex == -1)
    {
        array1[curIndex+1] = firstElem();
        array[curIndex+1] = elem;
    
        curIndex++;
        print();
        return;
    }
        
    for (int i = 0; i < arraySize; ++i)
    {
        if (array1[i] == -2)
        {
            array[i] = elem;
            
            array1[i] = array1[readIndex];
            array1[readIndex] = i;
            break;
        }
    }
    curIndex++;
    print();
}

template <typename T>
T ListOne<T>::getElement()
{
    T temp;
    curIndex--;

    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        temp = array[beginIndex];
        
        if (curIndex == 0)
        {
            array1[beginIndex] = -2;
            array1[firstElem()] = -1;
            print();
            return temp ;
        }
            
        array1[beginIndex] = -2;
        
        print();
        return temp ;
    }
        
    int beginIndex = array1[readIndex];
    temp = array[beginIndex];
        
    int tempIndex = array1[beginIndex];
    array1[readIndex] = tempIndex;
        
    if (curIndex == 0)
    {
        array1[beginIndex] = -2;
        array1[array1[readIndex]] = -1;
        
        print();
        return temp;
    }
    
    array1[beginIndex] = -2;

    print();
    return temp;
}

template <typename T>
T ListOne<T>::readElement()
{
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
        return array[beginIndex];
    }
        
    int beginIndex = array1[readIndex];
    return array[beginIndex];

return 0;
}

template <typename T>
void ListOne<T>::deleteElement()
{
    curIndex--; 
    
    if (readIndex == -1)
    {
        int beginIndex = firstElem();
            
        if (curIndex == 0)
        {
            array1[beginIndex] = -2;
            array1[firstElem()] = -1;
            print();
            return;
        }
            
        array1[beginIndex] = -2;
        print();
        return;
    }
        
    int beginIndex = array1[readIndex];
    int tempIndex = array1[beginIndex];
    array1[readIndex] = tempIndex;
        
    if (curIndex == 0)
    {
        array1[beginIndex] = -2;
        array1[array1[readIndex]] = -1;
            
        print();
        return;
    }
    
    array1[beginIndex] = -2;
    print();
}

template <typename T>
void ListOne<T>::print ()
{
    for (int i = 0; i<arraySize; ++i)
        cout<<array[i]<<' ';
    cout<<endl;
    for (int i = 0; i<arraySize; ++i)
        cout<<array1[i]<<' ';
    cout<<endl;
}

#endif /* ListOne_hpp */
