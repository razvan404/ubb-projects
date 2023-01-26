#include "operations.h"
#include "trigonometry.h"

#include <math.h>

vector_p scalar_multiply_vector(scalar_p scalar, vector_p vector) {
    vector_p rez = init_vector(get_size(vector));
    for (int i = 0; i < get_size(rez); ++i) {
        set_value_at(rez, i, get_value_at(vector, i) * get_value(scalar));
    }

    return rez;
}

vector_p add_vectors(vector_p first, vector_p second) {
    if(!eq_size_vectors(first, second)) {
        errno = -2;
        return NULL;
    }

    vector_p rez = init_vector(get_size(first));
    for (int i = 0; i < get_size(rez); ++i) {
        set_value_at(rez, i, get_value_at(first, i) + get_value_at(second, i));
    }

    return rez;
}

vector_p reverse_vector(vector_p vector) {
    vector_p rez = init_vector(get_size(vector));
    for (int i = 0; i < get_size(rez); ++i) {
        set_value_at(rez, i, -get_value_at(vector, i));
    }

    return rez;
}

scalar_p dot_product_vectors(vector_p first, vector_p second) {
    if(!eq_size_vectors(first, second)) {
        errno = -2;
        return NULL;
    }

    double sum = 0;
    for (int i = 0; i < get_size(first); ++i) {
        sum += get_value_at(first, i) * get_value_at(second, i);
    }

    scalar_t* rez = init_scalar(sum);
    return rez;
}

matrix_p scalar_multiply_matrix(scalar_p scalar, matrix_p matrix) {
    matrix_p result = init_matrix(get_rows(matrix), get_cols(matrix));
    for (int i = 0; i < get_rows(matrix); ++i) {
        for (int j = 0; j < get_cols(matrix); ++j) {
            set_matrix_value_at(result, i, j, get_value(scalar) * get_matrix_value_at(matrix, i, j));
        }
    }
    return result;
}

vector_p vector_multiply_matrix(vector_p vector, matrix_p matrix) {
    if(get_size(vector) != get_cols(matrix)) {
        errno = -3;
        return NULL;
    }

    vector_p rez = init_vector(get_size(vector));
    for (int j = 0; j < get_size(rez); ++j) {
        double sum = 0;
        for (int i = 0; i < get_size(rez); ++i) {
            sum += get_matrix_value_at(matrix, i, j) * get_value_at(vector, i);
        }
        set_value_at(rez, j, sum);
    }

    return rez;
}

matrix_p multiply_matrix(matrix_p matrix1, matrix_p matrix2) {
    if (get_cols(matrix1) != get_rows(matrix2)) {
        errno = -3;
        return NULL;
    }

    matrix_p result = init_matrix(get_rows(matrix1), get_cols(matrix2));
    for (int i = 0; i < get_rows(matrix1); ++i) {
        for (int j = 0; j < get_cols(matrix2); ++j) {
            double current = 0;
            for (int k = 0; k < get_cols(matrix1); ++k) {
                current += get_matrix_value_at(matrix1, i, k) * get_matrix_value_at(matrix2, k, j);
                
            }
            set_matrix_value_at(result, i, j, current);
        }
    }
    return result;
}

scalar_p get_newton_zero_polynomial(polynomial_p polynomial, double a, double b, double epsilon) {
    double result = b;
    double polynomial_result = calculate_polynomial_value_at(polynomial, result);
    polynomial_p derivative = derivative_polynomial(polynomial);
    // x = x - P(x)/P'(x)
    while (polynomial_result > epsilon) {
        result -= polynomial_result / calculate_polynomial_value_at(derivative, result);
        polynomial_result = calculate_polynomial_value_at(polynomial, result);
    }
    destroy_polynomial(derivative);
    return init_scalar(result);
}

matrix_p vandermonde_matrix(vector_p vector) {
    int n = get_size(vector);
    matrix_p vandermonde = init_matrix(n, n);
    for (int i = 0; i < n; ++i) {
        int factor = 1;
        for (int j = n - 1; j > -1; --j) {
            set_matrix_value_at(vandermonde, i, j, factor);
            factor *= get_value_at(vector, i);
        }
    }
    return vandermonde;
}

polynomial_p lagrange_interpolation(vector_p x, vector_p y) {
    double* coefficients = (double*)malloc(get_size(x) * sizeof(double));

    matrix_p vandermonde = vandermonde_matrix(x);
    matrix_p inverse_vandermonde = invert_matrix(vandermonde);
    
    matrix_p y_matrix = init_matrix(get_size(y), 1);
    for (int i = 0; i < get_size(y); ++i) {
        set_matrix_value_at(y_matrix, i, 0, get_value_at(y, i));
    }
    
    matrix_p result = multiply_matrix(inverse_vandermonde, y_matrix);

    for (int i = 0; i < get_size(x); ++i) {
        coefficients[i] = get_matrix_value_at(result, get_size(x) - i - 1, 0);
    }

    polynomial_p lagrange_polynomial = init_polynomial(get_size(x) - 1, coefficients);

    free(coefficients);
    destroy_matrix(vandermonde);
    destroy_matrix(inverse_vandermonde);
    destroy_matrix(y_matrix);
    destroy_matrix(result);

    return lagrange_polynomial;
}

matrix_p bezier_matrix(int n)
{
    matrix_p mat = init_matrix(n, n);

    for (int line = 0; line < n; line++)
    {
        for (int col = 0; col < n; col++)
            set_matrix_value_at(mat, line, col, 0);

    }

    set_matrix_value_at(mat, n - 1, n - 1, 1);
    for (int line = n - 2; line >= 0; line--)
    {
        set_matrix_value_at(mat, line, n - 1, 1);
        set_matrix_value_at(mat, line, line, 1);
        for (int col = line + 1; col < n - 1; col++)
        {
            double v1 = get_matrix_value_at(mat, line + 1, col);
            double v2 = get_matrix_value_at(mat, line + 1, col + 1);
            set_matrix_value_at(mat, line, col, v1 + v2);
        }
    }

    for (int line = 0; line < n; line++)
    {
        for (int col = 0; col < n; col++)
        {
            double el = get_matrix_value_at(mat, line, col);
            el *= get_matrix_value_at(mat, 0, line);
                        
            set_matrix_value_at(mat, line, col, el);
        }
    }

    for (int line = 0; line < n; line++)
    {
        for (int col = 0; col < n; col++)
        {
            double el = get_matrix_value_at(mat, line, col);
            if (abs(line - col) % 2 == 1)
            {               
                el = -el;
            }
            set_matrix_value_at(mat, line, col, el);
        }
    }   
   
    /**
    1, -3, 3, -1    | 1
    0, 3, -6, 3    | 3
    0, 0, 3, -3,   | 3
    0, 0, 0,  1    | 1
    */
    return mat;
}

// mat*(p1|...|pn)
// TO DO : beautify code
complex_polynomial_p bezier_curve(vector_p x, vector_p y)
{
    int n = get_size(x);
    complex_p* coeff = (complex_p*)malloc(n * sizeof(complex_p));    

    matrix_p mat = bezier_matrix(n);   

    for (int row = 0; row < n; row++)
    {                        
        coeff[row] = init_complex(0, 0);        
        for (int col = 0; col < n; col++)
        {
            complex_p elemc = init_complex(get_matrix_value_at(mat, row, col), 0);
            complex_p point = init_complex(get_value_at(x, col), get_value_at(y, col));

            complex_p prod = complex_mul(elemc, point);
            complex_p res = complex_add(coeff[row], prod);

            destroy_complex(prod);
            destroy_complex(elemc);
            destroy_complex(point);
            destroy_complex(coeff[row]);
            coeff[row] = res;

        }
    }  

    complex_polynomial_p p = init_complex_polynomial(n, coeff);
    return p;
}

complex_p complex_unit_root(int n, int j){
    double theta = 2 * M_PI * j / n;
    double real = cosinus(theta, DEFAULT_EPSILON);
    double imag = sinus(theta, DEFAULT_EPSILON);
    return init_complex(real, imag);
}

complex_polynomial_p fast_fourier_transform(complex_polynomial_p p){
    int n = p->degree + 1;
    if(n == 1){
       return copy_complex_polynomial(p);
    }

    complex_p* coeffs_even = malloc(n/2 * sizeof(complex_p));
    complex_p* coeffs_odd = malloc(n/2 * sizeof(complex_p));

    int poz_even = 0, poz_odd = 0;
    for(int i = 0; i < n; ++i){
        if(i % 2 == 0){
            coeffs_even[poz_even++] = get_complex_coefficient_at(p, i);
        } else {
            coeffs_odd[poz_odd++] = get_complex_coefficient_at(p, i);
        }
    }

    complex_polynomial_p p_even = init_complex_polynomial(n/2 - 1, coeffs_even);
    complex_polynomial_p p_odd = init_complex_polynomial(n/2 - 1, coeffs_odd);

    complex_polynomial_p y_even = fast_fourier_transform(p_even);
    complex_polynomial_p y_odd = fast_fourier_transform(p_odd);

    complex_p* coeffs = (complex_p*) malloc(n * sizeof(complex_p));

    for(int j = 0; j < n/2; ++j){
        complex_p even_coeff = get_complex_coefficient_at(y_even, j);
        complex_p odd_coeff = get_complex_coefficient_at(y_odd, j);
        complex_p omega = complex_unit_root(n, j);
        complex_p product = complex_mul(omega, odd_coeff);
        complex_p sum = complex_add(even_coeff, product);
        complex_p diff = complex_sub(even_coeff, product);
        coeffs[j] = sum;
        coeffs[j + n/2] = diff;

        destroy_complex(omega);
        destroy_complex(product);
    }


    complex_polynomial_p result = init_complex_polynomial(n-1, coeffs);
    for(int i = 0; i < n; ++i){
        destroy_complex(coeffs[i]);
    }
    destroy_complex_polynomial(y_odd);
    destroy_complex_polynomial(y_even);
    destroy_complex_polynomial(p_even);
    destroy_complex_polynomial(p_odd);
    free(coeffs);
    free(coeffs_odd);
    free(coeffs_even);

    return result;
}
