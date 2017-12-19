#include <iostream>
#include <vector>

using namespace std;

struct coordinates
{
    double x;
    double y;
    double z;
};

struct triangle
{
    coordinates first;
    coordinates second;
    coordinates third;
};

int main ()
{
    int n;
    cin>>n;
    coordinates a[n];
    vector <triangle> b;
    for (int i = 0; i < n; ++i)
        cin>>a[i].x>>a[i].y>>a[i].z;
    
    for (int i = 0; i < n-2; ++i)
    {
        for (int j = i+1; j < n-1; ++j)
        {
            for (int k = j+1; k < n; ++k)
            {
                //if (a[i]==a[j]||a[i]==a[k]||a[j]==a[k])
                //  continue;
                //уравнение плоскости
                //int sign;
                //sign = плоскость от первого не равного i, j, k
                //int temp = номер этого элемента
                for (int p = 0; p < n; ++p)
                {
                    //if (p==i||p==j||p==k||p==temp)
                    //  continue;
                    //if (плоскость(a[p])!=sign)
                    //  continue;
                }
                triangle tr;
                tr.first = a[i];
                tr.second = a[j];
                tr.third = a[k];
                b.push_back(tr);
            }
        }
    }
    
    for (int i = 0; i < b.size()-1; ++i)
    {
        for (int j = i + 1; j < b.size(); ++j)
        {
            //если плоскости совпадают, то все эти точки объединить в одну грань
        }
    }
    
    return 0;
}
