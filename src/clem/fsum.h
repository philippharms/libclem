#ifndef CLEM_FSUM_H
#define CLEM_FSUM_H

#include "error.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

float       fsumf(const float *args, size_t argc, clem_error_t *err);

double      fsum(const double *args, size_t argc, clem_error_t *err);

long double fsuml(const long double *args, size_t argc, clem_error_t *err);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
inline float fsum(float *args, size_t argc, clem_error_t *err) {
  return fsumf(args, argc, err);
}

inline long double fsum(long double *args, size_t argc, clem_error_t *err) {
  return fsuml(args, argc, err);
}
#elif  __STDC_VERSION__ >= 201112L
#define fsum(args, argc, err) _Generic((args)), \
  float *: fsumf, \
  double *: fsum, \
  long double *: fsuml, \
  default: fsum)(args, argc, err)
#endif

#endif
