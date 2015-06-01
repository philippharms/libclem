#ifndef CLEM_MATRIX3X3F_BUFFER_H
#define CLEM_MATRIX3X3F_BUFFER_H

#include "error.h"

#include <stddef.h>

typedef struct matrix3x3f_buffer {
  float restrict *a00, restrict *a01, restrict *a02;
  float restrict *a10, restrict *a11, restrict *a12;
  float restrict *a20, restrict *a21, restrict *a22;
  size_t n, allocated;
} matrix3x3f_buffer_t;

void matrix3x3f_buffer_init(matrix3x3f_buffer *buffer);

void matrix3x3f_buffer_reserve(matrix3x3f_buffer *buffer);

void matrix3x3f_buffer_free(matrix3x3f_buffer *buffer);

void matrix3x3f_buffer_pushback(float a00, float a01, float a02,
                                float a10, float a11, float a12,
                                float a20, float a21, float a22);

void matrix3x3f_buffer_pushback_arr(float[3][3] matrix);

#endif
