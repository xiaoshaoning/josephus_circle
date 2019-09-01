#include <stdio.h>

int f(n, m)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return (f(n-1, m)-1+m) % n + 1;
    }
}

int main(int argc, char ** argv)
{
    int n, m;

    if (argc != 3)
    {
        printf("usage: ./josephus_circle_recursive n m");
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);

    printf("The survivor is %d\n", f(n, m));

    return 0;
}
