#include "utils.h"
#include "tests.h"
#include "scalar.h"
#include "vector.h"
#include "matrix.h"
#include "operations.h"
#include "polynomial.h"
#include "trigonometry.h"
#include "complex.h"

#define number_of_tests 9

void run_scalar_tests();
void run_vector_tests();
void run_matrix_tests();
void run_operations_tests();
void run_polynomial_tests();
void run_trigonometry_tests();
void run_complex_tests(); 
void run_complex_polynomial_tests();
void run_fast_fourier_transform_tests();


void run_all_tests() {
    printf("| Running all tests\n");

    printf("|  Running 'scalar tests'. Result: ");
    run_scalar_tests();
    printf(" [%d%c]\n", (int)(1.0 * 100 / number_of_tests), '%');

    printf("|  Running 'vector tests'. Result: ");
    run_vector_tests();
    printf(" [%d%c]\n", (int)(2.0 * 100 / number_of_tests), '%');

    printf("|  Running 'matrix tests'. Result: ");
    run_matrix_tests();
    printf(" [%d%c]\n", (int)(3.0 * 100 / number_of_tests), '%');

    printf("|  Running 'operations tests'. Result: ");
    run_operations_tests();
    printf(" [%d%c]\n", (int)(4.0 * 100 / number_of_tests), '%');

    printf("|  Running 'polynomial tests'. Result: ");
    run_polynomial_tests();
    printf(" [%d%c]\n", (int)(5.0 * 100 / number_of_tests), '%');

    printf("|  Running 'trigonometry tests'. Result: ");
    run_trigonometry_tests();
    printf(" [%d%c]\n", (int)(6.0 * 100 / number_of_tests), '%');

    printf("|  Running 'complex tests'. Result: ");
    run_complex_tests();
    printf(" [%d%c]\n", (int)(7.0 * 100 / number_of_tests), '%');

    printf("|  Running 'complex polynomial tests'. Result: ");
    run_complex_polynomial_tests();
    printf(" [%d%c]\n", (int)(8.0 * 100 / number_of_tests), '%');

    printf("|  Running 'FFT tests'. Result: ");
    run_fast_fourier_transform_tests();
    printf(" [%d%c]\n", (int)(9.0 * 100 / number_of_tests), '%');

    printf("| All tests ran successfully!\n");
}

void run_scalar_tests() {
    double value = 1.2;
    scalar_p scalar = init_scalar(value);
    assert(eq_double(value, get_value(scalar)));
    destroy_scalar(scalar);
    printf("PASSED");
}
void run_vector_tests() {
    vector_p vector = init_vector(3);
    assert(get_size(vector) == 3);
    set_value_at(vector, 0, 0.0);
    set_value_at(vector, 1, 1.0);
    set_value_at(vector, 2, 2.0);

    assert(eq_double(get_value_at(vector, 0), 0.0));
    assert(eq_double(get_value_at(vector, 1), 1.0));
    assert(eq_double(get_value_at(vector, 2), 2.0));

    get_value_at(vector, 3);
    assert(errno==-1);
    errno = 0;

    set_value_at(vector, 4, 0.5);
    assert(errno==-1);
    errno = 0;
    destroy_vector(vector);

    printf("PASSED");
}
void run_matrix_tests(){
    matrix_t* matrix = init_matrix(2, 2);
    assert(get_rows(matrix)==2);
    assert(get_cols(matrix)==2);
    set_matrix_value_at(matrix, 0, 0, 3.0);
    assert(eq_double(get_matrix_value_at(matrix, 0, 0), 3));
    get_matrix_value_at(matrix, 3, 3);
    assert(errno==-1);
    errno = 0;
    set_matrix_value_at(matrix, 4, 3, 0.7);
    assert(errno==-1);
    errno = 0;

    matrix_t* det_matrix = init_matrix(3, 3);
    set_matrix_value_at(det_matrix, 0, 0, -5); set_matrix_value_at(det_matrix, 0, 1, 0); set_matrix_value_at(det_matrix, 0, 2, 1);
    set_matrix_value_at(det_matrix, 1, 0, 0); set_matrix_value_at(det_matrix, 1, 1, 3); set_matrix_value_at(det_matrix, 1, 2, -1);
    set_matrix_value_at(det_matrix, 2, 0, 4); set_matrix_value_at(det_matrix, 2, 1, 1); set_matrix_value_at(det_matrix, 2, 2, 0);
    assert(eq_double(get_determinant(det_matrix), -17));

    matrix_t* det_matrix_4 = init_matrix(4, 4);
    set_matrix_value_at(det_matrix_4, 0, 0, 1); set_matrix_value_at(det_matrix_4, 0, 1, 2); set_matrix_value_at(det_matrix_4, 0, 2, 3); set_matrix_value_at(det_matrix_4, 0, 3, 4);
    set_matrix_value_at(det_matrix_4, 1, 0, 5); set_matrix_value_at(det_matrix_4, 1, 1, 6); set_matrix_value_at(det_matrix_4, 1, 2, 7); set_matrix_value_at(det_matrix_4, 1, 3, 8);
    set_matrix_value_at(det_matrix_4, 2, 0, -8); set_matrix_value_at(det_matrix_4, 2, 1, -7); set_matrix_value_at(det_matrix_4, 2, 2, -6); set_matrix_value_at(det_matrix_4, 2, 3, -5);
    set_matrix_value_at(det_matrix_4, 3, 0, -1); set_matrix_value_at(det_matrix_4, 3, 1, -2); set_matrix_value_at(det_matrix_4, 3, 2, -3); set_matrix_value_at(det_matrix_4, 3, 3, -4);
    assert(eq_double(get_determinant(det_matrix_4), 0));


    destroy_matrix(matrix);
    destroy_matrix(det_matrix);
    destroy_matrix(det_matrix_4);

    matrix_t* normal_matrix = init_matrix(2, 3);
    set_matrix_value_at(normal_matrix, 0, 0, 1.1); set_matrix_value_at(normal_matrix, 0, 1, 1.2); set_matrix_value_at(normal_matrix, 0, 2, 1.3);
    set_matrix_value_at(normal_matrix, 1, 0, 2.1); set_matrix_value_at(normal_matrix, 1, 1, 2.2); set_matrix_value_at(normal_matrix, 1, 2, 2.3);
    matrix_t* transp_matrix = transpose_matrix(normal_matrix);
    assert(get_rows(transp_matrix) == 3);
    assert(get_cols(transp_matrix) == 2);
    assert(eq_double(get_matrix_value_at(transp_matrix, 0, 0), 1.1)); assert(eq_double(get_matrix_value_at(transp_matrix, 0, 1), 2.1));
    assert(eq_double(get_matrix_value_at(transp_matrix, 1, 0), 1.2)); assert(eq_double(get_matrix_value_at(transp_matrix, 1, 1), 2.2));
    assert(eq_double(get_matrix_value_at(transp_matrix, 2, 0), 1.3)); assert(eq_double(get_matrix_value_at(transp_matrix, 2, 1), 2.3));

    destroy_matrix(normal_matrix);
    destroy_matrix(transp_matrix);

    printf("PASSED");
}
void run_operations_tests(){
    scalar_p scalar = init_scalar(7);
    vector_p vector = init_vector(2);
    set_value_at(vector, 0, 3);
    set_value_at(vector, 1, 4);

    vector_p s_vector = scalar_multiply_vector(scalar, vector);
    assert(eq_size_vectors(s_vector, vector) == true);
    assert(eq_double(get_value_at(s_vector, 0), 21));
    assert(eq_double(get_value_at(s_vector, 1), 28));
    
    vector_p sum_vector = add_vectors(vector, s_vector);
    assert(eq_size_vectors(sum_vector, vector) == true);
    assert(eq_double(get_value_at(sum_vector, 0), 24));
    assert(eq_double(get_value_at(sum_vector, 1), 32));
    destroy_vector(sum_vector);
    
    vector_p d3_vector = init_vector(3);
    sum_vector = add_vectors(vector, d3_vector);
    assert(errno==-2);
    assert(sum_vector==NULL);
    errno=0;
    
    vector_p rev_vector = reverse_vector(vector);
    sum_vector = add_vectors(rev_vector, vector);
    assert(eq_double(get_value_at(sum_vector, 0), 0));
    assert(eq_double(get_value_at(sum_vector, 1), 0));
    destroy_vector(sum_vector);
    
    destroy_scalar(scalar);
    scalar = dot_product_vectors(vector, rev_vector);
    assert(eq_double(get_value(scalar), -25));
    
    matrix_p rot_matrix = init_matrix(2, 2);
    set_matrix_value_at(rot_matrix, 0, 0, 0);
    set_matrix_value_at(rot_matrix, 0, 1, 1);
    set_matrix_value_at(rot_matrix, 1, 0, -1);
    set_matrix_value_at(rot_matrix, 1, 1, 0);

    scalar_p mul_scalar = init_scalar(0.1);
    matrix_p mul_matrix = init_matrix(2, 3);
    set_matrix_value_at(mul_matrix, 0, 0, 1.1); set_matrix_value_at(mul_matrix, 0, 1, 1.2); set_matrix_value_at(mul_matrix, 0, 2, 1.3);
    set_matrix_value_at(mul_matrix, 1, 0, 2.1); set_matrix_value_at(mul_matrix, 1, 1, 2.2); set_matrix_value_at(mul_matrix, 1, 2, 2.3);
    matrix_p multiplied_matrix = scalar_multiply_matrix(mul_scalar, mul_matrix);
    assert(eq_double(get_matrix_value_at(multiplied_matrix, 0, 0), 0.11));
    assert(eq_double(get_matrix_value_at(multiplied_matrix, 0, 1), 0.12));
    assert(eq_double(get_matrix_value_at(multiplied_matrix, 0, 2), 0.13));
    assert(eq_double(get_matrix_value_at(multiplied_matrix, 1, 0), 0.21));
    assert(eq_double(get_matrix_value_at(multiplied_matrix, 1, 1), 0.22));
    assert(eq_double(get_matrix_value_at(multiplied_matrix, 1, 2), 0.23));
    destroy_scalar(mul_scalar);
    destroy_matrix(mul_matrix);
    destroy_matrix(multiplied_matrix);

    matrix_p adj_input_matrix = init_matrix(3, 3);
    set_matrix_value_at(adj_input_matrix, 0, 0, 1); set_matrix_value_at(adj_input_matrix, 0, 1, 2); set_matrix_value_at(adj_input_matrix, 0, 2, 1);
    set_matrix_value_at(adj_input_matrix, 1, 0, -1); set_matrix_value_at(adj_input_matrix, 1, 1, 0); set_matrix_value_at(adj_input_matrix, 1, 2, 1);
    set_matrix_value_at(adj_input_matrix, 2, 0, 1); set_matrix_value_at(adj_input_matrix, 2, 1, 3); set_matrix_value_at(adj_input_matrix, 2, 2, -2);

    matrix_p adj_output_matrix = adjunct_matrix(adj_input_matrix);
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 0, 0), -3));
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 0, 1), -1));
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 0, 2), -3));

    assert(eq_double(get_matrix_value_at(adj_output_matrix, 1, 0), 7));
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 1, 1), -3));
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 1, 2), -1));

    assert(eq_double(get_matrix_value_at(adj_output_matrix, 2, 0), 2));
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 2, 1), -2));
    assert(eq_double(get_matrix_value_at(adj_output_matrix, 2, 2), 2));

    destroy_matrix(adj_input_matrix);
    destroy_matrix(adj_output_matrix);

    matrix_p inv_input_matrix = init_matrix(3, 3);
    set_matrix_value_at(inv_input_matrix, 0, 0, 1); set_matrix_value_at(inv_input_matrix, 0, 1, 2); set_matrix_value_at(inv_input_matrix, 0, 2, 3);
    set_matrix_value_at(inv_input_matrix, 1, 0, -1); set_matrix_value_at(inv_input_matrix, 1, 1, 0); set_matrix_value_at(inv_input_matrix, 1, 2, -1);
    set_matrix_value_at(inv_input_matrix, 2, 0, 3); set_matrix_value_at(inv_input_matrix, 2, 1, 4); set_matrix_value_at(inv_input_matrix, 2, 2, 7);

    matrix_p bad_inv_output_matrix = invert_matrix(inv_input_matrix);
    assert(bad_inv_output_matrix == NULL);
    assert(errno == -6);
    errno = 0;

    set_matrix_value_at(inv_input_matrix, 0, 0, 1); set_matrix_value_at(inv_input_matrix, 0, 1, -1); set_matrix_value_at(inv_input_matrix, 0, 2, 1);
    set_matrix_value_at(inv_input_matrix, 1, 0, 2); set_matrix_value_at(inv_input_matrix, 1, 1, 0); set_matrix_value_at(inv_input_matrix, 1, 2, 3);
    set_matrix_value_at(inv_input_matrix, 2, 0, 1); set_matrix_value_at(inv_input_matrix, 2, 1, 1); set_matrix_value_at(inv_input_matrix, 2, 2, -2);

    matrix_p inv_output_matrix = invert_matrix(inv_input_matrix);
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 0, 0), 0.375));
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 0, 1), 0.125));
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 0, 2), 0.375));

    assert(eq_double(get_matrix_value_at(inv_output_matrix, 1, 0), -0.875));
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 1, 1), 0.375));
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 1, 2), 0.125));

    assert(eq_double(get_matrix_value_at(inv_output_matrix, 2, 0), -0.25));
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 2, 1), 0.25));
    assert(eq_double(get_matrix_value_at(inv_output_matrix, 2, 2), -0.25));

    destroy_matrix(inv_input_matrix);
    destroy_matrix(inv_output_matrix);

    vector_p prod_vector = vector_multiply_matrix(vector, rot_matrix);
    assert(get_size(vector) == get_cols(rot_matrix));
    assert(eq_double(get_value_at(prod_vector, 0), -4));
    assert(eq_double(get_value_at(prod_vector, 1), 3));
    destroy_vector(prod_vector);
   
    prod_vector = vector_multiply_matrix(d3_vector, rot_matrix);
    assert(errno==-3);
    assert(prod_vector==NULL);
    errno = 0;
    
    destroy_scalar(scalar);
    destroy_vector(vector);
    destroy_vector(s_vector);
    destroy_vector(d3_vector);
    destroy_vector(rev_vector);
    destroy_matrix(rot_matrix);
    
    
    matrix_p prod_matrix1 = init_matrix(1, 3);
    set_matrix_value_at(prod_matrix1, 0, 0, 3);
    set_matrix_value_at(prod_matrix1, 0, 1, 4);
    set_matrix_value_at(prod_matrix1, 0, 2, 2);

    matrix_p prod_matrix2 = init_matrix(3, 4);
    set_matrix_value_at(prod_matrix2, 0, 0, 13);
    set_matrix_value_at(prod_matrix2, 0, 1, 9);
    set_matrix_value_at(prod_matrix2, 0, 2, 7);
    set_matrix_value_at(prod_matrix2, 0, 3, 15);
    set_matrix_value_at(prod_matrix2, 1, 0, 8);
    set_matrix_value_at(prod_matrix2, 1, 1, 7);
    set_matrix_value_at(prod_matrix2, 1, 2, 4);
    set_matrix_value_at(prod_matrix2, 1, 3, 6);
    set_matrix_value_at(prod_matrix2, 2, 0, 6);
    set_matrix_value_at(prod_matrix2, 2, 1, 4);
    set_matrix_value_at(prod_matrix2, 2, 2, 0);
    set_matrix_value_at(prod_matrix2, 2, 3, 3);
    matrix_p prod_matrix_fail = init_matrix(4, 4);

    matrix_p rez_prod_matrix = multiply_matrix(prod_matrix1, prod_matrix_fail);
    assert(errno == -3);
    assert(rez_prod_matrix == NULL);
    errno = 0;
    
    rez_prod_matrix = multiply_matrix(prod_matrix1, prod_matrix2);
    assert(get_matrix_value_at(rez_prod_matrix, 0, 0) == 83);
    assert(get_matrix_value_at(rez_prod_matrix, 0, 1) == 63);
    assert(get_matrix_value_at(rez_prod_matrix, 0, 2) == 37);
    assert(get_matrix_value_at(rez_prod_matrix, 0, 3) == 75);
    
    destroy_matrix(prod_matrix1);
    destroy_matrix(prod_matrix2);
    destroy_matrix(prod_matrix_fail);
    destroy_matrix(rez_prod_matrix);


    double* coefficients = (double*)malloc(4 * sizeof(double));
    coefficients[0] = -7; coefficients[1] = 5;
    coefficients[2] = 2; coefficients[3] = 3;
    polynomial_p polynomial = init_polynomial(3, coefficients);
    free(coefficients);

    scalar_p temp = get_newton_zero_polynomial(polynomial, 0.5, 2, 10e-5);
    assert(eq_double(get_value(temp), 0.813067));

    destroy_scalar(temp);
    destroy_polynomial(polynomial);

    vector_p vector_vand = init_vector(4);
    set_value_at(vector_vand, 0, -2);
    set_value_at(vector_vand, 1, -1);
    set_value_at(vector_vand, 2, 1);
    set_value_at(vector_vand, 3, 2);
    // -8 4 -2 1
    // -1 1 -1 1
    // 1 1 1 1
    // 8 4 2 1
    matrix_p matrix_vand = vandermonde_matrix(vector_vand);
    assert(eq_double(get_matrix_value_at(matrix_vand, 0, 0), -8));
    assert(eq_double(get_matrix_value_at(matrix_vand, 0, 1), 4));
    assert(eq_double(get_matrix_value_at(matrix_vand, 0, 2), -2));
    assert(eq_double(get_matrix_value_at(matrix_vand, 0, 3), 1));

    assert(eq_double(get_matrix_value_at(matrix_vand, 1, 0), -1));
    assert(eq_double(get_matrix_value_at(matrix_vand, 1, 1), 1));
    assert(eq_double(get_matrix_value_at(matrix_vand, 1, 2), -1));
    assert(eq_double(get_matrix_value_at(matrix_vand, 1, 3), 1));

    assert(eq_double(get_matrix_value_at(matrix_vand, 2, 0), 1));
    assert(eq_double(get_matrix_value_at(matrix_vand, 2, 1), 1));
    assert(eq_double(get_matrix_value_at(matrix_vand, 2, 2), 1));
    assert(eq_double(get_matrix_value_at(matrix_vand, 2, 3), 1));

    assert(eq_double(get_matrix_value_at(matrix_vand, 3, 0), 8));
    assert(eq_double(get_matrix_value_at(matrix_vand, 3, 1), 4));
    assert(eq_double(get_matrix_value_at(matrix_vand, 3, 2), 2));
    assert(eq_double(get_matrix_value_at(matrix_vand, 3, 3), 1));

    destroy_vector(vector_vand);
    destroy_matrix(matrix_vand);

    vector_p lagrange_x = init_vector(3);
    vector_p lagrange_y = init_vector(3);
    set_value_at(lagrange_x, 0, 1); set_value_at(lagrange_x, 1, 2); set_value_at(lagrange_x, 2, 3);
    set_value_at(lagrange_y, 0, 1); set_value_at(lagrange_y, 1, 8); set_value_at(lagrange_y, 2, 27);
    polynomial_p lagrange_polynomial = lagrange_interpolation(lagrange_x, lagrange_y);

    assert(get_degree(lagrange_polynomial) == 2);
   
    assert(eq_double(get_coefficient_at(lagrange_polynomial, 0), 6));
    assert(eq_double(get_coefficient_at(lagrange_polynomial, 1), -11));
    assert(eq_double(get_coefficient_at(lagrange_polynomial, 2), 6));

    destroy_vector(lagrange_x);
    destroy_vector(lagrange_y);
    destroy_polynomial(lagrange_polynomial);
  
    printf("PASSED");
}
void run_polynomial_tests() {
    double* coefficients = (double*)malloc(5 * sizeof(double));
    coefficients[0] = 1; coefficients[1] = 2; coefficients[2] = 3;
    coefficients[3] = 4; coefficients[4] = 5;
    polynomial_p polynomial = init_polynomial(4, coefficients);

    assert(get_degree(polynomial) == 4);
    assert(eq_double(get_coefficient_at(polynomial, 0), 1));
    assert(eq_double(get_coefficient_at(polynomial, 1), 2));
    assert(eq_double(get_coefficient_at(polynomial, 2), 3));
    assert(eq_double(get_coefficient_at(polynomial, 3), 4));
    assert(eq_double(get_coefficient_at(polynomial, 4), 5));
    assert(eq_double(get_coefficient_at(polynomial, 5), 0));
    assert(errno == -4);
    errno = 0;

    polynomial_p derivative = derivative_polynomial(polynomial);
    // (5x^4 + 4x^3 + 3x^2 + 2x^1 + 1)' = 20x^3 + 12x^2 + 6x^1 + 2
    assert(get_degree(derivative) == 3);
    assert(eq_double(get_coefficient_at(derivative, 0), 2));
    assert(eq_double(get_coefficient_at(derivative, 1), 6));
    assert(eq_double(get_coefficient_at(derivative, 2), 12));
    assert(eq_double(get_coefficient_at(derivative, 3), 20));

    // 5 - 4 + 3 - 2 + 1 = 3 
    assert(eq_double(calculate_polynomial_value_at(polynomial, -1), 3.0));
    // 5 + 4 + 3 + 2 + 1 = 15
    assert(eq_double(calculate_polynomial_value_at(polynomial, 1), 15.0));
    // 0.3125 + 0.5 + 0.75 + 1 + 1 = 3.5625
    assert(eq_double(calculate_polynomial_value_at(polynomial, 0.5), 3.5625));
    // 0.3125 - 0.5 + 0.75 - 1 + 1 = 
    assert(eq_double(calculate_polynomial_value_at(polynomial, -0.5), 0.5625));

    polynomial_p bad_polynomial = init_polynomial(-2, coefficients);
    assert(bad_polynomial == NULL);
    assert(errno == -5);
    errno = 0;

    coefficients[0] = 0;
    polynomial_p zero_polynomial = init_polynomial(-1, coefficients);
    assert(get_degree(zero_polynomial) == 0);
    assert(eq_double(get_coefficient_at(zero_polynomial, 0), 0));

    destroy_polynomial(polynomial);
    destroy_polynomial(derivative);
    destroy_polynomial(zero_polynomial);

    int n = 3;
    matrix_p mat = bezier_matrix(n);
    assert(eq_double(get_matrix_value_at(mat, 0, 0), 1));
    assert(eq_double(get_matrix_value_at(mat, 0, 1), -2));
    assert(eq_double(get_matrix_value_at(mat, 0, 2), 1));

    assert(eq_double(get_matrix_value_at(mat, 1, 0), 0));
    assert(eq_double(get_matrix_value_at(mat, 1, 1), 2));
    assert(eq_double(get_matrix_value_at(mat, 1, 2), -2));

    assert(eq_double(get_matrix_value_at(mat, 2, 0), 0));
    assert(eq_double(get_matrix_value_at(mat, 2, 1), 0));
    assert(eq_double(get_matrix_value_at(mat, 2, 2), 1));

    destroy_matrix(mat);

    n = 4;
    mat = bezier_matrix(n);
    assert(eq_double(get_matrix_value_at(mat, 0, 0), 1));
    assert(eq_double(get_matrix_value_at(mat, 0, 1), -3));
    assert(eq_double(get_matrix_value_at(mat, 0, 2), 3));
    assert(eq_double(get_matrix_value_at(mat, 0, 3), -1));

    assert(eq_double(get_matrix_value_at(mat, 1, 0), 0));
    assert(eq_double(get_matrix_value_at(mat, 1, 1), 3));
    assert(eq_double(get_matrix_value_at(mat, 1, 2), -6));
    assert(eq_double(get_matrix_value_at(mat, 1, 3), 3));

    assert(eq_double(get_matrix_value_at(mat, 2, 0), 0));
    assert(eq_double(get_matrix_value_at(mat, 2, 1), 0));
    assert(eq_double(get_matrix_value_at(mat, 2, 2), 3));
    assert(eq_double(get_matrix_value_at(mat, 2, 3), -3));

    assert(eq_double(get_matrix_value_at(mat, 3, 0), 0));
    assert(eq_double(get_matrix_value_at(mat, 3, 1), 0));
    assert(eq_double(get_matrix_value_at(mat, 3, 2), 0));
    assert(eq_double(get_matrix_value_at(mat, 3, 3), 1));

    destroy_matrix(mat);
    free(coefficients);
    printf("PASSED");
}

void run_complex_tests()
{
    complex_p z = init_complex(4, 5);
    assert(eq_double(get_complex_re(z), 4));
    assert(eq_double(get_complex_im(z), 5));

    complex_p zz = copy_complex(z);
    assert(equal_complex(z, zz));
    destroy_complex(zz);

    complex_p z1, z2, r;
    z1 = init_complex(10, 5);
    z2 = init_complex(4, 2);

    r = complex_add(z1, z2);
    assert(eq_double(get_complex_re(r), 14));
    assert(eq_double(get_complex_im(r), 7));

    free(r);
    r = complex_sub(z1, z2);
    assert(eq_double(get_complex_re(r), 6));
    assert(eq_double(get_complex_im(r), 3));

    free(r);
    r = complex_mul(z1, z2);
    assert(eq_double(get_complex_re(r), 30));
    assert(eq_double(get_complex_im(r), 40));

    int n = 8, j = 4;
    complex_p root =  complex_unit_root(n, j);
    complex_p result = init_complex(-1, 0);
    assert(equal_complex(root, result));
    destroy_complex(root);
    destroy_complex(result);

   
    destroy_complex(z);
    destroy_complex(z1);
    destroy_complex(z2);
    destroy_complex(r);

    printf("PASSED");
}

void run_complex_polynomial_tests()
{
    int n = 3;

    complex_polynomial_p cpy = init_default_complex_polynomial(n);
    assert(get_complex_degree(cpy) == n);
    complex_p zero = init_complex(0, 0);
    for(int i = 0; i <= n; ++i){
        assert(equal_complex(get_complex_coefficient_at(cpy, i), zero));
    }
    destroy_complex(zero);
    destroy_complex_polynomial(cpy);

    complex_p* coeffs = (complex_p*)malloc(n * sizeof(complex_p));
    if (coeffs)
    {
        coeffs[0] = init_complex(2, 3);
        coeffs[1] = init_complex(0, 1);
        coeffs[2] = init_complex(1, 0);

        complex_polynomial_p p = init_complex_polynomial(2, coeffs);
        complex_polynomial_p cpy = copy_complex_polynomial(p);

        assert(equal_complex_polynomial(p, cpy));
        destroy_complex_polynomial(cpy);

        assert(get_complex_degree(p) == 2);

        complex_p z;
        z = get_complex_coefficient_at(p, 0);
        assert(eq_double(get_complex_re(z),2) && eq_double(get_complex_im(z), 3));
        z = get_complex_coefficient_at(p, 1);
        assert(eq_double(get_complex_re(z), 0) && eq_double(get_complex_im(z), 1));
        z = get_complex_coefficient_at(p, 2);
        assert(eq_double(get_complex_re(z), 1) && eq_double(get_complex_im(z), 0));

        z = init_complex(1, 0);
        complex_p result = calculate_complex_polynomial_value_at(p, z);
        printf("%f %f", result->x, result->y);
        assert(eq_double(get_complex_re(result), 3));
        assert(eq_double(get_complex_im(result), 4));


        destroy_complex_polynomial(p);
        destroy_complex(z);
        destroy_complex(result);
        destroy_complex(coeffs[0]);
        destroy_complex(coeffs[1]);
        destroy_complex(coeffs[2]);
    }
    free(coeffs);

    printf("PASSED");
}

void run_trigonometry_tests() {
    assert(eq_double(sinus(M_PI_2, 10e-7), 1));
    assert(eq_double(cosinus(0, 0.001), 1));

    printf("PASSED");
}

void run_fast_fourier_transform_tests(){
    int degree = 3;
    complex_p* coeffs = malloc((degree + 1) * sizeof(complex_p));
    coeffs[0] = init_complex(5, 0);
    coeffs[1] = init_complex(3, 0);
    coeffs[2] = init_complex(2, 0);
    coeffs[3] = init_complex(1, 0);
    complex_polynomial_p p = init_complex_polynomial(degree, coeffs);

    destroy_complex(coeffs[0]);
    destroy_complex(coeffs[1]);
    destroy_complex(coeffs[2]);
    destroy_complex(coeffs[3]);

    coeffs[0] = init_complex(11, 0);
    coeffs[1] = init_complex(3, 2);
    coeffs[2] = init_complex(3, 0);
    coeffs[3] = init_complex(3, -2);

    complex_polynomial_p expected_result = init_complex_polynomial(degree, coeffs);
    complex_polynomial_p result = fast_fourier_transform(p);

    assert(equal_complex_polynomial(result, expected_result));

    destroy_complex(coeffs[0]);
    destroy_complex(coeffs[1]);
    destroy_complex(coeffs[2]);
    destroy_complex(coeffs[3]);
    free(coeffs);

    destroy_complex_polynomial(result);
    destroy_complex_polynomial(expected_result);
    destroy_complex_polynomial(p);

    printf("PASSED");
}
