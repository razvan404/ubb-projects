#include <stdio.h>


int main()
{
    int h, m, x, y, newh, newm;
    int t = 0;
    while (!t)
    {
        t = 1;
        printf("Hour: ");
        scanf("%d", &h);
        if (h > 23 || h < 0)
        {
            printf("Invalid hour, try again\n");
            t = 0;
        }
    }
    t = 0;
    while (!t)
    {
        t = 1;
        printf("Minutes: ");
        scanf("%d", &m);
        if (m > 60 || m < 0)
        {
            printf("Invalid minutes, try again\n");
            t = 0;
        }
    }
    printf("Passed hours: ");
    scanf("%d", &x);
    printf("Passed minutes: ");
    scanf("%d", &y);

    newm = (m + y) % 60;
    newh = (h + x + (m + y) / 60) % 24;

    printf("Current time: [%d:%d]", newh, newm);
    return 0;
}
