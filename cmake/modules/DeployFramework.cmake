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

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND NOT IOS)
  function(_createosxcomponentpackage_failure_message msg)
    message(SEND_ERROR "${msg}")
  endfunction()

  find_program(CreateOSXComponentPackage_PKGBUILD pkgbuild)

  if(NOT CreateOSXComponentPackage_PKGBUILD)
    _createosxcomponentpackage_failure_message("Could not find pkgbuild")
  endif()

  mark_as_advanced(CreateOSXComponentPackage_PKGBUILD)

  if(NOT TARGET deploy)
    add_custom_target(deploy)
  endif()

  function(deploy_framework framework-target)
    get_target_property(OUTPUT_NAME ${framework-target} OUTPUT_NAME)
    get_target_property(VERSION ${framework-target} VERSION)
    get_target_property(OSX_PKGBUILD_ID ${framework-target} OSX_PKGBUILD_ID)

    add_custom_target(${framework-target}-deploy
      COMMAND mkdir distribution || true
      COMMAND ${CreateOSXComponentPackage_PKGBUILD}
        --install-location /Library/Frameworks
        --identifier ${OSX_PKGBUILD_ID}
        --component "${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_NAME}.framework"
        distribution/${OUTPUT_NAME}-${VERSION}-MacOSX-Xcode.pkg
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
      add_dependencies(deploy ${framework-target}-deploy)
  endfunction()
else()
  macro(deploy_framework)
  endmacro()
endif()
