#include "det3x3.h"

clem_error_t det3x3f(matrix3x3f_buffer_t matrices, float *result) {
  size_t n = matrix3x3f_buffer_get_size(matrices);
  if (n == 0) {
    return CLEM_SUCCESS;
  } else if (result == NULL) {
    return CLEM_INVALID_VALUE;
  }

  for (size_t k=0; k<n; k++) {
    result[k] =
      matrices.data[0][0][k] * matrices.data[1][1][k] * matrices.data[2][2][k] +
      matrices.data[0][1][k] * matrices.data[1][2][k] * matrices.data[2][0][k] +
      matrices.data[0][2][k] * matrices.data[1][0][k] * matrices.data[2][1][k] -
      matrices.data[0][2][k] * matrices.data[1][1][k] * matrices.data[2][0][k] -
      matrices.data[0][1][k] * matrices.data[1][0][k] * matrices.data[2][2][k] -
      matrices.data[0][0][k] * matrices.data[1][2][k] * matrices.data[2][1][k];
  }

  return CLEM_SUCCESS;
}
