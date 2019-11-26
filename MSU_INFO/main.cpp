#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

int stringCompare(string s1, string s2);
struct tree* add_to_tree(struct tree *root, string new_value);
void printTree(struct tree *p, ofstream &fout);

struct tree
{
    string a;
    struct tree *left;
    struct tree *right;
    int count;
};

int main()
{
    string word;
    struct tree *root = NULL;
    ifstream fin ("input.txt");
    ofstream fout("output.txt");
            
    while (!fin.eof())
    {
        if (fin>>word)
            root = add_to_tree(root, word);
    }
    
    printTree(root, fout);
    
    return 0;
}

struct tree* add_to_tree(struct tree *root, string new_value)
{
    if (root == NULL)
    {
        root = (struct tree*)malloc(sizeof(struct tree));
        
        root->a = new_value;
        
        root->left = NULL;
        root->right = NULL;
        root->count = 1;
        return root;
    }
    
    string cur_value = root->a;
    
    if (cur_value.compare(new_value) < 0)
        root->right = add_to_tree(root->right, new_value);
    else if (cur_value.compare(new_value) > 0)
        root->left = add_to_tree(root->left, new_value);
    else
        ++root->count;
    
    return root;
}

void printTree(struct tree *p, ofstream &fout)
{
    if(p != NULL)
    {
        printTree(p->left, fout);
        fout<<"count: "<<p->count<<", word: "<<p->a<<"\n";
        printTree(p->right, fout);
    }
}
