#include <stdio.h>
#include <stdlib.h>

int find_max(int n, int arr[])
{
    int Max = arr[1];
    for (int i = 2; i <= n; ++i)
    {
        if (arr[i] > Max)
            Max = arr[i];
    }
    return Max;
}

int find_min(int n, int arr[])
{
    int Min = arr[1];
    for (int i = 2; i <= n; ++i)
    {
        if (arr[i] < Min)
            Min = arr[i];
    }
    return Min;
}

int n, arr[256];

int main()
{
    printf("Give the length of array: ");
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        if (i == 1) printf("Give the 1st element: ");
        else if (i == 2) printf("Give the 2nd element: ");
        else if (i == 3) printf("Give the 3rd element: ");
        else printf("Give the %dth element: ", i);
        scanf("%d", &arr[i]);
    }
    printf("The maximum value of the array is %d and the minimum is %d\n", find_max(n, arr), find_min(n, arr));

    return 0;
}
