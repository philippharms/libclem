#include "det3x3.h"
#include "fsum.h"
#include "math-private.h"

static inline float mult2f(float lhs, float rhs, float* roundoff) {
  float lhs_hi, lhs_lo, rhs_hi, rhs_lo;
  float tmp, a, b, rounded;

  lhs_hi = splitf(lhs, &lhs_lo);
  rhs_hi = splitf(rhs, &rhs_lo);

  rounded = lhs*rhs;
  tmp = (lhs_hi * rhs_hi) - rounded, a = lhs_hi * rhs_lo, b = lhs_lo * rhs_hi;
  tmp = (a > b) ? (tmp + a) + b : (tmp + b) + a;
  tmp = tmp + (lhs_lo * rhs_lo);

  *roundoff = tmp;

  return rounded;
}

static inline clem_error_t mult3f(float arg1, float arg2, float arg3,
                                  float *result1, float *result2,
                                  float *result3) {
  clem_error_t err;
  float hi, lo, hi2, lo2, hi3, lo3;
  hi  = mult2f(arg1, arg2, &lo);
  hi2 = mult2f(hi, arg3, &lo2);
  hi3 = mult2f(lo, arg3, &lo3);

  float tmp[6] = { hi2, lo2, hi3, lo3, 0.f, 0.f };
  *result1 = fsumf(tmp, 4, &err);
  if (err != CLEM_SUCCESS) {
    return err;
  }
  tmp[4] = -*result1;

  *result2 = fsumf(tmp, 5, &err);
  if (err != CLEM_SUCCESS) {
    return err;
  }
  tmp[5] = -*result2;

  *result3 = fsumf(tmp, 6, &err);
  if (err != CLEM_SUCCESS) {
    return err;
  }

  return CLEM_SUCCESS;
}

clem_error_t det3x3f(matrix3x3f_buffer_t matrices, float *result) {
  size_t n = matrix3x3f_buffer_get_size(matrices);
  if (n == 0) {
    return CLEM_SUCCESS;
  } else if (result == NULL) {
    return CLEM_INVALID_VALUE;
  }

  float tmp[18]; // the summands of Sarrus' rule
  for (size_t k=0; k<n; k++) {
    clem_error_t err = CLEM_SUCCESS;
    err |= mult3f(
      matrices.data[0][0][k], matrices.data[1][1][k], matrices.data[2][2][k],
      &tmp[0], &tmp[1], &tmp[2]);
    err |= mult3f(
      matrices.data[0][1][k], matrices.data[1][2][k], matrices.data[2][0][k],
      &tmp[3], &tmp[4], &tmp[5]);
    err |= mult3f(
      matrices.data[0][2][k], matrices.data[1][0][k], matrices.data[2][1][k],
      &tmp[6], &tmp[7], &tmp[8]);
    err |= mult3f(
      matrices.data[0][2][k], matrices.data[1][1][k], matrices.data[2][0][k],
      &tmp[9], &tmp[10], &tmp[11]);
    err |= mult3f(
      matrices.data[0][1][k], matrices.data[1][0][k], matrices.data[2][2][k],
      &tmp[12], &tmp[13], &tmp[14]);
    err |= mult3f(
      matrices.data[0][0][k], matrices.data[1][2][k], matrices.data[2][1][k],
      &tmp[15], &tmp[16], &tmp[17]);
    for (size_t i=9; i<18; i++) {
      tmp[i] = -tmp[i];
    }

    if (err != CLEM_SUCCESS) {
      return err;
    }

    result[k] = fsumf(tmp, 18, &err);
    if (err != CLEM_SUCCESS) {
      return err;
    }
  }

  return CLEM_SUCCESS;
}
