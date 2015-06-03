cmake_minimum_required(VERSION 3.1)

project(clem C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

option(CLEM_BUILD_SHARED_LIBRARY "build a shared library" On)
option(CLEM_BUILD_STATIC_LIBRARY "build a static library" Off)
option(CLEM_DISABLE_SANITY_CHECKS "disable all checks that prevent building - not recommended" Off)

include(TestCForIEEE754)
if (NOT CLEM_DISABLE_SANITY_CHECKS AND NOT CMAKE_C_IEEE754_FLOATS)
  message(FATAL_ERROR
    "Your system seems not to provide IEEE 754 standard compliant floating "
    "point number support. This library relies on standard compliancy and it "
    "is not recommended to use it nonetheless. If you mean to do this, rerun "
    "cmake with -DCLEM_DISABLE_SANITY_CHECKS=On."
  )
endif()

include(SetInstallDirectories)

add_subdirectory(src)
if(NOT DEFINED CLEM_SOURCES)
  message(AUTHOR_WARNING "CLEM_SOURCES should be set now.")
endif()

set(CLEM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include(PrependPath)
prepend_path(CLEM_SOURCES ${CLEM_SOURCE_DIR} CLEM_SOURCES)

include(CTest)
include(CodeCoverage)
add_subdirectory(tests)
