//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//struct tree* add_to_tree(struct tree *root, double new_value);// change here
//void printTree(struct tree *p, ofstream &fout);
//
//struct tree
//{
//    double value;// change here
//    struct tree *left;
//    struct tree *right;
//    int count;
//};
//
//int main()
//{
//    double value;// change here
//    struct tree *root = NULL;
//    ifstream fin("input.txt");
//    ofstream fout("output.txt");
//            
//    while (!fin.eof())
//    {
//        if (fin>>value)
//            root = add_to_tree(root, value);
//    }
//    
//    printTree(root, fout);
//    
//    return 0;
//}
//
//struct tree* add_to_tree(struct tree *root, double new_value)// change here
//{
//    if (root == NULL)
//    {
//        root = (struct tree*)malloc(sizeof(struct tree));
//        
//        root->value = new_value;
//        
//        root->left = NULL;
//        root->right = NULL;
//        root->count = 1;
//        return root;
//    }
//    
//    double cur_value = root->value;// change here
//    
//    if (cur_value < new_value)// change here
//        root->right = add_to_tree(root->right, new_value);
//    else if (cur_value > new_value)// change here
//        root->left = add_to_tree(root->left, new_value);
//    else
//        ++root->count;
//    
//    return root;
//}
//
//void printTree(struct tree *p, ofstream &fout)
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
