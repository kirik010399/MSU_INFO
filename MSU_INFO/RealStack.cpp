//
//  RealStack.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 18.11.2017.
//  Copyright © 2017 Кирилл Мащенко. All rights reserved.
//

#include "RealStack.hpp"

class StackException {
public:
    const char *reason;
    StackException():
    reason("")
    {}
    
    StackException(const char *cause):
    reason(cause)
    {}
};

class RealStack {
private:
    double* stack;
    int max_size;
    int size;
public:
    RealStack();
    RealStack(int maxSize);
    ~RealStack();
    void push(double) throw (StackException);
    double pop() throw (StackException);
    double top() const throw (StackException);
    int depth() const;
    void init();
    bool empty() const;
    double elementAt(int i) const;
};
