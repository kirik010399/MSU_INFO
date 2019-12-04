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
    
    void buildHeap(int *a, int n)
    {
        heapSize = 0;
        for (int i = 0; i < n; ++i)
            addElement(a[i]);
    }
    
    void heapify(int i)
    {
        int left, right;
        left = 2*i+1;
        right = 2*i+2;

        if(left < heapSize)
        {
            if(list[i] < list[left])
            {
                swap(list[i], list[left]);
                heapify(left);
            }
        }

        if(right < heapSize)
        {
            if(list[i] < list[right])
            {
                swap(list[i], list[right]);
                heapify(right);
            }
        }
    }
    
    void buildHeapOptimal(int *a, int n)
    {
        for(int i = 0; i < n; ++i)
            list[i] = a[i];
        
        heapSize = n;

        for (int i = heapSize/2; i >= 0; i--)
            heapify(i);
    }
    
    int popMax()
    {
        int max = list[0];
        list[0] = list[heapSize-1];
        --heapSize;
        return max;
    }
    
    void heapSort(int *a, int n)
    {
        buildHeap(a, n);
//        buildHeapOptimal(a, n);

        for (int i = n-1; i >= 0; --i)
        {
            a[i] = popMax();
            heapify(0);
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
    ifstream fin("input.txt");
    ofstream fout("output.txt");
            
    int *a;
    fin>>n;
    
    a = new int[n];
    
    for (int i = 0; i < n; ++i)
        fin>>a[i];
    
    Heap heap(n);
    heap.heapSort(a, n);
    
    for (int i = 0; i < n; ++i)
        fout<<a[i]<<" ";
    
    delete []a;
    return 0;
}

