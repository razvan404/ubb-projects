#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[256][256], n, m;
    printf("Give the numer of rows: ");
    scanf("%d", &n);
    printf("Give the number of columns: ");
    scanf("%d", &m);
    printf("Give the 2D array:\n");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &a[i][j]);
    printf("The transpose of the 2D array:\n");
    for (int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n; ++i)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
