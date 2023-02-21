#include <stdio.h>
#define lim 256
#define true 1
#define false 0

int s1[lim], s2[lim], ans[2 * lim], n1, n2, change;

int main()
{
    printf("Give length of first array: ");
    scanf("%d", &n1);
    for (int i = 0; i < n1; ++i)
    {
        printf("Element %d: ", i);
        scanf("%d", &s1[i]);
    }
    change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < n1 - 1; ++i)
        {
            if (s1[i] > s1[i + 1])
            {
                int aux = s1[i];
                s1[i] = s1[i + 1];
                s1[i + 1] = aux;
                change = true;
            }
        }
    }
    for (int i = 0; i < n1; ++i)
    {
        ans[i] = s1[i];
    }

    printf("Give length of second array: ");
    scanf("%d", &n2);
    for (int i = 0; i < n2; ++i)
    {
        printf("Element %d: ", i);
        scanf("%d", &s2[i]);
    }
    change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < n2 - 1; ++i)
        {
            if (s2[i] > s2[i + 1])
            {
                int aux = s2[i];
                s2[i] = s2[i + 1];
                s2[i + 1] = aux;
                change = true;
            }
        }
    }
    for (int i = n1; i < n1 + n2; ++i)
    {
        ans[i] = s2[i - n1];
    }

    printf("The merged array of the sorted arrays: ");
    for (int i = 0; i < n1 + n2; ++i)
        printf("%d ", ans[i]);

    return 0;
}
