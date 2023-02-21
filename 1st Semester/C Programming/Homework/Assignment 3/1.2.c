#include <stdio.h>
#define lim 256
#define true 1
#define false 0

void read(int *p, int n)
{
    for (int i = 0; i < n; ++i)
    {
        printf("Element %d: ", i);
        scanf("%d", p + i);
    }
}

void bubblesort(int *p, int n)
{
    short change = true;
    while (change)
    {
        change = false;
        for (int i = 0; i < n - 1; ++i)
        {
            if (*(p + i) > *(p + i + 1))
            {
                int aux = *(p + i);
                *(p + i) = *(p + i + 1);
                *(p + i + 1) = aux;
                change = true;
            }
        }
    }
}

void merge(int *p1, int n1, int *p2, int n2, int *pans)
{
    for (int i = 0; i < n1; ++i)
    {
        *pans = *(p1 + i);
        pans++;
    }

    for (int i = 0; i < n2; ++i)
    {
        *pans = *(p2 + i);
        pans++;
    }
}

int s1[lim], s2[lim], ans[2 * lim], n1, n2;
int *p1, *p2, *pans;

int main()
{
    p1 = &s1;
    p2 = &s2;
    pans = &ans;

    printf("Give length of first array: ");
    scanf("%d", &n1);
    read(p1, n1);
    bubblesort(p1, n1);

    printf("Give length of second array: ");
    scanf("%d", &n2);
    read(p2, n2);
    bubblesort(p2, n2);

    merge(p1, n1, p2, n2, pans);
    printf("The merged array of the sorted arrays: ");
    for (int i = 0; i < n1 + n2; ++i)
        printf("%d ", ans[i]);

    return 0;
}
