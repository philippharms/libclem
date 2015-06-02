#ifndef TESTS_TEST_H_
#define TESTS_TEST_H_

#include <stdio.h>
#include <stdlib.h>

typedef enum test_result {
  TEST_PASSED,
  TEST_FAILED,
  TEST_FATAL
} test_result_t;

#define CREATE_TEST_RESULT_MESSAGE(output, format, ...) \
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

#endif
