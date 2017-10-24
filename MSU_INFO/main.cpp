#include <iostream>
#include <stdio.h>
//#include "OneStack.h"
//#include "TwoStacks.h"
//#include "ThreeStacks.hpp"
//#include "DEQ.hpp"
//#include "Vector.hpp"
//#include "Sequence.hpp"
//#include "ListOneString.hpp"
#include "Set.hpp"

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

//int ex56 ()
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
//    Vector <int> vector (size);
//
//    while(fscanf(fin,"%d",&comand)!=EOF)
//    {
//        switch (comand)
//        {
//            case 2:
//            {
//                vector.vectorNull();
//                break;
//            }
//            case 3:
//            {
//                fprintf (fout, "%d\n", vector.isNull());
//                break;
//            }
//            case 4:
//            {
//                fprintf (fout, "%d\n", vector.size());
//                break;
//            }
//            case 5:
//            {
//                try
//                {
//                    int elem;
//                    fscanf(fin,"%d",&elem);
//                    vector.push(elem);
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 6:
//            {
//                try
//                {
//                    vector.pop();
//                }
//                catch (bool a) {}
//
//                break;
//            }
//            case 7:
//            {
//                try
//                {
//                    int index;
//                    fscanf(fin,"%d",&index);
//                    fprintf (fout, "%d\n", vector.getElement(index));
//                }
//                catch (bool a) {}
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

//int ex78 ()
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
//    Sequence<char> seq (size);
//
//    while(fscanf(fin,"%d",&comand)!=EOF)
//    {
//        switch (comand)
//        {
//            case 2:
//            {
//                seq.sequenceNull();
//                break;
//            }
//            case 3:
//            {
//                fprintf (fout, "%d\n", seq.isNull());
//                break;
//            }
//            case 4:
//            {
//                try
//                {
//                    char t;
//                    fscanf(fin,"%c",&t);
//
//                    char elem;
//                    fscanf(fin,"%c",&elem);
//                    seq.push(elem);
//                }
//                catch (bool a) {
//                    fclose (fin);
//                    fclose (fout);
//                    return 0;
//                }
//                break;
//            }
//            case 5:
//            {
//                seq.begin();
//                break;
//            }
//            case 6:
//            {
//                fprintf (fout, "%d\n", seq.isUnread());
//                break;
//            }
//            case 7:
//            {
//                try
//                {
//                    fprintf (fout, "%c\n", seq.read());
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 8:
//            {
//                try
//                {
//                    fprintf (fout, "%c\n", seq.element());
//                }
//                catch (bool a) {}
//                break;
//            }
//            case 9:
//            {
//                seq.skip();
//                break;
//            }
//            case 10:
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


//int ex910 ()
//{
//    ifstream fin ("input.txt");
//    ofstream fout ("output.txt");
//
//    int comand = 0;
//
//    fin>>comand;
//    if (fin.eof())
//    {
//        fin.close();
//        fout.close();
//        return 0;
//    }
//
//    int size;
//    fin>>size;
//
//    if (fin.eof())
//    {
//        fin.close();
//        fout.close();
//        return 0;
//    }
//
//    if (size<0)
//    {
//        fin.close();
//        fout.close();
//        return 0;
//    }
//    ListOneString <string> list (size);
//
//    while(!fin.eof())
//    {
//        if (fin>>comand)
//        {
//            switch (comand)
//            {
//                case 2:
//                {
//                    list.listNull();
//                    break;
//                }
//                case 3:
//                {
//                    fout<<list.isNull()<<endl;
//                    break;
//                }
//                case 4:
//                {
//                    list.begin();
//                    break;
//                }
//                case 5:
//                {
//                    fout<<list.isEnd()<<endl;
//                    break;
//                }
//                case 6:
//                {
//                    list.moveIndex();
//                    break;
//                }
//                case 7:
//                {
//                    try
//                    {
//                        string elem;
//                        fin>>elem;
//                        list.push(elem);
//                    }
//                    catch (bool a) {
//                        fin.close();
//                        fout.close();
//                        return 0;
//                    }
//                    break;
//                }
//                case 8:
//                {
//                    try
//                    {
//                        fout<<list.getElement()<<endl;
//                    }
//                    catch (bool a) {
//                        fin.close();
//                        fout.close();
//                        return 0;
//                    }
//                    break;
//                }
//                case 9:
//                {
//                    try
//                    {
//                        string res = list.readElement();
//                        fout<<res<<endl;
//                    }
//                    catch (bool a) {
//                        fin.close();
//                        fout.close();
//                        return 0;
//                    }
//                    break;
//                }
//                case 10:
//                {
//                    try
//                    {
//                        list.deleteElement();
//                    }
//                    catch (bool a) {
//                        fin.close();
//                        fout.close();
//                        return 0;
//                    }
//                    break;
//                }
//                case 11:
//                {
//                    fin.close();
//                    fout.close();
//                    return 0;
//                    break;
//                }
//            }
//        }
//    }
//
//    return 0;
//}

int ex14 ()
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
    Set <double> set (size);

    while(fscanf(fin,"%d",&comand)!=EOF)
    {
        switch (comand)
        {
            case 2:
            {
                set.setNull();
                break;
            }
            case 3:
            {
                fprintf (fout, "%d\n", set.isNull());
                break;
            }
            case 4:
            {
                try
                {
                    double elem;
                    fscanf(fin,"%lf",&elem);
                    set.push(elem);
                }
                catch (bool a) {}
                break;
            }
            case 5:
            {
                try
                {
                    double elem;
                    fscanf(fin,"%lf",&elem);
                    set.deleteElem(elem);
                }
                catch (bool a)
                {
                    fclose (fin);
                    fclose (fout);
                    break;
                }

                break;
            }
            case 6:
            {
                try
                {
                    double elem;
                    fscanf(fin,"%lf",&elem);
                    fprintf (fout, "%d\n", set.inSet(elem));
                }
                catch (bool a)
                {
                    fclose (fin);
                    fclose (fout);
                    break;
                }
                break;
            }
            case 7:
            {
                try
                {
                    fprintf (fout, "%lf\n", set.getElement());
                }
                catch (bool a)
                {
                    fclose (fin);
                    fclose (fout);
                    break;
                }
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
    ex14();
    return 0;
}

