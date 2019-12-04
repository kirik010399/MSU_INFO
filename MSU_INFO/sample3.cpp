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
        buildHeapOptimal(a, n);

        for (int i = n-1; i >= 0; --i)
        {
            a[i] = popMax();
            heapify(0);
        }
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

