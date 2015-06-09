#include "det3x3.h"
#include "fsum.h"

clem_error_t det3x3f(matrix3x3f_buffer_t matrices, float *result) {
  size_t n = matrix3x3f_buffer_get_size(matrices);
  if (n == 0) {
    return CLEM_SUCCESS;
  } else if (result == NULL) {
    return CLEM_INVALID_VALUE;
  }

  float tmp[6]; // the summands of Sarrus' rule
  for (size_t k=0; k<n; k++) {
    tmp[0] = + matrices.data[0][0][k] * matrices.data[1][1][k] *
                matrices.data[2][2][k];
    tmp[1] = + matrices.data[0][1][k] * matrices.data[1][2][k] *
                matrices.data[2][0][k];
    tmp[2] = + matrices.data[0][2][k] * matrices.data[1][0][k] *
                matrices.data[2][1][k];
    tmp[3] = - matrices.data[0][2][k] * matrices.data[1][1][k] *
                matrices.data[2][0][k];
    tmp[4] = - matrices.data[0][1][k] * matrices.data[1][0][k] *
                matrices.data[2][2][k];
    tmp[5] = - matrices.data[0][0][k] * matrices.data[1][2][k] *
                matrices.data[2][1][k];

    clem_error_t err;
    result[k] = fsumf(tmp, 6, &err);
    if (err != CLEM_SUCCESS) {
      return err;
    }
  }

  return CLEM_SUCCESS;
}
