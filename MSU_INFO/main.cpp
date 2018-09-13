#include <iostream>
#include <vector>
using namespace std;

unsigned long deleteElements (vector <double> a, double x, double n);

int main()
{
    vector <double> a;
    
    int n;
    cin>>n;
    double x;
    cin>>x;
    
    cout<<"choose type of enter data: 1 - file, 2 - random"<<endl;

    int type;
    cin>>type;
    
    if (type == 1)
    {
        FILE *fin;
        fin = fopen("input.txt", "r");

        for (int i = 0; i < n; ++i)
        {
            double b;
            fscanf (fin, "%lf", &b);
            a.push_back(b);
        }
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {
            double b;
            b = rand();
            a.push_back(b);
        }
    }
    
    for (int i = 0; i < n; ++i)
        cout<<a[i]<<' ';
    cout<<endl;
    
    cout<<deleteElements(a, x, n);
    
    return 0;
}

unsigned long deleteElements (vector <double> a, double x, double n)
{
    for (int i = n-1; i >= 0; --i)
    {
        if (a[i]<x)
        {
            a.erase(a.begin()+i);
//            for (int i = 0; i < a.size(); ++i)
//                cout<<a[i]<<' ';
//            cout<<endl;
        }
    }
    
    return a.size();
}
