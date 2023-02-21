#include <stdio.h>

int main()
{
    int a, b;
    printf("First number: ");
    scanf("%d", &a);
    printf("Second number: ");
    scanf("%d", &b);
    printf("Sum: %d\nAverage: %d.%d\nSum of the squares: %d", a + b, (a + b) / 2, (a + b) * 10 / 2 % 10, a * a + b * b);

    return 0;
}
