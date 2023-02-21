#include "utils.h"

bool eq_double(double a, double b){
    return fabs(a - b) <= DEFAULT_EPSILON;
}