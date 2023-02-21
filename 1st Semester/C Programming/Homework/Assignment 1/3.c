#include <stdio.h>

int main()
{
    int x;
    printf("Enter the numbers: ");
    scanf("%d", &x);
    int Max = x, Min = x;

    for (int i = 2; i <= 5; ++i)
    {
        scanf("%d", &x);
        if (x > Max) Max = x;
        if (x < Min) Min = x;
    }

    printf("Biggest number: %d\nSmallest number: %d", Max, Min);

    return 0;
}
