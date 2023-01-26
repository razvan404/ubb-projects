#pragma once
#include <stdlib.h>
#include <errno.h>

typedef struct {
    int rows;
    int cols;
    double** values;
} matrix_t;

typedef matrix_t* matrix_p;

matrix_t* init_matrix(unsigned, unsigned);

unsigned get_rows(matrix_t*);
unsigned get_cols(matrix_t*);
double get_matrix_value_at(matrix_t*, unsigned, unsigned);
void set_matrix_value_at(matrix_t*, unsigned, unsigned, double);

double get_determinant(matrix_t*);
matrix_t* transpose_matrix(matrix_t*);
matrix_t* adjunct_matrix(matrix_t*);
matrix_t* invert_matrix(matrix_t*);



void destroy_matrix(matrix_t*);
