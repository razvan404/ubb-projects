#include <stdio.h>
#include <stdlib.h>


void read_matrix(int **mat, int n, int m)
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", &mat[i][j]);
}

void multiply_matrices(int **A, int **B, int N, int M, int P, int **C)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < P; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < M; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }

}

void print_matrix(int **mat, int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main()
{
    int N, M, P;
    printf("We multiply 2 matrix, A and B, A's dimensions are NxM and B's dimensions are MxP\n");
    printf("Give N: ");
    scanf("%d", &N);
    printf("Give M: ");
    scanf("%d", &M);
    printf("Give P: ");
    scanf("%d", &P);

    int **A = malloc(N * sizeof(int *));
    int **B = malloc(M * sizeof(int *));
    int **C = malloc(N * sizeof(int *));
    for (int i = 0; i < N; ++i)
        A[i] = malloc(M * sizeof(int));
    for (int i = 0; i < M; ++i)
        B[i] = malloc(P * sizeof(int));
    for (int i = 0; i < N; ++i)
        C[i] = malloc(P * sizeof(int));

    printf("Give matrix A:\n");
    read_matrix(A, N, M);
    printf("Give matrix B:\n");
    read_matrix(B, M, P);

    multiply_matrices(A, B, N, M, P, C);
    printf("The multiplication of the matrices:\n");
    print_matrix(C, N, P);
}
