#ifndef CLEM_DET3X3_H
#define CLEM_DET3X3_H

#include "error.h"
#include "matrix3x3f_buffer.h"

#include <stddef.h>

clem_error_t det3x3f(matrix3x3f_buffer_t matrices, float *result);

#endif
