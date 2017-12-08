#include "RealStack.hpp"

RealStack::RealStack()
{
    stack = new double[256];
    size = -1;
    max_size = 256;
}


RealStack::RealStack(int maxSize)
{
    stack = new double[maxSize];
    size = -1;
    max_size = maxSize;
}

RealStack::~RealStack()
{
    delete [] stack;
}

bool RealStack::empty() const
{
    return size == -1;
}

void RealStack::init()
{
    size = -1;
}

int RealStack::depth() const
{
    return size+1;
}

void RealStack::push(double elem) throw(StackException)
{
    if (size < max_size-1)
    {
        size++;
        stack[size] = elem;
    }
    else throw(StackException());
}

double RealStack::pop() throw(StackException)
{
    if (size > -1)
    {
        size--;
        return stack[size+1];
    }
    else throw(StackException());
}

double RealStack::top() const throw(StackException)
{
    if (size > -1)
        return stack[size];
    else throw(StackException());
}

double RealStack::elementAt(int i) const
{
    return stack[i];
}
