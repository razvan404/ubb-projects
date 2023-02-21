#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    double* values;
    unsigned size;
} vector_t;

typedef vector_t* vector_p;

vector_t* init_vector(unsigned);

unsigned get_size(vector_t*);

double get_value_at(vector_t*, unsigned);

void set_value_at(vector_t*, unsigned, double);

bool eq_size_vectors(vector_t*, vector_t*);

bool eq_vectors(vector_t*, vector_t*);

void destroy_vector(vector_t*);