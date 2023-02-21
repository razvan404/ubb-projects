#include <stdio.h>
#include <stdlib.h>
#define maxn 100001

int erat[maxn];

int main()
{
    for (int i = 2; i * i <= maxn; ++i)
    {
        if (!erat[i])
        {
            for (int j = 2; j * i <= maxn; ++j)
            {
                erat[i * j] = 1;
            }
        }
    }


    int n;
    printf("Give number: ");
    scanf("%d", &n);
    if (erat[n]) printf("The number is not prime!");
    else printf("The number is prime!");
}
