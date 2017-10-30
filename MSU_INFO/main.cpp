#include <iostream>
#include <stdio.h>
#include "ListOne.hpp"
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


int main()
{
    ifstream fin ("input.txt");
    ofstream fout ("output.txt");
    
    int comand = 0;
    
    fin>>comand;
    if (fin.eof())
    {
        fin.close();
        fout.close();
        return 0;
    }
    
    int size;
    fin>>size;
    
    if (fin.eof())
    {
        fin.close();
        fout.close();
        return 0;
    }
    
    if (size<0)
    {
        fin.close();
        fout.close();
        return 0;
    }
    ListOne list (size);
    
    while(!fin.eof())
    {
        if (fin>>comand)
        {
            switch (comand)
            {
                case 2:
                {
                    list.listNull();
                    break;
                }
                case 3:
                {
                    fout<<list.isNull()<<endl;
                    break;
                }
                case 4:
                {
                    list.begin();
                    break;
                }
                case 5:
                {
                    fout<<list.isEnd()<<endl;
                    break;
                }
                case 6:
                {
                    list.moveIndex();
                    break;
                }
                case 7:
                {
                    try
                    {
                        int elem;
                        fin>>elem;
                        list.push(elem);
                    }
                    catch (bool a)
                    {
                        fin.close();
                        fout.close();
                        return 0;
                    }
                    break;
                }
                case 8:
                {
                    try
                    {
                        fout<<list.getElement()<<endl;
                    }
                    catch (bool a) {
                        fin.close();
                        fout.close();
                        return 0;
                    }
                    break;
                }
                case 9:
                {
                    try
                    {
                        fout<<list.readElement()<<endl;
                    }
                    catch (bool a) {
                        fin.close();
                        fout.close();
                        return 0;
                    }
                    break;
                }
                case 10:
                {
                    try
                    {
                        list.deleteElement();
                    }
                    catch (bool a) {
                        fin.close();
                        fout.close();
                        return 0;
                    }
                    break;
                }
                case 11:
                {
                    fin.close();
                    fout.close();
                    return 0;
                    break;
                }
            }
        }
    }
    
    return 0;
}

