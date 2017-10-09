#include <iostream>
#include <stdio.h>
#include "OneStack.h"
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int ex1 ()
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
        cout<<1<<endl;
        fclose (fin);
        fclose (fout);
        return 0;
    }
    OneStack stack(size);//ctor
    

    while(fscanf(fin,"%d",&comand)!=EOF)
    {
        switch (comand)
        {
            case 2:
            {
                stack.stackNull();
                break;
            }
            case 3:
            {
                fprintf (fout, "%d\n", stack.isNull());
                break;
            }
            case 4:
            {
                int elem;
                fscanf(fin,"%d",&elem);
                stack.addElement(elem);
                break;
            }
            case 5:
            {
                try
                {
                    fprintf (fout, "%d\n", stack.getElement());
                }
                catch (bool a) {}
                break;
            }
            case 6:
            {
                try
                {
                    fprintf (fout, "%d\n", stack.getVertice());
                }
                catch (bool a) {}

                break;
            }
            case 7:
            {
                stack.deleteVertice();
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

/*void ex2 ()
 {
 FILE* fin;
 FILE* fout;
 fin = fopen("input.txt", "r");
 fout = fopen("output.txt","w");
 int comand = 0;
 setlocale(LC_CTYPE, "rus");
 
 
 fscanf(fin,"%d",&comand);
 
 int size;
 fscanf(fin,"%d",&size);
 int number;
 TwoStacks stack(size);//ctor
 
 while(fscanf(fin,"%d",&comand)!=EOF)
 {
 switch (comand)
 {
 case 2:
 {
 stack.stackNull();
 break;
 }
 case 3:
 {
 fscanf(fin,"%d",&number);
 fprintf (fout, "%d\n", stack.isNull(number));
 break;
 }
 case 4:
 {
 string elem;
 fscanf(fin,"%d",&number);
 char curSymbol = '0';
 
 while(curSymbol!='\n')
 {
 fscanf(fin,"%c",&curSymbol);
 elem+=curSymbol;
 }
 cout<<elem;
 
 stack.addElement(elem, number);
 break;
 }
 case 5:
 {
 fscanf(fin,"%d",&number);
 string res = stack.getElement(number);
 for (int i=0; i<res.length(); ++i)
 {
 fprintf (fout, "%d\n", res[i]);
 }
 break;
 }
 case 6:
 {
 fscanf(fin,"%d",&number);
 string res = stack.getVertice(number);
 for (int i=0; i<res.length(); ++i)
 {
 fprintf (fout, "%d\n", res[i]);
 }
 break;
 }
 case 7:
 {
 fscanf(fin,"%d",&number);
 stack.deleteVertice(number);
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
 }
 
 */


int main()
{
    return ex1();
    return 0;
}

