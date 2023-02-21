#include "matrix.h"
#include "operations.h"

matrix_t* init_matrix(unsigned rows, unsigned cols) {
    matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
    
    matrix->values = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; ++i)
        matrix->values[i] = (double*)malloc(cols * sizeof(double));

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

unsigned get_rows(matrix_t* matrix) {
    return matrix->rows;
}

unsigned get_cols(matrix_t* matrix) {
    return matrix->cols;
}

double get_matrix_value_at(matrix_t* matrix, unsigned row, unsigned col) {
    if (row < matrix->rows && col < matrix->cols) {
        return matrix->values[row][col];
    }
    errno = -1;
    return -1.0;
}

void set_matrix_value_at(matrix_t* matrix, unsigned row, unsigned col, double value){
    if (row < matrix->rows && col < matrix->cols) {
        matrix->values[row][col] = value;
    }
    errno = -1;
}

void get_minor_matrix(matrix_t* matrix, int row, int col, matrix_t* minor) {
    int k = 0;
    int n = get_rows(matrix);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != row && j != col) {
                set_matrix_value_at(minor, k / (n - 1), k % (n - 1), get_matrix_value_at(matrix, i, j));  
                ++k;
            }
        }
    }
}

double get_determinant(matrix_t* matrix) {
    if (get_rows(matrix) == 1) {
        return get_matrix_value_at(matrix, 0, 0);
    }
    double determinant = 0;
    int factor = 1;
    matrix_t* minor = init_matrix(get_rows(matrix) - 1, get_rows(matrix) - 1);
    for (int i = 0; i < get_rows(matrix); ++i) {
        get_minor_matrix(matrix, 0, i, minor);
        determinant += factor * get_matrix_value_at(matrix, 0, i) * get_determinant(minor);
        factor *= -1;
    }
    destroy_matrix(minor);
    return determinant;
}

matrix_t* transpose_matrix(matrix_t* matrix) {
    matrix_t* transpose = init_matrix(get_cols(matrix), get_rows(matrix));
    for (int i = 0; i < get_rows(matrix); ++i) {
        for (int j = 0; j < get_cols(matrix); ++j) {
            set_matrix_value_at(transpose, j, i, get_matrix_value_at(matrix, i, j));
        }
    }
    return transpose;
}

matrix_t* adjunct_matrix(matrix_t* matrix) {
    matrix_t* adjunct = init_matrix(get_rows(matrix), get_cols(matrix));
    matrix_t* minor = init_matrix(get_rows(matrix) - 1, get_cols(matrix) - 1);
    int factor1 = 1;
    for (int i = 0; i < get_rows(matrix); ++i) {
        factor1 *= -1;
        int factor2 = 1;
        for (int j = 0; j < get_cols(matrix); ++j) {
            factor2 *= -1;
            get_minor_matrix(matrix, i, j, minor);
            set_matrix_value_at(adjunct, i, j, factor1 * factor2 * get_determinant(minor));
        }
    }
    destroy_matrix(minor);
    return adjunct;
}

matrix_t* invert_matrix(matrix_t* matrix) {
    double det_matrix = get_determinant(matrix);
    if (det_matrix == 0) {
        errno = -6;
        return NULL;
    }
    matrix_t* transpose = transpose_matrix(matrix);
    matrix_t* adjunct = adjunct_matrix(transpose);
    scalar_t* factor = init_scalar(1.0 / det_matrix);
    matrix_t* inverse = scalar_multiply_matrix(factor, adjunct);

    destroy_matrix(transpose);
    destroy_matrix(adjunct);
    destroy_scalar(factor);

    return inverse;
}

void destroy_matrix(matrix_t* matrix){
    for (int i = 0; i < matrix->rows; ++i) {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}
