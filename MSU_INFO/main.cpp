#include "table.h"
#include <string>
#include <assert.h>
#include <vector>
#include <iostream>

int main()
{
    Table a;
    a["A99"] = (float)1.5;
    
    cout<<(a["A99"].toFloat()==(float)1.5);
    return 0;
}
