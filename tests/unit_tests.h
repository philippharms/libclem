#ifndef CLEM_UNIT_TESTS_H
#define CLEM_UNIT_TESTS_H

#include "test.h"

typedef enum unit_test_error {
  UNIT_TEST_SUCCESS = 0,
  UNIT_TEST_OUT_OF_MEMORY = 1
} unit_test_error_t;

typedef test_result_t (*test_function_t)(char ** /*result_message*/);
typedef struct unit_test_list * unit_test_list_t;

unit_test_list_t unit_test_initialize_list(unit_test_error_t *err);

void unit_test_free_list(unit_test_list_t list);

test_function_t unit_test_get_by_name(unit_test_list_t list, const char* name);

#endif
