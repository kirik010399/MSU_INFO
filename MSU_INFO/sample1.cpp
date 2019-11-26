#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

struct tree* addToTree(struct tree *root, double newValue);
void printTree(struct tree *p, ofstream &fout);

struct tree
{
    double value;
    struct tree *left;
    struct tree *right;
    int count;
};

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
    
    printTree(root, fout);
    
    return 0;
}

struct tree* addToTree(struct tree *root, double newValue)
{
    if (root == NULL)
    {
        root = (struct tree*)malloc(sizeof(struct tree));
        
        root->value = newValue;
        
        root->left = NULL;
        root->right = NULL;
        root->count = 1;
        return root;
    }
    
    double curValue = root->value;
    
    if (curValue < newValue)
        root->right = addToTree(root->right, newValue);
    else if (curValue > newValue)
        root->left = addToTree(root->left, newValue);
    else
        ++root->count;
    
    return root;
}

void printTree(struct tree *p, ofstream &fout)
{
    if(p != NULL)
    {
        printTree(p->left, fout);
        
        for (int i = 0; i < p->count; ++i)
            fout<<p->value<<" ";
        
        printTree(p->right, fout);
    }
}
