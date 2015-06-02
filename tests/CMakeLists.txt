set(CLEM_TEST_SOURCES "test_driver.c"
                      "matrix3x3f_buffer_test.c"
                      "det3x3f_test.c")

if (BUILD_TESTING OR CodeCov_BUILD_COVERAGE)
  set(CLEM_TEST_LIST_FILE "${CMAKE_CURRENT_BINARY_DIR}/unit_tests.c")
  set(CLEM_TEST_FORWARD_FILE "${CMAKE_CURRENT_BINARY_DIR}/unit_tests_forward.h")

  list(APPEND CLEM_TEST_SOURCES ${CLEM_TEST_LIST_FILE})
endif()

if(BUILD_TESTING)
  add_executable(clem-test-driver ${CLEM_TEST_SOURCES})
  set_property(TARGET clem-test-driver APPEND PROPERTY
               INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/src"
                                   "${CMAKE_CURRENT_SOURCE_DIR}")
  set_property(TARGET clem-test-driver PROPERTY C_STANDARD 11)

  if(CLEM_BUILD_SHARED_LIBRARY)
    target_link_libraries(clem-test-driver PRIVATE clem-shared)
  else()
    target_link_libraries(clem-test-driver PRIVATE clem-static)
  endif()
endif()

if(CodeCov_BUILD_COVERAGE)
  add_library(clem-coverage SHARED ${CLEM_SOURCES})
  set_property(TARGET clem-coverage PROPERTY C_STANDARD 11)
  add_coverage_target(clem-coverage C)

  add_executable(clem-coverage-driver ${CLEM_TEST_SOURCES})
  set_property(TARGET clem-coverage-driver APPEND PROPERTY
               INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/src"
                                   "${CMAKE_CURRENT_SOURCE_DIR}")
  set_property(TARGET clem-coverage-driver PROPERTY C_STANDARD 11)

  target_link_libraries(clem-coverage-driver PRIVATE clem-coverage)
endif()

if(BUILD_TESTING OR CodeCov_BUILD_COVERAGE)
  string(TIMESTAMP CLEM_BUILD_DATE "%Y-%m-%d" UTC)

  set(UNIT_TEST_FORWARDS "")
  set(UNIT_TEST_INITS "")

  function(add_unit_test test_name)
    set(UNIT_TEST_FORWARDS
    "${UNIT_TEST_FORWARDS}\ntest_result_t ${test_name}(char **result_message);\n" PARENT_SCOPE)
    set(UNIT_TEST_INITS
        "${UNIT_TEST_INITS}\n  UNIT_TEST_ADD_TEST(${test_name});" PARENT_SCOPE)
    if(BUILD_TESTING)
      add_test(NAME ${test_name} COMMAND clem-test-driver --test-case ${test_name})
    endif()
    if(CodeCov_BUILD_COVERAGE)
      add_coverage_run(${test_name} clem-coverage-driver --test-case ${test_name})
    endif()
  endfunction()

  add_unit_test(matrix3x3f_buffer_test_01)
  add_unit_test(matrix3x3f_buffer_test_02)
  add_unit_test(matrix3x3f_buffer_test_03)
  add_unit_test(matrix3x3f_buffer_test_04)
  add_unit_test(matrix3x3f_buffer_test_05)
  add_unit_test(matrix3x3f_buffer_test_06)
  add_unit_test(matrix3x3f_buffer_test_07)
  add_unit_test(matrix3x3f_buffer_test_08)

  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.c.in"
                 "${CLEM_TEST_LIST_FILE}")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/unit_tests_forward.h.in"
                 "${CLEM_TEST_FORWARD_FILE}")
endif()
