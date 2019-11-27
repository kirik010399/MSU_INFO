#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class tree
{
public:
    tree(){}
    tree(T value)
    {
        this->value = value;
    }
    ~tree();

    T value;
    tree *left;
    tree *right;
    int count;
};

template <class T>
tree <T>* addToTree(tree <T> *root, T newValue);

template <class T>
void printTree(tree <T> *p);

template <class T>
bool findValue(tree <T> *p, T x);

int main()
{
    string value;// change here
    ifstream fin("input.txt");
    ofstream fout("output.txt");
            
    tree <string> *root = NULL;// change here
    
    string x;//change here
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

template <class T>
bool findValue(tree <T> *p, T x)
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

template <class T>
tree <T>* addToTree(tree <T> *root, T newValue)
{
    if (root == NULL)
    {
        tree <T> *newRoot = new tree <T> (newValue);
                
        newRoot->left = NULL;
        newRoot->right = NULL;
        newRoot->count = 1;
        return newRoot;
    }
    
    T curValue = root->value;
    
    if (curValue < newValue)
        root->right = addToTree(root->right, newValue);
    else if (curValue > newValue)
        root->left = addToTree(root->left, newValue);
    else
        ++root->count;
    
    return root;
}

template <class T>
void printTree(tree <T> *p)
{
    if(p != NULL)
    {
        printTree(p->left);

        for (int i = 0; i < p->count; ++i)
            cout<<p->value<<" ";

        printTree(p->right);
    }
}
