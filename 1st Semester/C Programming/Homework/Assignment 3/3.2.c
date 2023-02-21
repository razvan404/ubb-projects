#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char reverse(char *s)
{
    char copy[256];
    for (int i = 0; i < strlen(s); ++i)
        *(copy + i) = *(s + strlen(s) - i - 1);
    strcpy(s, copy);
}

int main()
{
    char s[256];
    printf("Give a string: ");
    scanf("%s", &s);
    reverse(s);
    printf("The reversed string: %s", s);
}
