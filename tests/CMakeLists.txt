set(CLEM_TEST_SOURCES "det3x3f_test.c")

if(BUILD_TESTING)
  add_executable(clem-test-driver ${CLEM_TEST_SOURCES})
  # TODO
endif()

if(CodeCov_BUILD_COVERAGE)
  add_executable(clem-coverage-driver ${CLEM_TEST_SOURCES})
  # TODO
endif()
