#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "tree.hpp"

using namespace std;

int main()
{
    ofstream fout("output.txt");

    tree *root = new tree (1);
    root->left = new tree (2);
    root->right = new tree (3);
    root->left->left = new tree(4);
    root->left->right = new tree(5);
    root->right->right = new tree(6);
    root->left->right->left = new tree(7);
    root->left->right->right = new tree(8);
    root->right->right->left = new tree(9);
    
    printTreeStraight(root, fout);
    fout<<endl;
    printTreeCenter(root, fout);
    fout<<endl;
    printTreeReverse(root, fout);
    fout<<endl;
    printTreeWide(root, fout);
    fout<<endl;
    
    return 0;
}

