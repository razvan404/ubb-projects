#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Give the length of array: ");
    scanf("%d", &n);

    int Max, Min, x;
    printf("Give the 1st number: ");
    scanf("%d", &x);
    Max = x;
    Min = x;

    for (int i = 2; i <= n; i++)
    {
        if (i == 2) printf("Give the 2nd number: ");
        else if (i == 3) printf("Give the 3rd number: ");
        else printf("Give the %dth number: ", i);
        scanf("%d", &x);
        if (x > Max) Max = x;
        if (x < Min) Min = x;
    }

    printf("The maximum value of the array is %d and the minimum is %d\n", Max, Min);

    return 0;
}
