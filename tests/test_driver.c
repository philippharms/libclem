#include "unit_tests.h"

#include <stdio.h>
#include <string.h>

const char** find_arg(const char **first, const char **last, const char *arg) {
  for (; first != last; first++) {
    if (strcmp(*first, arg) == 0)
      break;
  }

  return first;
}

void print_help(const char* command_name) {
  printf("Usage: %s --test-case <test_name>\n", command_name);
}

int main(int argc, char *argv[]) {
  const char *  command_name = *argv;
  const char ** args_begin   = (const char**) argv+1;
  const char ** args_end     = (const char**) argv+argc;

  const char * test_name = NULL;
  {
    const char ** it = find_arg(args_begin, args_end, "--test-case");
    if (it == args_end || it+1 == args_end) {
      print_help(command_name);
      return TEST_FATAL;
    }

    test_name = *(it+1);
  }

  unit_test_error_t err = UNIT_TEST_SUCCESS;
  unit_test_list_t list = unit_test_initialize_list(&err);

  if (err != UNIT_TEST_SUCCESS) {
    printf("internal error in %s:%d\n", __FILE__, __LINE__);
    return TEST_FATAL;
  }

  test_function_t test_case = unit_test_get_by_name(list, test_name);

  if (test_case == NULL) {
    printf("Could not find test case %s.\n", test_name);
    unit_test_free_list(list);
    return TEST_FATAL;
  }

  char *msg = NULL;
  unit_test_result_t result = test_case(&msg);

  if (result != TEST_PASSED) {
    puts(msg);
  }

  free(msg);
  unit_test_free_list(list);

  return result;
}
