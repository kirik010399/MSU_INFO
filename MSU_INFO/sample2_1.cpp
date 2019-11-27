#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

struct tree
{
    string value;// change here
    struct tree *left;
    struct tree *right;
    int count;
};

struct tree* addToTree(struct tree *root, string newValue);// change here
void printTree(struct tree *p);
bool findValue(struct tree *p, string x);//change here

int main()
{
    string value;// change here
    struct tree *root = NULL;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    
    string x;// change here
    fin>>x;
       
    while (!fin.eof())
    {
        if (fin>>value)
            root = addToTree(root, value);
    }
    
    printTree(root);

    bool retFlag = findValue(root, x);
    fout<<retFlag<<endl;
    
    return 0;
}

bool findValue(struct tree *p, string x)// change here
{
    if (!p->left && !p->right)
        return x == p->value;
    
    if (x < p->value)
    {
        if (p->left)
            return findValue(p->left, x);
        else
            return false;
    }
    if (x > p->value)
    {
        if (p->right)
            return findValue(p->right, x);
        else
            return false;
    }
    else
    {
        return true;
    }
}

struct tree* addToTree(struct tree *root, string newValue)// change here
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
    
    string curValue = root->value;// change here
    
    if (curValue < newValue)// change here
        root->right = addToTree(root->right, newValue);
    else if (curValue > newValue)// change here
        root->left = addToTree(root->left, newValue);
    else
        ++root->count;
    
    return root;
}

void printTree(struct tree *p)
{
    if(p != NULL)
    {
        printTree(p->left);
        
        for (int i = 0; i < p->count; ++i)
            cout<<p->value<<" ";
        
        printTree(p->right);
    }
}
