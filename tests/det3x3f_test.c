#include "clem/det3x3.h"
#include "clem/matrix3x3f_buffer.h"

#include "test.h"

test_result_t det3x3f_test_01(char **result_message) {
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
