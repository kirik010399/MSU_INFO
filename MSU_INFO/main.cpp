#include <iostream>
#include <vector>
#include "R3Vec.1.h"

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

bool eq(coordinates a, coordinates b)
{
    if (a.x==b.x && a.y==b.y && a.z==b.z)
        return true;
    else
        return false;
}

int main ()
{
    int n;
    cin>>n;
    coordinates a[n];
    vector <triangle> b;
    
    for (int i = 0; i < n; ++i)
        cin>>a[i].x>>a[i].y>>a[i].z;
    cout<<1;
    for (int i = 0; i < n-2; ++i)
    {
        cout<<2;
        for (int j = i+1; j < n-1; ++j)
        {
            cout<<3;
            for (int k = j+1; k < n; ++k)
            {
                cout<<4;
                if (eq(a[i], a[j]) || eq(a[i], a[k]) || eq(a[j], a[k]))
                  continue;

                R3Vec v1(a[i].x-a[j].x, a[i].y-a[j].y, a[i].z-a[j].z);
                R3Vec v2(a[k].x-a[j].x, a[k].y-a[j].y, a[k].z-a[j].z);

                R3Vec v3((v1^v2).x, (v1^v2).y, (v1^v2).z);
                
                double A = v3.x;
                double B = v3.y;
                double C = v3.z;
                double D = -A*a[i].x-B*a[i].y-C*a[i].z;
                
                bool sign = false;
                int temp = 0;
                
                for (int p = 0; p < n; ++p)
                {
                    cout<<5;
                    if (p != i && p != j && p !=k)
                    {
                        temp = p;
                        sign = (A*a[p].x+B*a[p].y+C*a[p].x+D > 0);
                        break;
                    }
                }
                
                for (int p = 0; p < n; ++p)
                {
                    cout<<6;
                    if (p==i||p==j||p==k||p==temp)
                      continue;
                    
                    if ((A*a[p].x+B*a[p].y+C*a[p].x+D>0) != sign)
                      continue;
                }
                triangle tr;
                tr.first = a[i];
                tr.second = a[j];
                tr.third = a[k];
                b.push_back(tr);
            }
        }
    }
    
    vector < vector <int> > borders;
    
    for (int i = 0; i < b.size()-1; ++i)
    {
        cout<<7;
        for (int j = i + 1; j < b.size(); ++j)
        {
            cout<<8;
            R3Vec v1(b[j].first.x-b[j].second.x, b[j].first.y-b[j].second.y, b[j].first.z-b[j].second.z);
            R3Vec v2(b[j].third.x-b[j].second.x, b[j].third.y-b[j].second.y, b[j].third.z-b[j].second.z);
            
            R3Vec v3((v1^v2).x, (v1^v2).y, (v1^v2).z);
            
            R3Vec v4(b[i].first.x-b[i].second.x, b[i].first.y-b[i].second.y, b[i].first.z-b[i].second.z);
            R3Vec v5(b[i].third.x-b[i].second.x, b[i].third.y-b[i].second.y, b[i].third.z-b[i].second.z);
        
            R3Vec v6((v1^v2).x, (v1^v2).y, (v1^v2).z);
            
            double o = v3.x/v6.x;
            double t = v3.y/v6.y;
            double c = v3.z/v6.z;
            
            if (o==t && t==c)
            {
                double x = b[j].first.x;
                double y = b[j].first.y;
                double z = b[j].first.z;
                
                double A = v6.x;
                double B = v6.y;
                double C = v6.z;
                double D = -A*b[i].first.x-B*b[i].first.y-C*b[i].first.z;
                
                bool flag = false;
                if (A*x+B*y+C*z+D == 0)
                {
                    if (borders.size()!=0)
                    for (int u = 0; u < borders.size(); ++u)
                    {
                    
                        int length = borders[u].size();
                        if (borders[u].size() != 0)
                        for (int ety = 0; ety < length; ++ety)
                        {
                            if (i == borders[u][ety])
                            {
                                borders[u].push_back(j);
                                flag = true;
                            }
                            else
                            if (j == borders[u][ety])
                            {
                                borders[u].push_back(i);
                                flag = true;
                            }
                        }
                    }
                    
                    if (!flag)
                    {
                        vector <int> er;
                        er.push_back(i);
                        er.push_back(j);
                        borders.push_back(er);
                    }
                }
                else
                {
                    bool flag = false;
                    for (int u = 0; u < borders.size(); ++u)
                    {
                        cout<<11;
                        for (int e = 0; e < borders[u].size(); ++e)
                        {
                            cout<<12;
                            if (i == borders[u][e])
                                flag = true;
                        }
                    }
                    if (!flag)
                    {
                        vector <int> er;
                        er.push_back(i);
                        borders.push_back(er);
                    }
                    
                    bool flag1 = false;
                    for (int u = 0; u < borders.size(); ++u)
                    {
                        cout<<13;
                        for (int e = 0; e < borders[u].size(); ++e)
                        {
                            cout<<14;
                            if (j == borders[u][e])
                                flag1 = true;
                        }
                    }
                    if (!flag1)
                    {
                        vector <int> er;
                        er.push_back(j);
                        borders.push_back(er);
                    }
                }
            }
        }
    }
    
    vector < vector <coordinates> > lew;
    
    for (int i = 0; i < borders.size(); ++i)
    {
        cout<<15;
        vector <coordinates> wer;
        for (int j = 0; j < borders[i].size(); ++j)
        {
            cout<<16;
            coordinates fir = b[borders[i][j]].first;
            coordinates sec = b[borders[i][j]].second;
            coordinates th = b[borders[i][j]].third;
            
            bool flag = true;
            for (int k = 0; k < wer.size(); ++k)
            {
                cout<<17;
                if (eq(fir, wer[i]))
                    flag = false;
            }
            if (flag)
                wer.push_back(fir);
            
            flag = true;
            for (int k = 0; k < wer.size(); ++k)
            {
                cout<<18;
                if (eq(sec, wer[i]))
                    flag = false;
            }
            if (flag)
                wer.push_back(sec);
            
            flag = true;
            for (int k = 0; k < wer.size(); ++k)
            {
                cout<<19;
                if (eq(th, wer[i]))
                    flag = false;
            }
            if (flag)
                wer.push_back(th);
        }
        lew.push_back(wer);
    }
    
    for (int i = 0; i < lew.size(); ++i)
    {
        cout<<i<<endl;
        for (int j = 0; j < lew[i].size(); ++j)
        {
            cout<<lew[i][j].x<<' '<<lew[i][j].y<<' '<<lew[i][j].z<<endl;
        }
    }
    //в lew ответ
        
    
    return 0;
}
