#ifndef CLEM_MATH_PRIVATE_H
#define CLEM_MATH_PRIVATE_H

#include <stdint.h>

#if !defined(CLEM_ENDIANNESS) || !defined(CLEM_FLOAT_ENDIANNESS)
# error "Please define the endianess of your platform."
#elif CLEM_ENDIANNESS == CLEM_FLOAT_ENDIANNESS
// actually, it masks the lower half of the mantissa ;)
# define CLEM_MANTISSA_MASKf 0x00000fff
#else
# define CLEM_MANTISSA_MASKf 0xfff00000
#endif

float splitf(float arg, float* lo) {
  // TODO: unclear behavior for special numbers
  uint32_t mask = CLEM_MANTISSA_MASKf;
  uint32_t pattern = *(uint32_t*) &arg;
  pattern &= ~mask;
  float hi = *(float*) &pattern;
  *lo = arg - hi;
  return hi;
}

#undef CLEM_MANTISSA_MASK

#endif
