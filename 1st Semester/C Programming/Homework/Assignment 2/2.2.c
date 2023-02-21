#include <stdio.h>
#include <stdlib.h>
#define maxn 100001

int erat[maxn];

void create_eratostene_array(int erat[], int size)
{
    for (int i = 2; i * i <= size; ++i)
    {
        if (!erat[i])
        {
            for (int j = 2; j * i <= size; ++j)
            {
                erat[i * j] = 1;
            }
        }
    }
}
void solve()
{
    int n;
    printf("Give number: ");
    scanf("%d", &n);
    create_eratostene_array(erat, n);
    if (erat[n]) printf("The number is not prime!");
    else printf("The number is prime!");
}

int main()
{
    solve();
}
