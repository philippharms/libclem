#ifndef CLEM_ERROR_H
#define CLEM_ERROR_H

typedef enum clem_error {
  CLEM_SUCCESS                        = 0,
  CLEM_OUT_OF_MEMORY                  = 1,
  CLEM_INVALID_VALUE                  = 2,
  CLEM_OUT_OF_RANGE                   = 3,
  CLEM_SET_FLOAT_ROUNDING_MODE_FAILED = 4,
  CLEM_UNKNOWN_ROUNDING_MODE          = 5,
  CLEM_NOT_IMPLEMENTED                = 6
} clem_error_t;

#endif
