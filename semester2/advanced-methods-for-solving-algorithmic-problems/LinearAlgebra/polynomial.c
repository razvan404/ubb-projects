#include "polynomial.h"

polynomial_t* init_polynomial(int degree, double* coefficients) {
	if (degree < -1) {
		errno = -5;
		return NULL;
	}
	polynomial_t* p = (polynomial_t*)malloc(sizeof(polynomial_t));
	p->degree = degree;
	if (degree == -1) {
		p->degree = 0;
	}

	p->coefficients = (double*)malloc((p->degree + 1) * sizeof(double));
	for (int i = 0; i <= p->degree; ++i) {
		p->coefficients[i] = coefficients[i];
	}
	return p;
}

int get_degree(polynomial_t* polynomial) {
	return polynomial->degree;
}

double get_coefficient_at(polynomial_t* polynomial, int position) {
	if (position > polynomial->degree) {
		errno = -4;
		return 0.0;
	}
	return polynomial->coefficients[position];
}

double calculate_polynomial_value_at(polynomial_t* polynomial, double value) {
	double current_value = 1;
	double result = 0;
	for (int i = 0; i <= polynomial->degree; ++i) {
		result += current_value * polynomial->coefficients[i];
		current_value *= value;
	}
	return result;
}

polynomial_t* derivative_polynomial(polynomial_t* polynomial) {
	double* der_coefficients = (double*)malloc((polynomial->degree + 1) * sizeof(double));
	for (int i = 0; i < polynomial->degree; ++i) {
		der_coefficients[i] = (i + 1) * polynomial->coefficients[i + 1];
	}

	polynomial_t* der = init_polynomial(polynomial->degree - 1, der_coefficients);
	free(der_coefficients);
	return der;
}

void destroy_polynomial(polynomial_t* polynomial) {
	free(polynomial->coefficients);
	free(polynomial);
}

complex_polynomial_t* init_complex_polynomial(int degree, complex_p* coefficients)
{
	if (degree < -1) {
		errno = -5;
		return NULL;
	}
	complex_polynomial_t* p = (complex_polynomial_t*)malloc(sizeof(complex_polynomial_t));
	p->degree = degree;
	if (degree == -1) {
		p->degree = 0;
	}

	p->coefficients = (complex_p*)malloc((p->degree + 1) * sizeof(complex_p));
	for (int i = 0; i <= p->degree; ++i) {
		p->coefficients[i] = copy_complex(coefficients[i]);
	}
	return p;
}

complex_polynomial_p init_default_complex_polynomial(int degree){
    complex_p* coefficients = (complex_p*) malloc(sizeof(complex_p) * (degree + 1));
    complex_p zero = init_complex(0, 0);
    for(int i = 0; i <= degree; ++i){
        coefficients[i] = zero;
    }

    complex_polynomial_p result = init_complex_polynomial(degree, coefficients);
    destroy_complex(zero);
    free(coefficients);
    return result;
}

complex_polynomial_p copy_complex_polynomial(complex_polynomial_p original){
    return init_complex_polynomial(original->degree, original->coefficients);
}

bool equal_complex_polynomial(complex_polynomial_p l, complex_polynomial_p r){
   if(l->degree == r->degree){
       for(int i = 0; i < l->degree; ++i){
           if(!equal_complex(l->coefficients[i], r->coefficients[i])){
               return false;
           }
       }
       return true;
   }
   return false;
}

int get_complex_degree(complex_polynomial_t* p)
{
	return p->degree;
}

complex_p get_complex_coefficient_at(complex_polynomial_t* p, int i)
{
	if (i < 0 || i > p->degree)
	{
		errno = -11;
		return NULL;
	}
	return p->coefficients[i];
}

complex_p calculate_complex_polynomial_value_at(complex_polynomial_t* p, complex_p t)
{
	// c0*t^0 + c1*t^1 +...
	complex_p result = init_complex(0, 0);
	complex_p var = init_complex(1, 0); // t^i
    complex_p tmp;
	for (int i = 0; i <= get_complex_degree(p); i++)
	{
		complex_p coef = get_complex_coefficient_at(p, i);
		complex_p prod = complex_mul(coef, var);
	    tmp = complex_add(result, prod);
        destroy_complex(result);
        result = tmp;

		tmp = complex_mul(var, t);
        destroy_complex(var);
        var = tmp;

		destroy_complex(prod);
	}
    free(var);
	return result;
}

complex_p calculate_complex_polynomial_value_at_double(complex_polynomial_t* p, double t)
{
	complex_p z = init_complex(t, 0);
	complex_p result = calculate_complex_polynomial_value_at(p, z);
	destroy_complex(z);
	return result;
}

//complex_polynomial_t* derivative_polynomial(complex_polynomial_t*);

void destroy_complex_polynomial(complex_polynomial_t* polynomial)
{
	for (int i = 0; i <= get_complex_degree(polynomial); i++)
		destroy_complex(polynomial->coefficients[i]);
	free(polynomial->coefficients);
	free(polynomial);
}