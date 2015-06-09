#include "clem/fsum.h"

#include "unit_tests.h"

#pragma STDC FENV_ACCESS ON

#include <fenv.h>
#include <stdint.h>

clem_error_t fsumf_test_basic_01(char **result_message) {
  clem_error_t err;
  float reference = 0.f;
  float testee = fsumf(NULL, 0, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_basic_02(char **result_message) {
  clem_error_t err;
  float testee = fsumf(NULL, 1, &err);

  if (err != CLEM_INVALID_VALUE) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_basic_03(char **result_message) {
  float vals[1] = { 0.f };

  clem_error_t err;
  float testee = fsumf(vals, SIZE_MAX / sizeof(float), &err);

  if (err != CLEM_OUT_OF_MEMORY) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundtonearest_01(char **result_message) {
  float vals[] = { 0x1.fffffep+0, 0x1.p-24};

  clem_error_t err;
  float reference = 0x1.p+1;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundtonearest_02(char **result_message) {
  float vals[] = { 0x1.fffffdp+0, 0x1.p-24};

  clem_error_t err;
  float reference = 0x1.fffffdp+0;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundtonearest_03(char **result_message) {
  float vals[] = { 0x1.fffffep-49, 0x1.fffffep-25, 0x1.fffffep+0 };

  clem_error_t err;
  float reference = 0x1.fffffep+0;
  float testee = fsumf(vals, 3, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_rounddownward_01(char **result_message) {
  float vals[] = { 0x1.fffffep+0, 0x1.p-24 };

  if (fesetround(FE_DOWNWARD)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  clem_error_t err;
  float reference = 0x1.fffffep+0;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_rounddownward_02(char **result_message) {
  float vals[] = { -0x1.fffffep+0, -0x1.p-24 };

  if (fesetround(FE_DOWNWARD)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  clem_error_t err;
  float reference = -0x1.p+1;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundtowardzero_01(char **result_message) {
  float vals[] = { 0x1.fffffep+0, 0x1.p-24 };

  if (fesetround(FE_TOWARDZERO)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  clem_error_t err;
  float reference = 0x1.fffffep+0;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundtowardzero_02(char **result_message) {
  float vals[] = { -0x1.fffffep+0, -0x1.p-24 };

  if (fesetround(FE_TOWARDZERO)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  clem_error_t err;
  float reference = -0x1.fffffep+0;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundupward_01(char **result_message) {
  float vals[] = { 0x1.fffffep+0, 0x1.p-24 };

  if (fesetround(FE_UPWARD)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  clem_error_t err;
  float reference = 0x1.p+1;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

clem_error_t fsumf_test_roundupward_02(char **result_message) {
  float vals[] = { -0x1.fffffep+0, -0x1.p-24 };

  if (fesetround(FE_UPWARD)) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  clem_error_t err;
  float reference = -0x1.fffffep+0;
  float testee = fsumf(vals, 2, &err);

  if (err != CLEM_SUCCESS) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n",
                               __FILE__, __LINE__);
    return TEST_FATAL;
  }

  if (testee != reference) {
    CREATE_TEST_RESULT_MESSAGE(result_message, "An error occurred in %s:%d\n"
                               " - %a != %a", __FILE__, __LINE__,
                               testee, reference);
    return TEST_FAILED;
  }
}
