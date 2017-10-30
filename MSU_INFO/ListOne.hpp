//
//  ListOne.hpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 14.10.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#ifndef ListOne_hpp
#define ListOne_hpp

#include <stdio.h>

#include <algorithm>
#include <iostream>

#include <stdio.h>

using namespace std;

class MySpisok
{
public:
    ~MySpisok();
    int *el;
    int *ss;
    int *ssz;
    MySpisok(int a);
    int n_pusto();
    int url(int a);
    int urlz(int a);
    void pered_cursor();
    void pered_cursor_naz();
    void push(int a);
    void push_z(int a);
    void print(); 
    int pop();
    int pop_z();
    int get_element();
    int get_element_z();
    void del();
    void del_z();
    void sdpust();
    int get_cur_size();
    void cursor_clear();
    void cursor_end();
    int url_cursor();
    int urlz_cursor();
    int get_max_size();
    int get_start();
    int get_endd();
    int get_cursor();
protected:
private:
    MySpisok();
    // int *ss;
    //int *el;
    int start,cursor,cur_size,max_size,endd;
};




#endif /* ListOne_hpp */
