#include <stdio.h>
#include <stdlib.h>

void replace_even(char *s)
{
    int i = 0;
    for (; i < strlen(s); ++i)
    {
        if (strchr("0123456789", s[i]) == NULL)
            return;
    }
    if (strchr("02468", s[strlen(s) - 1]) == NULL)
        return;
    strcpy(s, "|");
}

char s[64], text[1024], *p;

int main()
{

    if (freopen("file.txt", "r", stdin) == NULL)
    {
        printf("Nu s-a putut deschide fisierul!");
        exit(1);
    }
    while (fgets(s, sizeof(s), stdin))
    {
        p = strtok(s, " ");
        while (p)
        {
            replace_even(p);
            strcat(text, p);
            strcat(text, " ");
            p = strtok(NULL, " ");
        }
    }
    fclose(stdin);
    freopen("file.txt", "w", stdout);
    printf("%s", text);
    fclose(stdout);
}
