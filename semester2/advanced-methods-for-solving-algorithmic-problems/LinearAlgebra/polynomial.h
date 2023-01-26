#pragma once
#include <errno.h>
#include <stdlib.h>
#include "complex.h"

typedef struct {
	double* coefficients;
	int degree;
} polynomial_t;

typedef polynomial_t* polynomial_p;

polynomial_t* init_polynomial(int, double*);

int get_degree(polynomial_t*);

double get_coefficient_at(polynomial_t*, int);

double calculate_polynomial_value_at(polynomial_t*, double);

polynomial_t* derivative_polynomial(polynomial_t*);

void destroy_polynomial(polynomial_t*);

typedef struct {
	complex_p* coefficients;
	int degree;
} complex_polynomial_t;

typedef complex_polynomial_t* complex_polynomial_p;

complex_polynomial_t* init_complex_polynomial(int, complex_p*);

complex_polynomial_p init_default_complex_polynomial(int);

complex_polynomial_p copy_complex_polynomial(complex_polynomial_p);

bool equal_complex_polynomial(complex_polynomial_p, complex_polynomial_p);

int get_complex_degree(complex_polynomial_t*);

complex_p get_complex_coefficient_at(complex_polynomial_t*, int);

complex_p calculate_complex_polynomial_value_at(complex_polynomial_t*, complex_p);

complex_p calculate_complex_polynomial_value_at_double(complex_polynomial_t*, double);

//complex_polynomial_t* derivative_polynomial(complex_polynomial_t*);

void destroy_complex_polynomial(complex_polynomial_t*);