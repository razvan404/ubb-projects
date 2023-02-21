#include <stdio.h>
#include <stdlib.h>

void read(int **a, int n, int m)
{
    printf("Give the 2D array:\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", *(a + i) + j);
}

void print_transpose(int **a, int n, int m)
{
    for (int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n; ++i)
            printf("%d ", *(*(a + i) + j));
        printf("\n");
    }
}

int main()
{
    int n, m;
    printf("Give the numer of rows: ");
    scanf("%d", &n);
    printf("Give the number of columns: ");
    scanf("%d", &m);
    int **a = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i)
        a[i] = (int*)malloc(n * sizeof(int));
    read(a, n, m);
    printf("The transpose of the 2D array:\n");
    print_transpose(a, n, m);
}
