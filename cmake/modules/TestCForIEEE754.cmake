#.rst:
# TestCForIEEE754
# -------------------
#
# Test for IEEE 754 floating point support
#
# check if the compiler supports the IEEE Standard for Floating-Point
# Arithmetic (IEEE 754) for "float" and "double" type in C.
#
# ::
#
#   CMAKE_C_IEEE754_FLOATS - defined by the results

if(NOT DEFINED _CMAKE_C_IEEE754_FLOATS)
  message(STATUS "Check whether C compiler supports IEEE 754 floats")
  try_compile(_CMAKE_C_IEEE754_FLOATS ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/modules/TestCForIEEE754.c)
  if(_CMAKE_C_IEEE754_FLOATS)
    message(STATUS "Check whether C compiler supports IEEE 754 floats - found")
    set(CMAKE_C_IEEE754_FLOATS 1 CACHE INTERNAL
      "Does the C compiler support IEEE 754 floats.")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the C compiler supports IEEE 754 floats passed with "
      "the following output:\n${OUTPUT}\n\n")
  else()
    message(STATUS "Check whether C compiler supports IEEE 754 floats - not found")
    set(CMAKE_C_IEEE754_FLOATS 0 CACHE INTERNAL
      "Does the C compiler support IEEE 754 floats.")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the C compiler supports IEEE 754 floats failed with "
      "the following output:\n${OUTPUT}\n\n")
  endif()
endif()
