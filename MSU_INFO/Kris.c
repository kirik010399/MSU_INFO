#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
//#include <string>

//using namespace std;

int main()
{
    int n = 0, m = 0;
    double *a;
    a = (double*)malloc(n * m * sizeof (double));
    scanf("%d%d", &n, &m);
    
    //проход по строкам
    for (int i = 0; i < n; ++i)//строки
    {
        for (int j = 0; j < m; ++j)//столбцы
        {
            scanf("%lf", &a[i*m+j]);
        }
    }
    
    //    проход по столбцам
    //    for (int i = 0; i < m; ++i)//стобцы
    //    {
    //        for (int j = 0; j < n; ++j)//строки
    //        {
    //             scanf("%lf", &a[j*m+i]);
    //        }
    //    }
    
    int min = a[0*m+0];
    int minstr = 0;
    
    for (int i = 0; i < n; ++i)//строки
    {
        for (int j = 0; j < m; ++j)//столбцы
        {
            //i, j элемент - a[i*m+j]
            if (a[i*m+j] < min)
            {
                min = a[i*m+j];
                minstr = i;
            }
        }
    }
    
    
    for (int i = 0; i < n; ++i)//строки
    {
        for (int j = 0; j < m; ++j)//столбцы
        {
            //i, j элемент - a[i*m+j]
            if(i != minstr)
                a[i*m+j]+=a[minstr*m+j];
        }
    }
    
    for (int j = 0; j < m; ++j)
    {
        a[minstr*m+j]*=2;
    }
    
    //проход по строкам
    for (int i = 0; i < n; ++i)//строки
    {
        for (int j = 0; j < m; ++j)//столбцы
        {
            printf("%lf ", a[i*m+j]);
        }
        printf("\n");
    }
    
    //0 1 2 3
    //4 5 6 7
    //8 9 10 11
    
    
    //    int a[36];
    //    int i;
    //
    //    for (int i = 0; i < 36; ++i)
    //        a[i] = 0;
    //
    //    char ch;
    //    cin>>ch;
    //    if(ch!='-')
    //    {
    //        if (ch>='a' && ch<='z')
    //            ++a[ch-'a'];
    //        if (ch>='0' && ch<='9')
    //            ++a[26 + ch-'0'];
    //    }
    //
    //    while(ch != '-')
    //    {
    //        if (ch>='a' && ch<='z')
    //            ++a[ch-'a'];
    //        if (ch>='0' && ch<='9')
    //            ++a[26 + ch-'0'];
    //        cin>>ch;
    //    }
    //
    //    for (i = 0 ; i<26 ;++i)
    //    {
    //        int c = 'a'+i;
    //        printf ("%d ", c);
    //        cout<<a[i]<<endl;
    //    }
    //    for (int i = 26; i < 36; ++i)
    //    {
    //        cout<<i-26<<' '<<a[i]<<endl;
    //    }
    //    return 0;
}





