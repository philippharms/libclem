#include "clem/matrix3x3f_buffer.h"

#include "test.h"

#include <string.h>
#include <stdint.h>

test_result_t matrix3x3f_buffer_test_01(char **result_message) {
  clem_error_t err;

  matrix3x3f_buffer_t testee = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_reserve(&testee, 1000);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  size_t capacity = matrix3x3f_buffer_get_capacity(testee);
  size_t size = matrix3x3f_buffer_get_size(testee);

  if (capacity != 1000) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               "Capacity was %zd != %d",
                               __FILE__, __LINE__, capacity, 1000);
    return TEST_FAILED;
  }

  if (size != 0) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               "Size was %zd != %d",
                               __FILE__, __LINE__, size, 0);
    return TEST_FAILED;
  }

  err = matrix3x3f_buffer_reserve(&testee, 1000);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  size_t new_capacity = matrix3x3f_buffer_get_capacity(testee);

  if (new_capacity != capacity) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               "Capacity was %zd != %zd",
                               __FILE__, __LINE__, new_capacity, capacity);
    return TEST_FAILED;
  }

  matrix3x3f_buffer_free(testee);

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_02(char **result_message) {
  clem_error_t err;

  err = matrix3x3f_buffer_reserve(NULL, 0);

  if (err != CLEM_INVALID_VALUE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
    __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_03(char **result_message) {
  clem_error_t err;

  matrix3x3f_buffer_t testee = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_reserve(&testee, 0);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_04(char **result_message) {
  clem_error_t err;
  matrix3x3f_t matrix = {{0.f, 1.f, 2.f},{3.f, 4.f, 5.f},{6.f, 7.f, 8.f}};

  matrix3x3f_buffer_t testee = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_pushback_arr(&testee, matrix);

  if (!(err == CLEM_SUCCESS &&
        matrix3x3f_buffer_get_size(testee) == (size_t) 1)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  matrix3x3f_t returned = { 0 };
  err = matrix3x3f_buffer_popback(&testee, &returned);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  if (memcmp((const void*) matrix, (const void*) returned,
              sizeof(matrix3x3f_t))) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  if (matrix3x3f_buffer_get_size(testee) != (size_t) 0) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  matrix3x3f_buffer_free(testee);

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_05(char **result_message) {
  clem_error_t err;

  matrix3x3f_buffer_t testee = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_reserve(&testee, SIZE_MAX);

  if (err != CLEM_OUT_OF_MEMORY) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_06(char **result_message) {
  clem_error_t err;

  matrix3x3f_t matrix = {{0.f, 1.f, 2.f},{3.f, 4.f, 5.f},{6.f, 7.f, 8.f}};

  err = matrix3x3f_buffer_pushback_arr(NULL, matrix);

  if (err != CLEM_INVALID_VALUE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_07(char **result_message) {
  clem_error_t err;

  matrix3x3f_t result;
  matrix3x3f_buffer_t testee = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_popback(&testee, &result);

  if (err != CLEM_OUT_OF_RANGE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  matrix3x3f_buffer_free(testee);

  return TEST_PASSED;
}

test_result_t matrix3x3f_buffer_test_08(char **result_message) {
  clem_error_t err;

  matrix3x3f_t matrix = {{0.f, 1.f, 2.f},{3.f, 4.f, 5.f},{6.f, 7.f, 8.f}};

  matrix3x3f_buffer_t testee = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_pushback_arr(&testee, matrix);

  if (!(err == CLEM_SUCCESS &&
        matrix3x3f_buffer_get_size(testee) == (size_t) 1)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  err = matrix3x3f_buffer_popback(NULL, &matrix);

  if (err != CLEM_INVALID_VALUE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  err = matrix3x3f_buffer_popback(&testee, NULL);

  if (err != CLEM_INVALID_VALUE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
    __FILE__, __LINE__);
    return TEST_FATAL;
  }

  matrix3x3f_buffer_free(testee);

  return TEST_PASSED;
}
