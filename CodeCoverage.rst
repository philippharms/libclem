CodeCoverage
************

This module defines some functions to wrap the code coverage capabilities of
the compiler.

How to Use
==========
The build flags of coverage targets are independent of the current build
configuration. You can use the ``add_coverage_target`` command to disable
optimizations and enable profiling on a target. Of course, additional flags
can be added as usual. See Executables_ and Libraries_ for examples.

To enable the code coverage module, type the following in the cmake file of
your project's top-level directory:

.. code-block:: cmake

    include(CodeCoverage)

To invoke the coverage, run:

.. code-block:: shell

    $ make && make coverage

Executables
-----------

Redefine a target to recompile it with the profiling flags set:

.. code-block:: cmake

    if(CodeCov_BUILD_COVERAGE)
      add_executable(<name>-coverage [...] ${<NAME>_SOURCES})
      add_coverage_target(<name>-coverage <LANG>) # <LANG> is e.g. C/CXX/Fortran
      add_coverage_run(coverage_run_01 <name>-coverage <args>)
    endif()

Libraries
----------------

The following works with static and shared libraries:

.. code-block:: cmake

   if(CodeCov_BUILD_COVERAGE)
     add_library(<name>-coverage ${<NAME>_SOURCES})
     add_coverage_target(<name>-coverage <LANG>)

     add_executable(<name>-coverage-driver [...] ${<NAME>_TESTCASE_SOURCES})
     target_link_libraries(<name>-coverage-driver PRIVATE <name>-coverage)
     add_coverage_run(coverage_run_01 <name>-coverage-driver <args>)
   endif()

