#include "bml_inverse.h"
#include "bml_introspection.h"
#include "bml_utilities.h"
#include "bml_logger.h"
#include "bml_types.h"
#include "dense/bml_inverse_dense.h"
#include "ellpack/bml_inverse_ellpack.h"

bml_matrix_t *
bml_inverse(
    const bml_matrix_t * A)
{
    bml_matrix_t *B = NULL;

    switch (bml_get_type(A))
    {
        case dense:
            B = bml_inverse_dense(A);
            break;
        case ellpack:
            B = bml_inverse_ellpack(A);
            break;
        case ellsort:
            LOG_ERROR("inverse routine is not implemented for ellsort\n");
            break;
        default:
            LOG_ERROR("unknown matrix type\n");
            break;
    }

    return B;

}
