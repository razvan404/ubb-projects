#include "scalar.h"

scalar_t* init_scalar(double value) {
    scalar_t* scalar = (scalar_t*)malloc(sizeof(scalar_t));

    scalar->value = value;

    return scalar;
}

double get_value(scalar_t* scalar) {
    return scalar->value;
}

void destroy_scalar(scalar_t* scalar) {
    free(scalar);
}