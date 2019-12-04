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
        list = new int[size];//current - i, left child - 2*i+1, right child - 2*i+2
        heapMaxSize = size;
        heapSize = 0;
    }
    
    ~Heap()
    {
        delete []list;
    }
    
    void addElement(int value)
    {
        list[heapSize] = value;
        int i = heapSize;
        int parent = (i-1)/2;
        
        while(parent >= 0 && i > 0)
        {
            if(list[i] > list[parent])
            {
              swap(list[i], list[parent]);
            }

            i = parent;
            parent = (i-1)/2;//if even - then right child and will return parent too
        }
        
        ++heapSize;
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
    
    void buildHeap(int *a, int n)
    {
        heapSize = n;
        for (int i = 0; i < heapSize; ++i)
            addElement(a[i]);
    }
    
    void buildHeapOptimal(int *a, int n)
    {
        heapSize = n;
        
        for(int i = 0; i < heapSize; ++i)
            list[i] = a[i];

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
        buildHeapOptimal(a, n);
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
                cout << list[i] << " ";
                i++;
            }
            cout << endl;
            k = k * 2 + 1;
        }
    }
    
    void out()
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
    int value;// change here
    ifstream fin("input.txt");
    ofstream fout("output.txt");
        
    Heap heap(10);
    
    while (!fin.eof())
    {
        if (fin>>value)
        {
            heap.addElement(value);
        }
    }
    
    heap.outHeap();
    cout<<endl;
    heap.out();

    return 0;
}

