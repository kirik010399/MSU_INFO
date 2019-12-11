#ifndef tree_hpp
#define tree_hpp

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class tree
{
public:
    tree(){}
    tree(double value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }
    ~tree(){}

    double value;
    tree *left;
    tree *right;
};

void printTreeStraight(tree *p, ofstream &fout);
void printTreeCenter(tree *p, ofstream &fout);
void printTreeReverse(tree *p, ofstream &fout);
void printTreeWide(tree *p, ofstream &fout);

void printTreeStraight(tree *p, ofstream &fout)
{
    if(p != NULL)
    {
        fout<<p->value<<" ";

        printTreeStraight(p->left, fout);
        printTreeStraight(p->right, fout);
    }
}

void printTreeCenter(tree *p, ofstream &fout)
{
    if(p != NULL)
    {
        printTreeCenter(p->left, fout);

        fout<<p->value<<" ";

        printTreeCenter(p->right, fout);
    }
}

void printTreeReverse(tree *p, ofstream &fout)
{
    if(p != NULL)
    {
        printTreeReverse(p->left, fout);
        printTreeReverse(p->right, fout);
        
        fout<<p->value<<" ";
    }
}

void printTreeWide(tree *p, ofstream &fout)
{
    queue <tree*> q;
    q.push(p);
    
    while (!q.empty())
    {
        tree* elem = q.front();
        q.pop();
        
        fout<<elem->value<<" ";
        
        if (elem->left)
            q.push(elem->left);
        if (elem->right)
            q.push(elem->right);
    }
}

#endif /* tree_hpp */
