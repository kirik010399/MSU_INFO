#include <iostream>
#include <stdio.h>
//#include "OneStack.h"
//#include "TwoStacks.h"
//#include "ThreeStacks.hpp"
//#include "DEQ.hpp"
#include "Vector.hpp"


#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

//int ex1 ()
//{
//    FILE* fin;
//    FILE* fout;
//    fin = fopen("input.txt", "r");
//    fout = fopen("output.txt","w");
//    int comand = 0;
//    if (fscanf(fin,"%d",&comand) == EOF)
//    {
//        fclose (fin);
//        fclose (fout);
//
//        return 0;
//    }
//
//    int size;
//    fscanf(fin,"%d",&size);
//
//    if (size<0)
//    {
//        fclose (fin);
//        fclose (fout);
//        return 0;
//    }
//    OneStack stack(size);//ctor
//
//
//    while(fscanf(fin,"%d",&comand)!=EOF)
//    {
//        switch (comand)
//        {
//            case 2:
//            {
//                stack.stackNull();
//                break;
//            }
//            case 3:
//            {
//                fprintf (fout, "%d\n", stack.isNull());
//                break;
//            }
//            case 4:
//            {
//                int elem;
//                fscanf(fin,"%d",&elem);
//                stack.addElement(elem);
//                break;
//            }
//            case 5:
//            {
//                try
//                {
//                    fprintf (fout, "%d\n", stack.getElement());
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 6:
//            {
//                try
//                {
//                    fprintf (fout, "%d\n", stack.getVertice());
//                }
//                catch (bool a) {}
//
//                break;
//            }
//            case 7:
//            {
//                stack.deleteVertice();
//                break;
//            }
//            case 8:
//            {
//                fclose (fin);
//                fclose (fout);
//                break;
//            }
//        }
//    }
//
//    return 0;
//}

//int ex2 ()
//{
//    FILE* fin;
//    FILE* fout;
//    fin = fopen("input.txt", "r");
//    fout = fopen("output.txt","w");
//    int comand = 0;
//    if (fscanf(fin,"%d",&comand) == EOF)
//    {
//        fclose (fin);
//        fclose (fout);
//
//        return 0;
//    }
//
//    int size;
//    fscanf(fin,"%d",&size);
//
//    if (size<0)
//    {
//        fclose (fin);
//        fclose (fout);
//        return 0;
//    }
//    TwoStacks stack(size);
//
//    int number;
//
//    while(fscanf(fin,"%d",&comand)!=EOF)
//    {
//        switch (comand)
//        {
//            case 2:
//            {
//                stack.stackNull();
//                break;
//            }
//            case 3:
//            {
//                fscanf(fin,"%d",&number);
//                fprintf (fout, "%d\n", stack.isNull(number));
//                break;
//            }
//            case 4:
//            {
//                try
//                {
//                    string elem;
//                    char curSymbol = 'a';
//                    fscanf(fin,"%d",&number);
//
//                    char t;
//                    fscanf (fin,"%c",&t);
//
//                    fscanf(fin,"%c",&curSymbol);
//
//                    while(curSymbol != '\n')
//                    {
//                        elem+=curSymbol;
//                        fscanf(fin,"%c",&curSymbol);
//                    }
//
//                    stack.addElement(elem, number);
//                }
//                catch (bool a)
//                {
//                    fclose (fin);
//                    fclose (fout);
//                    return 0;
//                }
//                break;
//            }
//            case 5:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    string res = stack.getElement(number);
//
//                    cout<<3<<endl;
//
//                    for (int i=0; i<res.length(); ++i)
//                    {
//                        fprintf (fout, "%c", res[i]);
//                    }
//                    fprintf (fout, "\n");
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 6:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//
//                    string res = stack.getVertice(number);
//                    for (int i=0; i<res.length(); ++i)
//                    {
//                        fprintf (fout, "%c", res[i]);
//                    }
//                    fprintf (fout, "\n");
//                }
//                catch (bool a) {}
//
//                break;
//            }
//            case 7:
//            {
//                fscanf(fin,"%d",&number);
//                stack.deleteVertice(number);
//
//                break;
//            }
//            case 8:
//            {
//                fclose (fin);
//                fclose (fout);
//                return 0;
//            }
//        }
//    }
//
//    return 0;
//}

//int ex3 ()
//{
//    FILE* fin;
//    FILE* fout;
//    fin = fopen("input.txt", "r");
//    fout = fopen("output.txt","w");
//    int comand = 0;
//    if (fscanf(fin,"%d",&comand) == EOF)
//    {
//        fclose (fin);
//        fclose (fout);
//
//        return 0;
//    }
//
//    int size;
//    fscanf(fin,"%d",&size);
//
//    if (size<0)
//    {
//        fclose (fin);
//        fclose (fout);
//        return 0;
//    }
//    ThreeStacks stack(size);
//
//    int number;
//
//    while(fscanf(fin,"%d",&comand)!=EOF)
//    {
//        switch (comand)
//        {
//            case 2:
//            {
//                stack.stackNull();
//                break;
//            }
//            case 3:
//            {
//                fscanf(fin,"%d",&number);
//                fprintf (fout, "%d\n", stack.isNull(number));
//                break;
//            }
//            case 4:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    int elem;
//                    fscanf(fin,"%d",&elem);
//
//                    stack.addElement(elem, number);
//                }
//                catch (bool a)
//                {
//                    fclose (fin);
//                    fclose (fout);
//                    return 0;
//                }
//                break;
//            }
//            case 5:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    fprintf (fout, "%d\n", stack.getElement(number));
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 6:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    fprintf (fout, "%d\n", stack.getVertice(number));
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 7:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    stack.deleteVertice(number);
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 8:
//            {
//                fclose (fin);
//                fclose (fout);
//                return 0;
//            }
//        }
//    }
//
//    return 0;
//}

//int ex4 ()
//{
//    FILE* fin;
//    FILE* fout;
//    fin = fopen("input.txt", "r");
//    fout = fopen("output.txt","w");
//    int comand = 0;
//    if (fscanf(fin,"%d",&comand) == EOF)
//    {
//        fclose (fin);
//        fclose (fout);
//        return 0;
//    }
//
//    int size;
//    fscanf(fin,"%d",&size);
//
//    if (size<0)
//    {
//        fclose (fin);
//        fclose (fout);
//        return 0;
//    }
//    DEQ stack(size);
//
//    int number;
//
//    while(fscanf(fin,"%d",&comand)!=EOF)
//    {
//        switch (comand)
//        {
//            case 2:
//            {
//                stack.stackNull();
//                break;
//            }
//            case 3:
//            {
//                fprintf (fout, "%d\n", stack.isNull());
//                break;
//            }
//            case 4:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    int elem;
//                    fscanf(fin,"%d",&elem);
//
//                    stack.addElement(elem, number);
//                }
//                catch (bool a)
//                {
//                    fclose (fin);
//                    fclose (fout);
//                    return 0;
//                }
//                break;
//            }
//            case 5:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    fprintf (fout, "%d\n", stack.getElement(number));
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 6:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    fprintf (fout, "%d\n", stack.getVertice(number));
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 7:
//            {
//                try
//                {
//                    fscanf(fin,"%d",&number);
//                    stack.deleteVertice(number);
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 8:
//            {
//                fclose (fin);
//                fclose (fout);
//                return 0;
//            }
//        }
//    }
//
//    return 0;
//}

int ex5 ()
{
    FILE* fin;
    FILE* fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    int comand = 0;
    if (fscanf(fin,"%d",&comand) == EOF)
    {
        fclose (fin);
        fclose (fout);
        return 0;
    }

    int size;
    fscanf(fin,"%d",&size);

    if (size<0)
    {
        fclose (fin);
        fclose (fout);
        return 0;
    }
    Vector <int> vector (size);

    while(fscanf(fin,"%d",&comand)!=EOF)
    {
        switch (comand)
        {
            case 2:
            {
                vector.vectorNull();
                break;
            }
            case 3:
            {
                fprintf (fout, "%d\n", vector.isNull());
                break;
            }
            case 4:
            {
                fprintf (fout, "%d\n", vector.size());
                break;
            }
            case 5:
            {
                try
                {
                    int elem;
                    fscanf(fin,"%d",&elem);
                    vector.push(elem);
                }
                catch (bool a) {}
                break;
            }
            case 6:
            {
                try
                {
                    vector.pop();
                }
                catch (bool a) {}

                break;
            }
            case 7:
            {
                try
                {
                    int index;
                    fscanf(fin,"%d",&index);
                    fprintf (fout, "%d\n", vector.getElement(index));
                }
                catch (bool a) {}
                break;
            }
            case 8:
            {
                fclose (fin);
                fclose (fout);
                break;
            }
        }
    }

    return 0;
}



int main()
{
    return ex5();
    return 0;
}

