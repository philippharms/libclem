cmake_minimum_required(VERSION 3.1)

project(clem C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

option(CLEM_BUILD_SHARED_LIBRARY "build a shared library" On)
option(CLEM_BUILD_STATIC_LIBRARY "build a static library" Off)

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
