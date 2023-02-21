#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Give a number: ");
    scanf("%d", &n);
    int fibo[n + 1];
    fibo[0] = 1;
    fibo[1] = 1;
    int i = 1;
    while (i < n)
    {
        ++i;
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    }
    printf("First %d values from Fibonacci Series:\n", n);
    for (int i = 0; i < n - 1; ++i)
        printf("%d, ", fibo[i]);
    printf("%d\n", fibo[n - 1]);
    return 0;
}
