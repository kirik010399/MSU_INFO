//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//template <class T>
//class tree
//{
//public:
//    tree(){}
//    tree(T value)
//    {
//        this->value = value;
//    }
//    ~tree();
//
//    T value;
//    tree *left;
//    tree *right;
//    int count;
//};
//
//template <class T>
//tree <T>* addToTree(tree <T> *root, T newValue);
//
//template <class T>
//void printTree(tree <T> *p, ofstream &fout);
//
//int main()
//{
//    int value;// change here
//    ifstream fin("input.txt");
//    ofstream fout("output.txt");
//            
//    tree <int> *root = NULL;// change here
//
//    while (!fin.eof())
//    {
//        if (fin>>value)
//            root = addToTree(root, value);
//    }
//    
//    printTree(root, fout);
//    
//    return 0;
//}
//
//template <class T>
//tree <T>* addToTree(tree <T> *root, T newValue)
//{
//    if (root == NULL)
//    {
//        tree <T> *newRoot = new tree <T> (newValue);
//                
//        newRoot->left = NULL;
//        newRoot->right = NULL;
//        newRoot->count = 1;
//        return newRoot;
//    }
//    
//    T curValue = root->value;
//    
//    if (curValue < newValue)
//        root->right = addToTree(root->right, newValue);
//    else if (curValue > newValue)
//        root->left = addToTree(root->left, newValue);
//    else
//        ++root->count;
//    
//    return root;
//}
//
//template <class T>
//void printTree(tree <T> *p, ofstream &fout)
//{
//    if(p != NULL)
//    {
//        printTree(p->left, fout);
//
//        for (int i = 0; i < p->count; ++i)
//            fout<<p->value<<" ";
//
//        printTree(p->right, fout);
//    }
//}
