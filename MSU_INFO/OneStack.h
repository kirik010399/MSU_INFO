#ifndef ONESTACK_H
#define ONESTACK_H

#include <algorithm>
using namespace std;

class OneStack
{
public:
    OneStack();
    OneStack(int size);
    virtual ~OneStack();
    int curIndex;
    int *array;
    void stackNull();
    int isNull();
    void addElement (int elem);
    int getElement ();
    int getVertice ();
    void deleteVertice ();
    int arraySize; 
    
protected:
    
private:
};

#endif // ONESTACK_H

