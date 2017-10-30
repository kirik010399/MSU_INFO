#include <iostream>
#include <stdio.h>
//#include "OneStack.h"
//#include "TwoStacks.h"
//#include "ThreeStacks.hpp"
//#include "DEQ.hpp"
//#include "Vector.hpp"
//#include "Sequence.hpp"
#include "ListOne.hpp"

#include <string>
#include <fstream>
#include <algorithm>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

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
//    ListOne <int> list (size);
//    int number;
//
//    while(!fin.eof())
//    {
//        if (fin>>comand)
//        {
//            cout<<comand<<endl;
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
//                    fin>>number;
//                    list.begin(number);
//                    break;
//                }
//                case 5:
//                {
//                    fin>>number;
//                    fout<<list.isEnd(number)<<endl;
//                    break;
//                }
//                case 6:
//                {
//                    fin>>number;
//                    list.moveIndex(number);
//                    break;
//                }
//                case 7:
//                {
//                    try
//                    {
//                        int elem;
//                        fin>>number;
//                        fin>>elem;
//                        list.push(elem, number);
//                    }
//                    catch (bool a)
//                    {
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
//                        fin>>number;
//                        fout<<list.getElement(number)<<endl;
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
//                        fin>>number;
//                        fout<<list.readElement(number)<<endl;
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
//                        fin>>number;
//                        list.deleteElement(number);
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


int main()
{
    
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string str;
    getline(cin,str);
    if (str=="") return 0;
    stringstream stream;
    stream << str;
    int firstIn=0;
    int secondIn=0;
    stream >> firstIn >> secondIn;
    if (secondIn<0) return 0;
    
    MySpisok mySpisok(secondIn);
    
    while(true){
        int a,b,r;
        cin >> a;
        /*cout << "Massiv:";
         for (int i=0;i<mySpisok.get_max_size()+1;i++){
         cout << "el:" << mySpisok.el[i];
         cout << "ss:" << mySpisok.ss[i];
         } */
        switch(a){
            case 2:
                mySpisok.sdpust();
                break;
            case 3:
                if (mySpisok.get_cur_size()==0) cout << 1 << endl;
                else cout << 0 << endl;
                break;
            case 4:
                cin >> r;
                if (r==0){
                    mySpisok.cursor_clear();
                }
                if (r==1){
                    mySpisok.cursor_end();
                }
                break;
            case 5:
                cin >> r;
                if (r==0){
                    if (mySpisok.get_cursor()==mySpisok.get_start()) cout << 1 << endl; else cout << 0 << endl;
                }
                if (r==1){
                    if (mySpisok.get_cursor()==mySpisok.get_endd()) cout << 1 << endl; else cout << 0 << endl;
                }
                break;
            case 6:
                cin >> r;
                if (r==0) mySpisok.pered_cursor();
                if (r==1) mySpisok.pered_cursor_naz();
                break;
            case 7:
                cin >> r >> b;
                if (mySpisok.get_cur_size()==mySpisok.get_max_size()) return 0;
                if (r==0){
                    mySpisok.push_z(b);
                }
                if (r==1){
                    mySpisok.push(b);
                }
                break;
            case 8:
                cin >> r;
                if (mySpisok.get_cur_size()==0) return 0;
                if (r==0) cout << mySpisok.pop_z() << endl;
                if (r==1) cout << mySpisok.pop() <<endl;
                break;
            case 9:
                cin >> r;
                if (r==1) cout << mySpisok.get_element() <<endl;
                if (r==0) cout << mySpisok.get_element_z() <<endl;
                break;
            case 10:
                cin >> r;
                if (mySpisok.get_cur_size()==0) return 0;
                if (r==1) mySpisok.del();
                if (r==0) mySpisok.del_z();
                break;
            case 11:
                return 0;
                
        }
        
        
    }
    
}

