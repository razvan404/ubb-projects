/*
26.  Se citeste de la tastatura un sir de numere in baza 10, cu semn. Sa se determine
valoarea minima din sir si sa se afiseze in fisierul min.txt (fisierul va fi creat) 
valoarea minima, in baza 16.
*/
#include <stdio.h>

int min(int n, int *s), n, s[256];

int main()
{
    printf("Introdu lungimea sirului: ");
    scanf("%d", &n);
    printf("Introdu sirul: ");
    
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &s[i]);
    }

    freopen("min.txt", "w", stdout);
    printf("Valoarea minima este: %X (%d in baza 10).", min(n, s), min(n, s));
    fclose(stdin);
    
    return 0;
}
