#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "tree.hpp"

using namespace std;

int main()
{
    double value;
    struct tree *root = NULL;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
            
    while (!fin.eof())
    {
        if (fin>>value)
            root = addToTree(root, value);
    }
    
    printTreeCenter(root, fout);
    
    return 0;
}


