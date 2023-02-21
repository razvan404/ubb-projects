#include <stdio.h>
#include <stdlib.h>

int main()
{
    float c;
    printf("Value in centimeters: ");
    scanf("%f", &c);
    int f = c / 2.54;
    int aux = ((c / 2.54) / 12) * 10;
    float i = aux * 1.0 / 10;
    printf("Value in feet: %d\nValue in inches: %.1f", f, i);
    return 0;
}
