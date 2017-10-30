//
//  ListOne.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#include "ListOne.hpp"

MySpisok::MySpisok(int a)
{
    //ctor
    el= new int [a+2];
    ss= new int [a+2];
    ssz = new int [a+2];
    for (int i=0; i<(a+2); i++){
        ss[i]=-2;
        el[i]=0;
    }
    ss[0]=-1;
    ssz[0]= a+1;
    ss[a+1]=0;
    ssz[a+1]=-1;
    start =a+1;
    endd = 0;
    cursor = 0;
    cur_size=0;
    max_size=a;
}

int MySpisok::n_pusto(){
    int i=0;
    while ((ss[i]!=(-2))&&(i<=(max_size+1))){
        i++;
    }
    if (i==(max_size+2)) return -1;
    return i;
}

int MySpisok::url(int a){
    return ss[a];
}

int MySpisok::urlz(int a){
    return ssz[a];
}

void MySpisok::pered_cursor(){
    if (url(cursor)>(-1)){
        cursor=url(cursor);
    }
}

void MySpisok::pered_cursor_naz(){
    if (urlz(cursor)>(-1)){
        cursor=urlz(cursor);
    }
}

void MySpisok::push(int a){ //ƒÓ·‡‚ËÚ¸ Á‡ ÛÍ‡Á‡ÚÂÎÂÏ
    if ((cur_size<max_size)&&(url(cursor)>-2)){
        if (urlz(cursor)!=(-1)){
            int el1=el[cursor];
            int s1=ss[cursor];
            int sz=ssz[cursor];
            int num = n_pusto();
            el[cursor]=a;
            ss[cursor]=num;
            el[num]=el1;
            ss[num]=s1;
            cur_size++;
            if (s1==(-1)) endd = num;
        } else {
            int num=n_pusto();
            el[cursor]=a;
            ssz[cursor]=num;
            ssz[num]=-1;
            ss[num]=cursor;
            start = num;
            cur_size++;
        }
    }
    print();
}

void MySpisok::push_z(int a){ //ƒÓ·‡‚ËÚ¸ Á‡ ÛÍ‡Á‡ÚÂÎÂÏ
    int r=cursor;
    pered_cursor_naz();
    if ((cur_size<max_size)&&(url(cursor)>-2)){
        if (urlz(cursor)!=(-1)){
            int el1=el[cursor];
            int s1=ss[cursor];
            int sz=ssz[cursor];
            int num = n_pusto();
            el[cursor]=a;
            ss[cursor]=num;
            el[num]=el1;
            ss[num]=s1;
            cur_size++;
            if (s1==(-1)) endd = num;
        } else {
            int num=n_pusto();
            el[cursor]=a;
            ssz[cursor]=num;
            ssz[num]=-1;
            ss[num]=cursor;
            start = num;
            cur_size++;
        }
    }
    cursor=r;
    print();
}

int MySpisok::pop(){ // ¬ÁˇÚ¸ ˝ÎÂÏÂÌÚ Á‡ ÛÍ‡Á‡ÚÂÎÂÏ
    if ((cur_size>0)&&(url(cursor)>-1)&&(urlz(cursor)>-1)){
        int p=el[cursor];
        int s1=ss[cursor];
        el[cursor]=el[s1];
        ss[cursor]=ss[s1];
        ss[s1]=-2;
        if (s1==endd) endd=cursor;
        cur_size--;
        print();

        return p;
    }
    print();

    return -1;
}

int MySpisok::pop_z(){ // ¬ÁˇÚ¸ ˝ÎÂÏÂÌÚ Á‡ ÛÍ‡Á‡ÚÂÎÂÏ
    pered_cursor_naz();
    if ((cur_size>0)&&(url(cursor)>-1)&&(urlz(cursor)>-1)){
        int p=el[cursor];
        int s1=ss[cursor];
        el[cursor]=el[s1];
        ss[cursor]=ss[s1];
        ss[s1]=-2;
        if (s1==endd) endd=cursor;
        cur_size--;
        print();

        return p;
    }
    print();

    return -1;
}

int MySpisok::get_element(){
    return el[cursor];
}

int MySpisok::get_element_z(){
    return el[urlz(cursor)];
}



void MySpisok::del(){
    if (cur_size>0){
        
        int s1=ss[cursor];
        el[cursor]=el[s1];
        ss[cursor]=ss[s1];
        ss[s1]=-2;
        if (s1==endd) endd=cursor;
        cur_size--;
        print();

    }
}

void MySpisok::del_z(){
    pered_cursor_naz();
    if (cur_size>0){
        
        int s1=ss[cursor];
        el[cursor]=el[s1];
        ss[cursor]=ss[s1];
        ss[s1]=-2;
        if (s1==endd) endd=cursor;
        cur_size--;
        print();

    }
}

void MySpisok::sdpust(){
    for (int i=0; i<(max_size+2); i++){
        ss[i]=-2;
        el[i]=0;
    }
    ss[0]=-1;
    ssz[0]= max_size+1;
    ss[max_size+1]=0;
    ssz[max_size+1]=-1;
    start =max_size+1;
    endd = 0;
    cursor = 0;
    cur_size=0;
}

int MySpisok::get_cur_size(){
    return cur_size;
}

void MySpisok::cursor_clear(){
    cursor=ss[start];
}

void MySpisok::cursor_end(){
    cursor=endd;
}

int MySpisok::url_cursor(){
    return ss[cursor];
}

int MySpisok::urlz_cursor(){
    return ssz[cursor];
}

int MySpisok::get_max_size(){
    return max_size;
}

int MySpisok::get_start(){
    return start;
}

int MySpisok::get_endd(){
    return endd;
}

int MySpisok::get_cursor(){
    return cursor;
}

MySpisok::~MySpisok()
{
    //dtor
    delete [] el;
    delete [] ss;
    delete [] ssz;
}

void MySpisok::print ()
{
    for (int i = 0; i < max_size; ++i)
    {
        cout<<el[i]<<' ';
    }
    cout<<endl;
    for (int i = 0; i < max_size; ++i)
    {
        cout<<ss[i]<<' ';
    }
    cout<<endl;
    for (int i = 0; i < max_size; ++i)
    {
        cout<<ssz[i]<<' ';
    }
    cout<<endl;
}

