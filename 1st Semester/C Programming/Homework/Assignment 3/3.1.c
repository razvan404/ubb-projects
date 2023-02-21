#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[256], copy[256];
int main()
{
    printf("Give a string: ");
    scanf("%s", &s);
    for (int i = strlen(s) - 1; i > -1; --i)
    {
        copy[strlen(s) - i - 1] = s[i];
    }
    printf("Reversed array: %s", copy);

}
