#include <iostream>
#include <stdio.h>
#include "any.h"

#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


double sin (double x)
{
    double res = 0, d = 1, fact = 1;
    int i = 1;
    
    while (d/fact>=0.0000000001 || d/fact<=-0.0000000001)
    {
        if (i%2!=1)
        {
            if (i%4==2)
                res+=d/fact;
            else if (i%4==0)
                res-=d/fact;
        }
        d*=x;
        fact*=i;
        i++;
    }
    
    return res;
}

int main()
{
    double x;
    cin>>x;
    cout<<sin(x)<<endl;
}

