#include <stdio.h>
#include <math.h>

int main()
{
    int d1, d2;
    int t = 1;
    while (t)
    {
        t = 0;
        printf("First diagonal: ");
        scanf("%d", &d1);
        if (d1 <= 0)
        {
            printf("Invalid value, try again\n");
            t = 1;
        }
    }
    t = 1;
    while (t)
    {
        t = 0;
        printf("Second diagonal: ");
        scanf("%d", &d2);
        if (d2 <= 0)
        {
            printf("Invalid value, try again\n");
            t = 1;
        }
    }
    float area = (d1 * 1.0 / 2) * d2, perimeter = 4 * sqrt((d1 / 2) * (d1 / 2) + (d2 / 2) * (d2 / 2));
    printf("Area of the diamond: %.1f\nPerimeter of the diamond: %f", area, perimeter);
    return 0;
}
