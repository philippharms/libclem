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

The command creates HTML pages in your project's binary tree in a
``coverage`` subdirectory, which you can browse in your favorite browser.

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
     add_library(<name>-coverage [...] ${<NAME>_SOURCES})
     add_coverage_target(<name>-coverage <LANG>)

     add_executable(<name>-coverage-driver [...] ${<NAME>_TESTCASE_SOURCES})
     target_link_libraries(<name>-coverage-driver PRIVATE <name>-coverage)
     add_coverage_run(coverage_run_01 <name>-coverage-driver <args>)
   endif()

Disabling Coverage Tests
========================

The module creates an option ``CodeCov_BUILD_COVERAGE`` which defaults to
``On``. You can either invoke CMake with ``-DCodeCov_BUILD_COVERAGE=Off`` to
disable coverage targets or set the option in your scripts before inclusion:

.. code-block:: cmake

   option(CodeCov_BUILD_COVERAGE "Build coverage targets" Off)
   include(CodeCoverage)

Internally, this only disables the creation of the ``coverage`` target and its
associated runs (which are created by ``add_coverage_run``). It will not prevent
your binaries from being recompiled with coverage flags. This is done by
enclosing them in an ``if`` condition as in the examples above.

Dependencies
============

This modules currently supports GCC and clang [#]_. The lcov_ script is needed
when building with GCC. If you need to install lcov in a nonstandard location,
you can set ``CodeCov_GNU_LCOV`` and ``CodeCov_GNU_GENHTML`` in your project's
CMake cache.

.. _lcov: https://github.com/linux-test-project/lcov

.. [#] clang support will actually be added in a couple of days.
