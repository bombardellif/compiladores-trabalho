#include <stdio.h>

int foo(int b, int c)
{
    if(b > 2 + c)
        b = 10;
    else
        b = 1;
    return b;
}

int main()
{
    printf("%d\n",foo(5, 9));
}