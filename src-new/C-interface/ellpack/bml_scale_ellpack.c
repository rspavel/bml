#include "bml_logger.h"
#include "bml_scale.h"
#include "bml_scale_ellpack.h"
#include "bml_types.h"
#include "bml_types_ellpack.h"

#include <stdlib.h>
#include <string.h>

/** Scale an ellpack matrix - result is a new matrix.
 *
 *  \ingroup scale_group
 *
 *  \param A The matrix to be scaled
 *  \return A scale version of matrix A.
 */
bml_matrix_ellpack_t *
bml_scale_ellpack_new(
    const double scale_factor,
    const bml_matrix_ellpack_t * A)
{
    bml_matrix_ellpack_t *B = NULL;

    switch (A->matrix_precision)
    {
    case single_real:
        B = bml_scale_ellpack_new_single_real(scale_factor, A);
        break;
    case double_real:
        B = bml_scale_ellpack_new_double_real(scale_factor, A);
        break;
    default:
        LOG_ERROR("unknown precision\n");
        break;
    }
    return B;
}

/** Scale an ellpack matrix.
 *
 *  \ingroup scale_group
 *
 *  \param A The matrix to be scaled
 *  \param B Scaled version of matrix A
 */
void
bml_scale_ellpack(
    const double scale_factor,
    const bml_matrix_ellpack_t * A,
    const bml_matrix_ellpack_t * B)
{
    switch (A->matrix_precision)
    {
    case single_real:
        bml_scale_ellpack_single_real(scale_factor, A, B);
        break;
    case double_real:
        bml_scale_ellpack_double_real(scale_factor, A, B);
        break;
    default:
        LOG_ERROR("unknown precision\n");
        break;
    }
}
