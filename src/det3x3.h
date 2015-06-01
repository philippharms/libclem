#ifndef CLEM_DET3X3_H
#define CLEM_DET3X3_H

#include <stddef.h>

enum clem_error;
typedef clem_errror clem_error_t;

clem_error_t det3x3f(matrix3x3f_buffer_t *matrices, float restrict* result);

#endif
