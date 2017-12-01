#include <stdio.h>
#include <math.h>
#define N 10000

int line(int *a,int *b,int v);// function of checking of intersection
int getarray(int *a,int *b, FILE *fin);// reading of array

int main(void)
{
    FILE *fin;// file with data
    int a[N];// array with x coordinates
    int b[N];// array with y coordinates
    char imya[120];// the name of file with data
    
    int v = 0,k = 0;
    printf("Enter the name of file with data\n");
    scanf("%s", imya);
    fin = fopen(imya, "r");
    
    v = getarray(a,b,fin);// checking if data were readed
    
    if (v != -1)
        k = line(a,b,v);//answer if there is points of intersection
    else
        return -1;
    
    if (k == 1)
        printf("there is points of intersection\n");
    else
        printf("there isn't points of intersection\n");
    
    fclose(fin);
    return 0;
}

int line(int *a, int *b, int v)
{
    int i = 0, j = 0;
    int x1,y1,x2,y2,x3,x4,y3,y4;
    int flag;
    double v1x, v2x, v1y, v2y;
    double v3x, v4x, v3y, v4y;
    double x, y, k1, d1, k2, d2;

    for (i = 0; i < v-1; ++i)
    {
        for (j = i+2; j < v-1; ++j)
        {
            x1 = a[i];
            x2 = a[i+1];
            y1 = b[i];
            y2 = b[i+1];
            x3 = a[j];
            x4 = a[j+1];
            y3 = b[j];
            y4 = b[j+1];
            
            k1 = (y2-y1)/(x2-x1);
            d1 = -(x1*y2-y1*x2)/(x2-x1);
            
            k2 = (y4-y3)/(x4-x3);
            d2 = -(x3*y4-y3*x4)/(x4-x3);
            
            if (k1 == k2)
            {
                if (d1 == d2)
                    flag = 1;
                else
                    flag = -1;
            }
            else
            {
                x = (d2-d1)/(k1-k2);
                y = k1*x+d1;
                
                v1x = x-x1;
                v1y = y-y1;
                
                v2x = x-x2;
                v2y = y-y2;
                
                v3x = x-x3;
                v3y = y-y3;
                
                v4x = x-x4;
                v4y = y-y4;
                
                if (v1x*v2x+v1y*v2y > 0 || v3x*v4x+v3y*v4y > 0)
                    flag = -1;
                else
                    flag = 1;
            }
            if (flag == 1)
                return 1;
        }
    }
    return -1;
}

int getarray(int *a, int *b, FILE *fin)
{
    int i = 0;
    int var;
    int x, y;
    i=0;
    
    while (true)
    {
        var = fscanf(fin,"%d%d",&x,&y);

        if (var == EOF)
        {
            if (i==0)
            {
                printf("Your file is empty\n");
                return -1;
            }
            else
                break;
        }
        if (var == -1)
        {
            printf("Your data is wrong\n");
            break;
        }
        
        a[i] = x;
        b[i] = y;
        ++i;
    }
    return i;
}
