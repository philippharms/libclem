# Copyright (c) 2015, Philipp Harms
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

if(NOT DEFINED _CMAKE_FLOAT_BIG_ENDIAN)
  message(STATUS "Check if the system's floats are big endian")
  try_run(_CMAKE_FLOAT_BIG_ENDIAN _CMAKE_TEST_FLOAT_BIG_ENDIAN_COMPILE_ERROR ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/modules/TestFloatBigEndian.c
    COMPILE_OUTPUT_VARIABLE COMPILE_OUTPUT)
  if(_CMAKE_TEST_FLOAT_BIG_ENDIAN_COMPILE_ERROR)
    message(SEND_ERROR "Check whether C compiler needs to link libm - failed")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the system's floats are big endian failed because of a "
      " build error with the following output:\n${COMPILE_OUTPUT}\n\n")
  elseif(_CMAKE_FLOAT_BIG_ENDIAN)
    message(STATUS "Check if the system's floats are big endian - yes")
    set(CMAKE_FLOAT_BIG_ENDIAN 1 CACHE INTERNAL
      "Are the system's floats big endian.")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the system's floats are big endian passed with the "
      "following result:\nbig endian\n\n")
  else()
    message(STATUS "Check if the system's floats are big endian - no")
    set(CMAKE_FLOAT_BIG_ENDIAN 0 CACHE INTERNAL
      "Are the system's floats big endian.")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the system's floats are big endian passed with the "
      " following result:\nlittle endian\n\n")
  endif()
endif()
