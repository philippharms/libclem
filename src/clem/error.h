#ifndef CLEM_ERROR_H
#define CLEM_ERROR_H

typedef enum clem_error {
  CLEM_SUCCESS = 0,
  CLEM_OUT_OF_MEMORY = 1,
  CLEM_INVALID_VALUE = 2,
  CLEM_OUT_OF_RANGE = 3
} clem_error_t;

#endif
