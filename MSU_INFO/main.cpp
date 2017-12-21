#include <stdio.h>
#include <stdlib.h>
int dlina(FILE *fin);
void GetArray(FILE *fin, double *a,int longa);
void sort(double *a,int longa);
int sravnenie(FILE *fin,double *a, double *b,int longa,int longb);

int main(void)
{
    FILE *fin1, *fin2,*fout;
    double *a;
    double *b;
    
    int longa=0,longb=0;
    
    fin1=fopen("ina.txt","r");
    fin2=fopen("inb.txt","r");
    fout=fopen("output.txt","w");
    
    if ((fin1==0)||(fin2==0))
        return -1;
    
    longa=dlina(fin1);
    longb=dlina(fin2);
    
    if ((longa==-1)||(longb==-1))
        return -1;
    
    a =(double*)malloc(longa * sizeof(double));
    b =(double*)malloc(longb * sizeof(double));
    
    fseek(fin1,0,SEEK_SET);
    fseek(fin2,0,SEEK_SET);
    
    GetArray(fin1,a,longa);
    GetArray(fin2,b,longb);
    
    sort(a,longa);
    sort(b,longb);
    
    int flag = sravnenie(fout,a,b,longa,longb);
    printf ("%d\n", flag);
    
    fclose(fin1);
    fclose(fin2);
    fclose(fout);
    return 0 ;
}

int dlina(FILE *fin)
{
    int lon=0;double x;
    while (fscanf(fin,"%lf",&x)==1)
        ++lon;
    if (lon==0)
        return -1;
    else
        return lon;
}

void GetArray(FILE *fin, double *a,int longa)
{
    int i=0;
    for (i=0;i<longa;++i)
        fscanf(fin,"%lf",&a[i]);
}

void sort(double *a,int longa)
{
    int i = 0,j = 0;double k;
    for (i=0;i < longa - 1;i++)
    {
        for (j=i+1;j<longa;j++)
        {
            if (a[i]>a[j])
            {
                k=a[i];
                a[i]=a[j];
                a[j]=k;
            }
        }
    }
}

int sravnenie(FILE *fin,double *a, double *b, int n, int m)
{
    int i=0, j=0, k=0;
    int flag = 0;
    int continueFlag = 1;
    int temp;
    
    while (k<m+n)
    {
        temp = k;
        if (i==n)
        {
            printf("%d %d %d\n",1, i , j);
            flag = 0; 
            ++k;
            ++j;
            continueFlag = 0;
        }
        printf("!!! %d %d %d\n",j, m , continueFlag);
        if (j==m && continueFlag != 0)
        {
            printf("%d %d %d\n",2, i , j);
            flag++;
            if (flag > 1)
                return -1;
            ++k;
            ++i;
            
            continueFlag = 0;
        }
        if (a[i]<b[j] && continueFlag != 0)
        {
            printf("%d %d %d\n",3, i , j);
            flag++;
            if (flag > 1)
                return -1;
            ++k;
            ++i;
        }
        else if (continueFlag != 0)
        {
            printf("%d %d %d\n",4, i , j);
            flag = 0;
            ++k;
            ++j;
        }
        continueFlag = 1;
        if (k==temp)
        {
            k++;
            printf("1");
        }
    }

    return 1;
}

