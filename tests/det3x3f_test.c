#include "clem/det3x3.h"
#include "clem/matrix3x3f_buffer.h"

#include "unit_tests.h"

unit_test_result_t det3x3f_test_01(char **result_message) {
  clem_error_t err;

  matrix3x3f_buffer_t matrices = matrix3x3f_buffer_create();

  err = det3x3f(matrices, NULL);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

unit_test_result_t det3x3f_test_02(char **result_message) {
  clem_error_t err;

  matrix3x3f_buffer_t matrices = matrix3x3f_buffer_create();

  matrix3x3f_t matrix;
  matrix3x3f_buffer_pushback_arr(&matrices, matrix);

  err = det3x3f(matrices, NULL);

  if (err != CLEM_INVALID_VALUE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

unit_test_result_t det3x3f_test_03(char **result_message) {
  clem_error_t err;
  matrix3x3f_buffer_t buffer;

  matrix3x3f_t matrix = {
    { 0x1.p+25,  0x1.p+0,  0x0.555554p+0 },
    { 0x1.p+25,  0x1.p+0,  0x1.fffffep+0 },
    { 0x1.p+0,   0,        0x1.p+0       }
  };

  // (0,0) and (0,1) minor should cancel, leaving (0,2) minor as the result
  float testee = 0.f, reference = 0x1.aaaaaap+0;

  buffer = matrix3x3f_buffer_create();

  err = matrix3x3f_buffer_pushback_arr(&buffer, matrix);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  err = det3x3f(buffer, &testee);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d:\n"
                               " - %a != %a",
                               __FILE__, __LINE__, testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}
