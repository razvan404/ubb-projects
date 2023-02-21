#include <stdio.h>

int main()
{
    int a;
    printf("Amount: ");
    scanf("%d", &a);
    printf("The minimum number of coins is: %d\nWe will use: %d (5-units) coins, %d (2-units) coins and %d (1-unit) coins", a / 5 + (a % 5) / 2 + (a % 5) % 2, a / 5, (a % 5) / 2, (a % 5) % 2);

    return 0;
}
