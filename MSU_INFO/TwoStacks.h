#ifndef TWOSTACKS_H
#define TWOSTACKS_H
#include <string>

using namespace std;

class TwoStacks
{
public:
    TwoStacks();
    TwoStacks(int size);
    virtual ~TwoStacks();
    int curIndex1;
    int curIndex2;
    int size;
    char *array;
    void stackNull();
    int isNull(int number);
    void addElement (string str, int number);
    string getElement (int number);
    string getVertice (int number);
    void deleteVertice (int number);

protected:

private:
};

#endif // ONESTACK_H
