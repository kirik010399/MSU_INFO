#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int stringCompare(char* s1, char* s2);
struct tree* add_to_tree(struct tree *root, char* new_value);
void printTree(struct tree *p, FILE* fin2);

struct tree
{
    char* a;
    struct tree *left;
    struct tree *right;
    int count;
};

int lengthOfFile = 0;

int stringCompare(char* s1, char* s2)
{
    int minLength =0;
    int minNumber = 0;
    if (strlen(s1)<strlen(s2))
    {
        minLength = strlen(s1);
        minNumber = 1;
    }
    else if (strlen(s1)>strlen(s2))
    {
        minLength = strlen(s2);
        minNumber = 2;
    }
    else
    {
        int flag = 1;
        
        for (int i = 0; i < strlen(s1); ++i)
            if (s1[i]!=s2[i])
                flag = 0;
        
        if(flag==1)
            return 0;
        else
            minLength = strlen(s1); 
    }
    
    for (int i = 0; i < minLength; ++i)
    {
        if (s1[i]<s2[i])
            return -1;
        else if (s1[i]>s2[i])
            return 1;
    }
    
    if (minNumber==1)
        return -1;
    else
        return 1;
}


struct tree* add_to_tree(struct tree *root, char* new_value)
{
    if (root == NULL)
    {
        root = (struct tree*)malloc(sizeof(struct tree));
        
        root->a = strdup(new_value);
        
        root->left = NULL;
        root->right = NULL;
        root->count = 1;
        return root;
    }
    
    if (stringCompare(root->a, new_value) == -1)
        root->right = add_to_tree(root->right, new_value);
    else if (stringCompare(root->a, new_value) == 1)
        root->left = add_to_tree(root->left, new_value);
    else
        ++root->count;
    
    return root;
}

void printTree(struct tree *p, FILE* fin2)
{
    if(p != NULL)
    {
        printTree(p->left, fin2);
        fprintf(fin2,"count: %d, word: %s\n", p->count, p->a);
        printTree(p->right,fin2);
    }
}

int main(void)
{
    char name[120];
    char output[120];
    char word[120];
    char c;
    struct tree *root = NULL;
    FILE *fin = NULL;
    FILE *fin2;
    int i = 0;
    
    printf("enter the name of input file:\n");
    scanf("%s", name);
    fin = fopen(name, "r");
    
    printf("enter the name of output file:\n");
    scanf("%s", output);
    fin2 = fopen(output, "w");
    
    while(!feof(fin))
    {
        c = getc(fin);
        
        while(isalpha(c))
        {
            word[i]=c;
            c = getc(fin);
            ++i;
        }
        
        if(isalpha(word[0]))
        {
            root = add_to_tree(root, word);
        }
        
        for(i = 0; i < 120; ++i)
        {
            word[i]='\0';
        }
        i=0;
    }
    
    printTree(root, fin2);
    
    return 0;
}

