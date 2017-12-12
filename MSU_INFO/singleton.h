//
//  singleton.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 12.12.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef singleton_hpp
#define singleton_hpp

#include <stdio.h>

#include <string>

using namespace std;

struct stringPair
{
    string key;
    string value;
    bool flag;
};

class Singleton
{
public:
    virtual ~Singleton()
    {
        if (array)
            delete [] array;
    };
    
    static Singleton* singelton;

    stringPair* array;
    
    static Singleton* getInstance()
    {
        if (!singelton)
        {
            singelton = new Singleton();
        }

        return singelton;
    };
    
    static void destroyInstance()
    {
        if (singelton)
        {
            delete singelton;
            singelton = nullptr;
        }
    };
    
    string & operator [](const string &key)
    {
        for (int i = 0; i < 100; ++i)
        {
            if (array[i].key == key && array[i].flag == true)
            {
                return array[i].value;
            }
        }
        
        for (int i = 0; i < 100; ++i)
        {
            if (array[i].flag == false)
            {
                array[i].key = key;
                array[i].value = "";
                array[i].flag = true;
                return array[i].value;
            }
        }
        return array[0].value;
    }
    
    void remove (const string &key)
    {
        for (int i = 0; i < 100; ++i)
        {
            if (array[i].key == key)
            {
                array[i].key = "";
                array[i].value = "";
                array[i].flag = false;
                break;
            }
        }
    }
    
    bool exists (const string &key)
    {
        for (int i = 0; i < 100; ++i)
        {
            if (array[i].key == key && array[i].flag == true)
            {
                return true;
            }
        }
        return false;
    }
    
    string *keys ()
    {
        sort();
        string *keys = new string [size()];
        int j = 0;
        for (int i = 0; i < 100; ++i)
        {
            if (array[i].flag == true)
            {
                keys[j] = array[i].key;
                ++j;
            }
        }
        
        return keys;
    }
    
    unsigned int size ()
    {
        unsigned int k = 0;
        for (int i = 0; i < 100; ++i)
        {
            if (array[i].flag == true)
            {
                ++k;
            }
        }
        return k;
    }
    
    void sort ()
    {
        for (int i=0; i<100; i++)
        {
            int mini=i;
            for (int j=i+1; j<100; j++)
                if (compare(array[j].key, array[mini].key))
                    mini=j;
            if (i!=mini) swap (array[i],array[mini]);
        }
    }
    
    bool compare (string string1, string string2)
    {
        for (int i = 0; i < min(string1.size(), string2.size()); ++i)
        {
            if (string1[i]<string2[i])
            {
                return true;
            }
            else
                return false;
        }
        
        if (string1.size()<string2.size())
            return true;
        else
            return false;
    }
    
    
protected:
    
private:
    Singleton()
    {
        array = new stringPair[100];
    };
};


#endif /* singleton_hpp */
