//
//  Cell.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 19.12.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

struct Cell
{
public:
    void* cell;
    int type;
    
    Cell &operator = (float value)
    {
        cell = new float;
        float* var = (float*)cell;
        *var = value;
        
        type = 1;
        return *this;
    };
    
    Cell &operator = (int value)
    {
        cell = new int;
        int* var = (int*)cell;
        *var = value;
        
        type = 0;
        return *this;
    };
    
    Cell &operator = (string value)
    {
        cell = new string;
        string* var = (string*)cell;
        *var = value;
        
        type = 2;
        return *this;
    };
    
    Cell &operator = (const Cell & other)
    {
        switch (other.type)
        {
            case 0:
            {
                *this = other.toInt();
                break;
            }
            case 1:
            {
                cout<<"!!!!!!!!!";
                *this = other.toFloat();
                break;
            }
            case 2:
            {
                *this = other.toString();
                break;
            }
        }
        
        type = other.type;
        
        return *this;
    };
    
    
    bool operator==(const Cell& other)
    {
        if (type!=other.type)
            return false;
        else
        {
            switch (type)
            {
                case 0:
                {
                    int* var = (int*)cell;
                    int* var1 = (int*)other.cell;
                    return *var == *var1;
                }
                case 1:
                {
                    float* var = (float*)cell;
                    float* var1 = (float*)other.cell;
                    return *var == *var1;
                }
                case 2:
                {
                    string* var = (string*)cell;
                    string* var1 = (string*)other.cell;
                    return *var == *var1;
                }
            }
        }
        return false;
    };
    
    bool operator!=(const Cell& other)
    {
        if (type!=other.type)
            return true;
        else
        {
            switch (type)
            {
                case 0:
                {
                    int* var = (int*)cell;
                    int* var1 = (int*)other.cell;
                    return !(*var == *var1);
                }
                case 1:
                {
                    float* var = (float*)cell;
                    float* var1 = (float*)other.cell;
                    return !(*var == *var1);
                }
                case 2:
                {
                    string* var = (string*)cell;
                    string* var1 = (string*)other.cell;
                    return !(*var == *var1);
                }
            }
        }
        return false;
    };
    
    float toFloat() const
    {
        cout<<type;
        if (type != 1)
        {
            return 0.0;
        }
        float* var = (float*)cell;
        return *var;
    };
    
    int toInt() const
    {
        if (type != 0)
        {
            return 0;
        }
        int* var = (int*)cell;
        return *var;
    };
    
    string toString() const
    {
        if (type != 2)
        {
            return "";
        }
        string* var = (string*)cell;
        return *var;
    };
    
};

class Table
{
public:
    Cell a[26][99];
    
    Cell &operator[](const string &cell)
    {
        int i = cell[0]-'A';
        int j = 0;
        if (cell.size()==2)
        {
            j = cell[1] - '0';
        }
        else
        {
            j = 10 * (cell[1] - '0') + cell[2] - '0';
        }
        return a[i][j];
    };
    
protected:
    
private:
};

#endif /* Cell_hpp */

