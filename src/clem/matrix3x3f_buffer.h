#ifndef CLEM_MATRIX3X3F_BUFFER_H
#define CLEM_MATRIX3X3F_BUFFER_H

#include "error.h"

#include <stddef.h>

typedef float matrix3x3f_t[3][3];

typedef struct matrix3x3f_buffer {
  float* data[3][3];
  size_t n, allocated;
} matrix3x3f_buffer_t;

matrix3x3f_buffer_t matrix3x3f_buffer_create();

size_t matrix3x3f_buffer_get_size(matrix3x3f_buffer_t buffer);

size_t matrix3x3f_buffer_get_capacity(matrix3x3f_buffer_t buffer);

clem_error_t matrix3x3f_buffer_reserve(matrix3x3f_buffer_t *buffer,
                                       size_t size);

void matrix3x3f_buffer_free(matrix3x3f_buffer_t buffer);

clem_error_t matrix3x3f_buffer_pushback(matrix3x3f_buffer_t *buffer,
                                        float a00, float a01, float a02,
                                        float a10, float a11, float a12,
                                        float a20, float a21, float a22);

clem_error_t matrix3x3f_buffer_pushback_arr(matrix3x3f_buffer_t *buffer,
                                            matrix3x3f_t matrix);

clem_error_t matrix3x3f_buffer_popback(matrix3x3f_buffer_t *buffer,
                                       matrix3x3f_t *result);

#endif
