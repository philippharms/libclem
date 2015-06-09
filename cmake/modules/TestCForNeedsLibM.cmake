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

if(NOT DEFINED _CMAKE_C_NEEDS_LIBM)
  message(STATUS "Check whether C compiler needs to link libm")
  try_compile(_CMAKE_C_NEEDS_LIBM ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/modules/TestCForNeedsLibM.c)
  if(_CMAKE_C_NEEDS_LIBM)
    message(STATUS "Check whether C compiler needs to link libm - no")
    set(CMAKE_C_NEEDS_LIBM 0 CACHE INTERNAL
      "Does the C compiler need to link libm.")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the C compiler needs to link libm passed with "
      "the following output:\n${OUTPUT}\n\n")
  else()
    message(STATUS "Check whether C compiler needs to link libm - yes")
    set(CMAKE_C_NEEDS_LIBM 1 CACHE INTERNAL
      "Does the C compiler need to link libm.")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the C compiler needs to link libm failed with "
      "the following output:\n${OUTPUT}\n\n")
  endif()
endif()
