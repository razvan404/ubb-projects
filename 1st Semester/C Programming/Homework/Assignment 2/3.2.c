#include <stdio.h>
#include <stdlib.h>

void print_first_digit(int h)
{
    if (h == 1) printf("one hundred ");
    if (h == 2) printf("two hundred ");
    if (h == 3) printf("three hundred ");
    if (h == 4) printf("four hundred ");
    if (h == 5) printf("five hundred ");
    if (h == 6) printf("six hundred ");
    if (h == 7) printf("seven hundred ");
    if (h == 8) printf("eight hundred ");
    if (h == 9) printf("nine hundred ");
}

void print_last_two_digits(int z, int u)
{
    if (z == 2) printf("twenty ");
    if (z == 3) printf("thirty ");
    if (z == 4) printf("fourty ");
    if (z == 5) printf("fifty ");
    if (z == 6) printf("sixty ");
    if (z == 7) printf("seventy ");
    if (z == 8) printf("eighty ");
    if (z == 9) printf("ninety ");

    if (u == 1 && z != 1) printf("one");
    if (u == 2 && z != 1) printf("two");
    if (u == 3 && z != 1) printf("three");
    if (u == 4 && z != 1) printf("four");
    if (u == 5 && z != 1) printf("five");
    if (u == 6 && z != 1) printf("six");
    if (u == 7 && z != 1) printf("seven");
    if (u == 8 && z != 1) printf("eight");
    if (u == 9 && z != 1) printf("nine");

    if (z == 1)
    {
        if (u == 0) printf("ten");
        if (u == 1) printf("eleven");
        if (u == 2) printf("twelve");
        if (u == 3) printf("thirteen");
        if (u == 4) printf("fourteen");
        if (u == 5) printf("fifteen");
        if (u == 6) printf("sixteen");
        if (u == 7) printf("seventeen");
        if (u == 8) printf("eighteen");
        if (u == 9) printf("nineteen");
    }
}

int main()
{
    int n, h, z, u;
    printf("Give a number: ");
    scanf("%d", &n);

    h = n / 100;
    z = n / 10 % 10;
    u = n % 10;

    printf("The value in words: ");
    print_first_digit(h);
    print_last_two_digits(z, u);
    if (u == 0 && z == 0 && h == 0) printf("zero");
    printf("\n");

    return 0;
}
