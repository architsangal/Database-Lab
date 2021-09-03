#include<stdio.h>

void f1(void)
{
    printf("f1\n");
}

void f2(void)
{
    printf("f2\n");
}

void somefun(void(*function)(void))
{
    *function;
    function();
}

int main()
{
    f1();
    f2();
    return 0;
}