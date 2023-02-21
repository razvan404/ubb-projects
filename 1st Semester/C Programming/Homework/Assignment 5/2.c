#include <stdio.h>
#include <stdlib.h>

void replace_vowels(char *s)
{
    int i = 0;
    for (; i < strlen(s); ++i)
    {
        if (strchr("aeiouAEIOU", s[i]) != NULL)
            s[i] = '#';
    }
}

int main()
{
    char s[1024];
    if (freopen("file.txt", "r", stdin) == NULL)
    {
        printf("Nu s-a putut deschide fisierul!");
        exit(1);
    }
    gets(s);
    fclose(stdin);
    replace_vowels(s);
    freopen("file.txt", "w", stdout);
    printf("%s", s);
    fclose(stdout);
}
