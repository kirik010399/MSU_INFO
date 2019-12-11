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
        this->height = 1;
    }
    ~tree(){}

    double value;
    int height;
    tree *left;
    tree *right;
};

int getHeight(tree *p);
int getBalanceFactor(tree *p);
void setCorrectHeight(tree *p);

int getHeight(tree *p)
{
    if (!p)
        return 0;
    else
        return p->height;
}

int getBalanceFactor(tree *p)
{
    return getHeight(p->right) - getHeight(p->left);
}

void setCorrectHeight(tree *p)
{
    int leftHeight = getHeight(p->left);
    int rightHeight = getHeight(p->right);
    
    if (leftHeight > rightHeight)
        p->height = leftHeight + 1;
    else
        p->height = rightHeight + 1;
}

tree* rotateRight(tree *p)
{
    tree *q = p->left;
    p->left = q->right;
    q->right = p;
    setCorrectHeight(p);
    setCorrectHeight(q);
    return q;
}

tree* rotateLeft(tree *q)
{
    tree *p = q->right;
    q->right = p->left;
    p->left = q;
    setCorrectHeight(q);
    setCorrectHeight(p);
    return p;
}

tree* balance(tree *p)
{
    setCorrectHeight(p);
    
    if (getBalanceFactor(p) == 2)
    {
        if (getBalanceFactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (getBalanceFactor(p) == -2)
    {
        if (getBalanceFactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

tree *addToTree(tree* p, double newValue)
{
    if (!p)
        return new tree(newValue);
    if (newValue < p->value)
        p->left = addToTree(p->left, newValue);
    else
        p->right = addToTree(p->right, newValue);
    
    return balance(p);
}

void printTreeCenter(tree *p, ofstream &fout)
{
    if(p != NULL)
    {
        printTreeCenter(p->left, fout);
        fout<<p->value<<" "<<p->height<<endl;
        printTreeCenter(p->right, fout);
    }
}

#endif /* tree_hpp */
