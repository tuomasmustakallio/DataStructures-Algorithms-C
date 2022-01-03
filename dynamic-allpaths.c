#include <stdio.h>
#define S 21

int main()
{

    int f[S+2];

    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= S; i++)
    {
        f[i] = f[i-1] + f[i-2];
    }

    printf("%d", f[S]);

    return 0;
}