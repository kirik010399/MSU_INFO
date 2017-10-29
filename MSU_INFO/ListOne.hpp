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
    int readIndex2;
    int length;
    int arraySize;
    T *array;
    int *array1;
    int *array2;
    void listNull();
    int isNull();
    void begin(int number);
    int isEnd(int number);
    void moveIndex(int number);
    int firstElem();
    int lastElem();
    void push(T elem, int number);
    void print();
    T getElement(int number);
    T readElement(int number);
    void deleteElement(int number);
    
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
    array2 = new int [maxSize];

    for (int i = 0; i<maxSize; ++i)
    {
        array[i]=-2;
        array1[i] = -2;
        array2[i] = -2;
    }
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
    delete [] array2;
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
int ListOne<T>::lastElem(){
    int sum=0, sum1=0;
    for (int i = 0; i <= curIndex; ++i){
        if (array2[i]!=-1)
            sum += array2[i];
        sum1 += i;
    }
    return (sum1 - sum);
}

template <typename T>
int ListOne<T>::firstElem(){
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
void ListOne<T>::begin(int number)
{
    if (number == 0)
    {
        readIndex = -1;
    }
    else
    {
        readIndex = lastElem();
    }
}

template <typename T>
int ListOne<T>::isEnd(int number)
{
   if (number == 0)
   {
       return (readIndex == -1);
   }
   else
   {
       if (readIndex==-1)
       {
           return 0;
       }
       return (array1[readIndex] == -1);
   }
}

template <typename T>
void ListOne<T>::moveIndex(int number)
{
    if (number == 0)
    {
        if (readIndex == -1)
            readIndex = firstElem();
        else
            readIndex = array1[array1[readIndex]];
    }
    else
    {
        if (array2[readIndex] == -1)
            return;
        
        readIndex = array2[array2[readIndex]];
    }
}

template <typename T>
void ListOne<T>::push(T elem, int number)
{
    cout<<"curIndex "<<curIndex+1<<endl; 
    if (curIndex+1>=arraySize)
        throw (false);
    
    if (curIndex+1==0)
    {
        curIndex++;
        array[curIndex] = elem;
        array1[curIndex] = -1;
        array2[curIndex] = -1;
        
        print(); 
        return;
    }
    
    if (number == 0)
    {
        if (readIndex == -1)
        {
            return;
        }
        
        for (int i = 0; i < arraySize; ++i)
        {
            if (array1[i] == -2 && array2[i] == -2)
            {
                array[i] = elem;
                
                array1[array2[readIndex]] = i;
                array1[i] = readIndex;
                
                array2[i] = array2[readIndex];
                array2[readIndex] = i;
                break;
            }
        }
        curIndex++;
        print();
    }
    else
    {
        if (readIndex == -1)
        {
            array1[curIndex+1] = firstElem();
            array[curIndex+1] = elem; 
            
            for (int i = 0; i <= curIndex; ++i)
            {
                if (array2[i]==-1)
                {
                    array2[i] = curIndex+1;
                    break;
                }
            }
            array2[curIndex+1] = -1;
            curIndex++;
            print();
            return;
        }
        
        for (int i = 0; i < arraySize; ++i)
        {
            if (array1[i] == -2 && array2[i] == -2)
            {
                array[i] = elem;
                
                array2[array1[readIndex]] = i;
                array2[i] = readIndex;
                
                array1[i] = array1[readIndex];
                array1[readIndex] = i;
                break;
            }
        }
        curIndex++;
        print();
    }
}

template <typename T>
T ListOne<T>::getElement(int number)
{
    T temp;
    curIndex--;
    if (number == 0)
    {
        if (readIndex == -1)
        {
            return -1;
        }
        
        int beginIndex = array2[readIndex];
        temp = array[beginIndex];
        
        int tempIndex = array2[beginIndex];
        array2[readIndex] = tempIndex;
        
        array1[beginIndex] = -2;
        array2[beginIndex] = -2;
        
        array1[array2[beginIndex]] = array1[beginIndex];
        if (curIndex == 0)
        {
            array1[array1[readIndex]] = -1;
            array2[array1[readIndex]] = -1;
        }
        print();
        return temp;
    }
    else
    {
        if (readIndex == -1)
        {
            int beginIndex = firstElem();
            temp = array[beginIndex];
            
            array1[beginIndex] = -2;
            array2[beginIndex] = -2;
            
            array2[array1[beginIndex]] = -1;
            if (curIndex == 0)
            {
                array1[firstElem()] = -1;
                array2[firstElem()] = -1;
            }
            print();
            return temp ;
        }
        
        int beginIndex = array1[readIndex];
        temp = array[beginIndex];
        
        int tempIndex = array1[beginIndex];
        array1[readIndex] = tempIndex;
        
        array1[beginIndex] = -2;
        array2[beginIndex] = -2;
        
        array2[array1[beginIndex]] = array2[beginIndex];
        if (curIndex == 0)
        {
            array1[array1[readIndex]] = -1;
            array2[array1[readIndex]] = -1;
        }
        print();
        return temp;
    }
}

template <typename T>
T ListOne<T>::readElement(int number)
{
    if (number == 0)
    {
        if (readIndex == -1)
        {
            return -1;
        }
        
        int beginIndex = array2[readIndex];
        return array[beginIndex];
    }
    else
    {
        if (readIndex == -1)
        {
            int beginIndex = firstElem();
            return array[beginIndex];
        }
        
        int beginIndex = array1[readIndex];
        return array[beginIndex];
    }
    return 0; 
}

template <typename T>
void ListOne<T>::deleteElement(int number)
{
    curIndex--; 
    if (number == 0)
    {
        if (readIndex == -1)
        {
            return;
        }
        
        int beginIndex = array2[readIndex];
        
        int tempIndex = array2[beginIndex];
        array2[readIndex] = tempIndex;
        
        array1[beginIndex] = -2;
        array2[beginIndex] = -2;
        
        array1[array2[beginIndex]] = array1[beginIndex];
        if (curIndex == 0)
        {
            array1[array1[readIndex]] = -1;
            array2[array1[readIndex]] = -1;
        }
        print();
    }
    else
    {
        if (readIndex == -1)
        {
            int beginIndex = firstElem();
            
            array1[beginIndex] = -2;
            array2[beginIndex] = -2;
            
            array2[array1[beginIndex]] = -1;
            if (curIndex == 0)
            {
                array1[firstElem()] = -1;
                array2[firstElem()] = -1;
            }
            print();
            return;
        }
        
        int beginIndex = array1[readIndex];
        
        int tempIndex = array1[beginIndex];
        array1[readIndex] = tempIndex;
        
        array1[beginIndex] = -2;
        array2[beginIndex] = -2;
        
        array2[array1[beginIndex]] = array2[beginIndex];

        if (curIndex == 0)
        {
            array1[array1[readIndex]] = -1;
            array2[array1[readIndex]] = -1;
        }
        print();
    }
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
    for (int i = 0; i<arraySize; ++i)
        cout<<array2[i]<<' ';
    cout<<endl;
}




#endif /* ListOne_hpp */
