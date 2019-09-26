#include <stdio.h>

void badAddOneToNumber(double a);
void goodAddOneToNumber(double *a);

int main(void)
{
    double a = 5;

    badAddOneToNumber(a);//передача в функцию обычным способом, в данном случае изменения внутри функции не подействуют на переменную внутри main, переменная a останется равной 5
    goodAddOneToNumber(&a);//передача в фукнцию с помощью указателей, в данном случае изменения внутри функции изменят переменную a и внутри main, она будет равной 6

    return 0;
}

void badAddOneToNumber(double a)
{
    a = a + 1;
}

void goodAddOneToNumber(double *a)//на вход в функцию передается не просто a, а указатель на нее, для этого здесь и далее перед названием переменной нужно писать *
{
    *a = *a + 1;
}

