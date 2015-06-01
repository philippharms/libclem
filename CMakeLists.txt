cmake_minimum_required(VERSION 3.0)

project(clem C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

include(SetInstallDirectories)

include(CTest)
include(CodeCoverage)
add_subdirectory(Tests)
