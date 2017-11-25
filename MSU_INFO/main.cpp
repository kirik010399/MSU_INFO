#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

struct coordinates
{
    double x = 0;
    double y = 0;
};

bool isIntersect (coordinates p1, coordinates p2, coordinates p3, coordinates p4)
{
    double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
    double x3 = p3.x, y3 = p3.y, x4 = p4.x, y4 = p4.y;
    
    double k1 = (y2-y1)/(x2-x1);
    double d1 = -(x1*y2-y1*x2)/(x2-x1);
    
    double k2 = (y4-y3)/(x4-x3);
    double d2 = -(x3*y4-y3*x4)/(x4-x3);
        
    if (k1 == k2)
    {
        if (d1 == d2)
            return true;
        else
            return false;
    }
    else
    {
        double x = (d2-d1)/(k1-k2);
        double y = k1*x+d1;
        
        coordinates v1, v2;
        v1.x = x-x1;
        v1.y = y-y1;
        
        v2.x = x-x2;
        v2.y = y-y2;
        
        coordinates v3, v4;
        v3.x = x-x3;
        v3.y = y-y3;
        
        v4.x = x-x4;
        v4.y = y-y4;
        
        if (v1.x*v2.x+v1.y*v2.y > 0 || v3.x*v4.x+v3.y*v4.y > 0)
            return false;
        else
            return true;
    }
}

int main()
{
    coordinates p;
    vector <coordinates> a;
    
    FILE* fin;
    FILE* fout;
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    
    double x, y;
    
    while(fscanf(fin,"%lf%lf",&x, &y)!=EOF)
    {
        p.x = x;
        p.y = y;
        a.push_back(p);
    }
    
    for (int i = 0; i < a.size()-1; ++i)
    {
        for (int j = i+2; j < a.size()-1; ++j)
        {
            if (isIntersect(a[i], a[i+1], a[j], a[j+1]))
            {
                fprintf (fout, "%d", 0);
                return 0;
            }
        }
    }
    
    fprintf (fout, "%d", 1);

    return 0;
}

