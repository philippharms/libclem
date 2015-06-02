#include "matrix3x3f_buffer.h"

#include <stdlib.h>
#include <string.h>

#define CACHELINE_SIZE 64

matrix3x3f_buffer_t matrix3x3f_buffer_create() {
  matrix3x3f_buffer_t result = { 0 };

  return result;
}

size_t matrix3x3f_buffer_get_size(matrix3x3f_buffer_t buffer) {
  return buffer.n;
}

size_t matrix3x3f_buffer_get_capacity(matrix3x3f_buffer_t buffer) {
  return buffer.allocated;
}

clem_error_t matrix3x3f_buffer_reserve(matrix3x3f_buffer_t *buffer,
                                       size_t size) {
  if (!buffer) {
    return CLEM_INVALID_VALUE;
  } else if (size == 0) {
    matrix3x3f_buffer_free(*buffer);
    buffer->allocated = 0;
    buffer->n = 0;
    return CLEM_SUCCESS;
  } else if (size == buffer->allocated) {
    return CLEM_SUCCESS;
  }

  // cannot use realloc since allocation might fail and we would end up with
  // an invalid object. Hence, a new buffer is allocated.
  matrix3x3f_buffer_t other = { 0 };
  int out_of_memory = 0;
  {
    size_t n_bytes = size * sizeof(float);
    for (size_t i=0; i<3; i++)
      for (size_t j=0; j<3; j++) {
        other.data[i][j] = malloc(n_bytes);
        out_of_memory = out_of_memory || !other.data[i][j];
      }

    other.allocated = size;
  }

  if (out_of_memory) {
    for (size_t i=0; i<3; i++)
      for (size_t j=0; j<3; j++) {
        free(buffer->data[i][j]);
      }

    return CLEM_OUT_OF_MEMORY;
  }

  // copy data to new buffer
  other.n = (buffer->n < size) ? other.n : size;
  {
    size_t n_bytes = other.n * sizeof(float);
    for (size_t i=0; i<3; i++)
      for (size_t j=0; j<3; j++) {
        memcpy(buffer->data[i][j], other.data[i][j], n_bytes);
      }
  }

  *buffer = other;

  return CLEM_SUCCESS;
}

void matrix3x3f_buffer_free(matrix3x3f_buffer_t buffer) {
  if (buffer.allocated == 0) {
    return;
  }

  for (size_t i=0; i<3; i++)
    for (size_t j=0; j<3; j++) {
      free(buffer.data[i][j]);
    }
}

clem_error_t matrix3x3f_buffer_pushback_arr(matrix3x3f_buffer_t *buffer,
                                            matrix3x3f_t matrix) {
  if (!buffer) {
    return CLEM_INVALID_VALUE;
  } else if (buffer->n+1 > buffer->allocated) {
    clem_error_t err = matrix3x3f_buffer_reserve(
      buffer, (buffer->allocated == 0) ? 1 : buffer->allocated * 2);
    if (err != CLEM_SUCCESS) {
      return err;
    }
  }

  for (size_t i=0; i<3; i++)
    for (size_t j=0; j<3; j++) {
      buffer->data[i][j][buffer->n] = matrix[i][j];
    }

  buffer->n = buffer->n + 1;

  return CLEM_SUCCESS;
}

clem_error_t matrix3x3f_buffer_popback(matrix3x3f_buffer_t *buffer,
                                       matrix3x3f_t *result) {
  if (!(buffer && result)) {
    return CLEM_INVALID_VALUE;
  } else if (buffer->n == 0) {
    return CLEM_OUT_OF_RANGE;
  }

  buffer->n = buffer->n - 1;

  for (size_t i=0; i<3; i++)
    for (size_t j=0; j<3; j++) {
      (*result)[i][j] = buffer->data[i][j][buffer->n];
    }

  return CLEM_SUCCESS;
}
