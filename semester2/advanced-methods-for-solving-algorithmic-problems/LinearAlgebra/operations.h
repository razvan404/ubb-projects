#pragma once
#include "scalar.h"
#include "vector.h"
#include "matrix.h"
#include "polynomial.h"
#include <errno.h>
#include <stdlib.h>

vector_p scalar_multiply_vector(scalar_p, vector_p);
vector_p add_vectors(vector_p, vector_p);
vector_p reverse_vector(vector_p);

scalar_p dot_product_vectors(vector_p, vector_p);
matrix_p scalar_multiply_matrix(scalar_p, matrix_p);
vector_p vector_multiply_matrix(vector_p, matrix_p);
matrix_p multiply_matrix(matrix_p, matrix_p);

scalar_p get_newton_zero_polynomial(polynomial_p, double, double, double);
matrix_p vandermonde_matrix(vector_p);
polynomial_p lagrange_interpolation(vector_p, vector_p);

matrix_p bezier_matrix(int);
complex_polynomial_p bezier_curve(vector_p, vector_p);

complex_polynomial_p fast_fourier_transform(complex_polynomial_p);

complex_p complex_unit_root(int, int);