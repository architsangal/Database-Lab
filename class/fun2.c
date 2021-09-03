#include<stdio.h>

void f1(int x)
{
    printf("f1 %d\n",x*x);
}

void f2(int x)
{
    printf("f2 %d\n",x+x);
}

void somefun(void(*function)(int), int secondparameter)
{
    //*function;
    function(secondparameter);
}

int main()
{
    f1(5);
    f2(10);
    return 0;
}