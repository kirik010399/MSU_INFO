#include <stdio.h>
#include <iostream>
//#include <string>

using namespace std;

int main()
{
    int a[36];
    int i;

    for (int i = 0; i < 36; ++i)
        a[i] = 0;

    char ch;
    cin>>ch;
    if(ch!='-')
    {
        if (ch>='a' && ch<='z')
            ++a[ch-'a'];
        if (ch>='0' && ch<='9')
            ++a[26 + ch-'0'];
    }

    while(ch != '-')
    {
        if (ch>='a' && ch<='z')
            ++a[ch-'a'];
        if (ch>='0' && ch<='9')
            ++a[26 + ch-'0'];
        cin>>ch;
    }

    for (i = 0 ; i<26 ;++i)
    {
        int c = 'a'+i;
        printf ("%d ", c);
        cout<<a[i]<<endl;
    }
    for (int i = 26; i < 36; ++i)
    {
        cout<<i-26<<' '<<a[i]<<endl;
    }
    return 0;
}


