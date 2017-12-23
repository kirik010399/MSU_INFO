//
//  Any.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 21.11.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef Any_hpp
#define Any_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class abstractVar
{
public:
    virtual abstractVar* copy()
    {
        return nullptr;
    };
    virtual ~abstractVar(){}
};

template <class T>
class Var: public abstractVar
{
public:
    Var (){}
    Var (T a);
    T variable;
    virtual abstractVar* copy();
    virtual ~Var()
    {
        
    }
};

template <class T>
Var<T>::Var(T a)
{
    variable = a;
}

template <class T>
abstractVar* Var<T>::copy()
{
    Var<T>* temp = new Var<T>;
    temp->variable = variable;
    return temp;
}

class Any
{
public:
    Any()
    {
        empty = true;
    }
    
    abstractVar* value;
    
    bool empty;
    //
    template<class T>
    Any(const T& val)
    {
        value = new Var<T> (val);
        empty = false;
    }
    //
    Any(const Any& rhs)
    {
        value = rhs.value->copy();
        empty = false;
    }
    //
    template<class T>
    Any& operator=(const T& val)
    {
        if (!empty)
            delete value;
        
        empty = false;
        value = new Var<T> (val);
        return *this;
    }
    //
    Any& operator=(const Any& rhs)
    {
        if (value == rhs.value)
            return *this;
        
        if (!rhs.Empty())
        {
            empty = false;
            value = rhs.value->copy();
        }
        else
        {
            empty = true; 
        }
        return *this;
    }
    
    
    ~Any()
    {
        if (!empty)
            delete value;
    }
    //
    bool Empty() const
    {
        return empty;
    }
    //
    void Clear()
    {
        if (!empty)
            delete value;
        
        empty = true;
    }
    //
    void Swap(Any& rhs)
    {
        Any temp;
        temp = rhs;
        rhs = *this;
        *this = temp;
    }
    //
    template<class T>
    T& GetValue()
    {
        return ((Var<T>*) value)->variable;
    }
};





#endif /* Any_hpp */

