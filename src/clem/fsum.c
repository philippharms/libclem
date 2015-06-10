#include "fsum.h"

#include <fenv.h>
#include <math.h>
#include <stdlib.h>

#pragma STDC FENV_ACCESS ON

static inline void set_error_code(clem_error_t in, clem_error_t *out) {
  if (out != NULL) {
    *out = in;
  }
}

static inline int samesignf(float lhs, float rhs) {
  return ((lhs >= 0.f) == (rhs >= 0.f));
}

static inline float sum2f_unchecked(float a, float b, float *roundoff) {
  float sum = a + b;

  volatile float b_virtual  = sum - a;

  *roundoff =  b - b_virtual;
  return sum;
}

static inline float sum2f(float lhs, float rhs, float *roundoff) {
  if (fabsf(lhs) < fabsf(rhs)) {
    float tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }

  return sum2f_unchecked(lhs, rhs, roundoff);
}

float fsumf(const float *args, size_t argc, clem_error_t *err) {
  if (!argc) {
    set_error_code(CLEM_SUCCESS, err);
    return 0.f;
  } else if (!args) {
    set_error_code(CLEM_INVALID_VALUE, err);
    return 0.f;
  }

  int old_mode = fegetround();
  if (old_mode != FE_TONEAREST) {
    int error = fesetround(FE_TONEAREST);
    if (error) {
      set_error_code(CLEM_SET_FLOAT_ROUNDING_MODE_FAILED, err);
      return 0.f;
    }
  }

  float *expansion = (float*) malloc(argc * sizeof(float));

  if (!expansion) {
    free(expansion);
    set_error_code(CLEM_OUT_OF_MEMORY, err);
    return 0.f;
  }

  for (size_t i=0; i<argc; i++) {

    float tmp = args[i];
    for (size_t j=0; j<i; j++) {
      tmp = sum2f(tmp, expansion[j], &expansion[j]);
    }
    expansion[i] = tmp;
  }

  float result = expansion[argc-1], roundoff = 0.f, nexttoroundoff = 0.f;

  for (size_t i=2; i<=argc; i++) {
    result = sum2f_unchecked(result, expansion[argc-i], &roundoff);
    if (roundoff != 0.f) {
      for (size_t j=i+1; j<=argc; j++) {
        nexttoroundoff = expansion[argc-j];
        if (nexttoroundoff != 0.f) {
          break;
        }
      }
      break;
    }
  }

  set_error_code(CLEM_SUCCESS, err);

  if (old_mode == FE_TONEAREST) {
    if (nexttoroundoff != 0.f && samesignf(roundoff, nexttoroundoff) &&
        (result + 2.f*roundoff) - result == 2.f*roundoff) {
      result += 2.f*roundoff;
    }
  } else if (old_mode == FE_DOWNWARD) {
    if (roundoff < 0.f) {
      result = nextafterf(result, -HUGE_VALF);
    }
  } else if (old_mode == FE_TOWARDZERO) {
    if (!samesignf(result, roundoff)) {
      result = nextafterf(result, 0.f);
    }
  } else if (old_mode == FE_UPWARD) {
    if (roundoff > 0.f) {
      result = nextafterf(result, HUGE_VALF);
    }
  } else {
    set_error_code(CLEM_UNKNOWN_ROUNDING_MODE, err);
    result = 0.f;
  }

  fesetround(old_mode);
  free(expansion);

  return result;
}
