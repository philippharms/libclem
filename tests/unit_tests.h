#ifndef CLEM_UNIT_TESTS_H
#define CLEM_UNIT_TESTS_H

#include <stdio.h>
#include <stdlib.h>

#define UNIT_TEST_CREATE_RESULT_MESSAGE(output, format, ...) \
int ret = snprintf(NULL, 0u, format, ##__VA_ARGS__); \
if (ret < 0) { \
  *output = NULL; \
} else { \
  size_t needed_size = ret + 1; \
  *output = (char *) malloc(needed_size * sizeof(char)); \
  ret = snprintf(*output, needed_size, format, ##__VA_ARGS__); \
  \
  if (ret < 0) { \
    free (*output); \
    *output = NULL; \
  } \
}

typedef enum test_result {
  TEST_PASSED = 0,
  TEST_FAILED = 1,
  TEST_FATAL  = 2
} unit_test_result_t;

typedef enum unit_test_error {
  UNIT_TEST_SUCCESS = 0,
  UNIT_TEST_OUT_OF_MEMORY = 1
} unit_test_error_t;

typedef unit_test_result_t (*test_function_t)(char ** /*result_message*/);
typedef struct unit_test_list * unit_test_list_t;

unit_test_list_t unit_test_initialize_list(unit_test_error_t *err);

void unit_test_free_list(unit_test_list_t list);

test_function_t unit_test_get_by_name(unit_test_list_t list, const char* name);

#endif
