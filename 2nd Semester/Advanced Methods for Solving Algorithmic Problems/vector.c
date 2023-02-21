#include "vector.h"
#include "utils.h"


vector_t* init_vector(unsigned size) {
    vector_t* vector = (vector_t*)malloc(sizeof(vector_t));

    vector->values = (double*)malloc(size * sizeof(double));
    vector->size = size;

    return vector;
}

unsigned get_size(vector_t* vector) {
    return vector->size;
}

double get_value_at(vector_t* vector, unsigned position) {
    if (0 <= position && position < get_size(vector)) {
        return vector->values[position];
    }
    errno = -1;
    return -1;
}

void set_value_at(vector_t* vector, unsigned position, double value) {
    if (0 <= position && position < get_size(vector)) {
        vector->values[position] = value;
    }
    errno = -1;
}

bool eq_size_vectors(vector_t* first, vector_t* second) {
    return first->size == second->size;
}

bool eq_vectors(vector_t* first, vector_t* second){
    if (!eq_size_vectors(first, second)) {
        return false;
    }

    for (int i = 0; i < get_size(first); ++i) {
        if (!eq_double(first->values[i], first->values[i])) {
            return false;
        }
    }
    return true;
}

void destroy_vector(vector_t* vector) {
    free(vector->values);
    free(vector);
}
