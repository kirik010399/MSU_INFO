#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Heap
{
public:
    int *list;
    int heapSize;
    int heapMaxSize;
    
    Heap()
    {
        list = new int[100];
        heapMaxSize = 100;
        heapSize = 0;
    }
    
    Heap(int size)
    {
        list = new int[size];//parent - i, left child - 2*i+1, right child - 2*i+2
        heapMaxSize = size;
        heapSize = 0;
    }
    
    ~Heap()
    {
        delete []list;
    }
    
    void addElement(int value)
    {
        ++heapSize;

        list[heapSize-1] = value;
        int i = heapSize-1;
        int parent = (i-1)/2;//if even - then right child and will return parent too because of int division
        
        while(parent >= 0 && i > 0)
        {
            if(list[i] > list[parent])
                swap(list[i], list[parent]);
            else
                break;
            
            i = parent;
            parent = (i-1)/2;
        }
    }
    
    void outHeap()
    {
        int i = 0;
        int k = 1;
        while(i < heapSize)
        {
            while((i < k) && (i < heapSize))
            {
                cout<<list[i]<<" ";
                i++;
            }
            cout<<endl;
            k = k*2+1;
        }
    }
    
    void outArray()
    {
        for (int i = 0; i < heapSize; ++i)
        {
            cout<<list[i]<<" ";
        }
        cout<<endl;
    }
};

int main()
{
    int n;
    int value;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
            
    fin>>n;
    
    Heap heap(n);

    for (int i = 0; i < n; ++i)
    {
        fin>>value;
        heap.addElement(value);
    }
    
    heap.outHeap();
    heap.outArray();
    
    return 0;
}

