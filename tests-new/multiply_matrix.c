#include "bml.h"
#include "bml_test.h"

#include <math.h>
#include <stdlib.h>

int
test_function(
    const int N,
    const bml_matrix_type_t matrix_type,
    const bml_matrix_precision_t matrix_precision,
    const int M)
{
    bml_matrix_t *A = NULL;
    bml_matrix_t *B = NULL;
    bml_matrix_t *C = NULL;

    float *A_float = NULL, *B_float = NULL, *C_float = NULL;
    double *A_double = NULL, *B_double = NULL, *C_double = NULL;

    double alpha_factor = 1.0;
    double beta_factor = 1.0;
    double threshold = 0.0;

    A = bml_random_matrix(matrix_type, matrix_precision, N, M);
    B = bml_zero_matrix(matrix_type, matrix_precision, N, M);
    C = bml_zero_matrix(matrix_type, matrix_precision, N, M);
    bml_multiply(A, A, C, alpha_factor, beta_factor, threshold);
    bml_multiply_x2(A, B, threshold);


    switch (matrix_precision)
    {
    case single_real:
        A_float = bml_convert_to_dense(A);
        B_float = bml_convert_to_dense(B);
        C_float = bml_convert_to_dense(C);
        bml_print_dense_matrix(N, matrix_precision, A_float, 0, N, 0, N);
        bml_print_dense_matrix(N, matrix_precision, B_float, 0, N, 0, N);
        bml_print_dense_matrix(N, matrix_precision, C_float, 0, N, 0, N);
        for (int i = 0; i < N * N; i++)
        {
            if (fabs(B_float[i] - C_float[i]) > 1e-12)
            {
                LOG_ERROR("matrices are not identical; B[%d] = %e C[%d] = %e\n", i, B_float[i], i, C_float[i]);
                return -1;
            }
        }
        bml_free_memory(A_float);
        bml_free_memory(B_float);
        bml_free_memory(C_float);
        break;
    case double_real:
        A_double = bml_convert_to_dense(A);
        B_double = bml_convert_to_dense(B);
        C_double = bml_convert_to_dense(C);;
        bml_print_dense_matrix(N, matrix_precision, A_double, 0, N, 0, N);
        bml_print_dense_matrix(N, matrix_precision, B_double, 0, N, 0, N);
        bml_print_dense_matrix(N, matrix_precision, C_double, 0, N, 0, N);
        for (int i = 0; i < N * N; i++)
        {
            if (fabs(B_double[i] - C_double[i]) > 1e-12)
            {
                LOG_ERROR("matrices are not identical; B[%d] = %e C[%d] = %e\n", i, B_double[i], i, C_double[i]);
                return -1;
            }
        }
        bml_free_memory(A_double);
        bml_free_memory(B_double);
        bml_free_memory(C_double);
        break;
    default:
        LOG_ERROR("unknown precision\n");
        return -1;
        break;
    }
    bml_deallocate(&A);
    bml_deallocate(&B);
    bml_deallocate(&C);

    LOG_INFO("multiply matrix test passed\n");

    return 0;
}