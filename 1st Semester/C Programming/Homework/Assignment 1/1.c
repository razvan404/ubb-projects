#include <stdio.h>

int main()
{
    float Length, pi = 3.14159;
    printf("Length: ");
    scanf("%f", &Length);

    float Area1 = pi * (Length * Length);
    double Area2 = pi * (Length * Length);

    printf("Area in float: %f\nArea in double: %f", Area1, Area2);

    if (Area1 > Area2)
        printf("\nArea in float is bigger.");
    else if (Area2 > Area1)
        printf("\nArea in double is bigger.");
    else printf("\nBoth area are equal.");

    return 0;
}
