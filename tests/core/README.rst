.. ReStructuredText
.. Copyright 2019-2023 MicroEJ Corp.  MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.

**********************
Core Engine Test Suite
**********************

Overview
========

This folder contains sources and projects to test drivers and implementation of print, time base, RAM, Core (see `Tests Description`_), and MicroEJ Core (see `MicroEJ Core Validation`_).

All tests can be run in one step: all tests will be executed one by one
and are run in a specific order, *next one* expects *previous one* is
passed.

For each test, the configuration and results are described in a
dedicated section. See `Quick Start`_ section which summarize how to configure the
tests, how to launch them and how to analyze the report.

Requirements
============

- Follow the `main Readme <../../README.rst>`_.
- EEMBC Coremark

Quick Start
===========

Configuration
-------------

#. In your BSP project, add all files of these folders as source files:

   * ``tests/core/c/src/``
   * ``framework/c/utils/src/``
   * ``framework/c/embunit/embUnit/``
   * ``framework/c/CoreMark/``

#. In your BSP project, add these folders as include paths:

   * ``tests/core/c/inc/``
   * ``framework/c/utils/inc/``
   * ``framework/c/embunit/embUnit/``
   * ``framework/c/CoreMark/``

#. Port EEMBC CoreMark (http://www.eembc.org/coremark/index.php) to your platform:

   * Pick one of the provided skeleton configuration folders located in ``framework/c/CoreMark/`` (*barebones* is a good choice, but one of the other folders may match your project better). Copy its source files into your BSP project and make sure they will be compiled/included.
   * Define the constants and functions required by CoreMark. What needs to be defined will depend on the configuration skeleton you picked, but CoreMark will at least require a clock and a text output. If you chose the *barebones* skeleton configuration, you will need to define the following:

      * In ``core_portme.h``:

         * Define the ``ITERATIONS`` constant as a number of iterations high enough to keep the benchmark running for at least 10 seconds. You will have to adjust its value depending on the hardware and according to the benchmark report, but ``1000`` is a good starting point.
         * Define the ``CLOCKS_PER_SEC`` as the frequency of your platform's clock ticks. CoreMark needs to be provided a clock to measure the time taken by the benchmarked operations. This constant will be used to convert the clock tick count to a value in seconds.
         * Define the ``TIMER_RES_DIVIDER`` constant. Its value will be used to prevent overflows of the clock tick count, but will reduce the time measurement resolution in return. Unless the resolution of your clock is too high and you experience integer overflows, you can set this constant to ``1``.
         * Go over the whole file and edit constants as needed for your platform. Specifically, you may want to edit the compiler version and flags, as well as some type definitions.

      * In ``core_portme.c``:

         * Implement ``barebones_clock`` to return the current time, measured in clock ticks. A clock frequency of 1 kHz is sufficient for CoreMark's measurements. You may use ``microej_time_get_current_time``, which should already be defined as it is required for the platform to run.
         * Add any needed initialization step to ``portable_init``. Namely, you might need to initialize the UART output there (if it is not yet initialized when reaching this point).

      * In ``ee_printf.c``:

         * Implement ``uart_send_char`` to send a single character through the UART output.

   * Finally, insert the directive line :code:`#define main core_main` in ``core_portme.h`` so that the BSP's main function does not conflict with CoreMark's main function.

#. Define all functions declared in ``x_ram_checks.h`` and ``x_core_benchmark.h``.

   * **RAM tests**: The RAM benchmark will perform several read, write and copy operations on different memory areas. You must allocate appropriate memory areas for these operations, and define all the ``X_RAM_CHECK`` functions that will give the benchmark access to these areas. See `RAM Tests: t_core_ram.c`_ and `RAM Benchs: t_core_ram.c`_ for more information.
   * **Run CoreMark**: Call CoreMark's main function in ``X_CORE_BENCHMARK_run``. This function should only call ``core_main``, and return ``true`` if CoreMark was run properly.

#. Implement other functions required by the benchmark:

   * :code:`int printf(const char* format, ...)` is required to output the benchmark results. If this function is not already defined, or if its ouptut is not visible, you will need to define your own version of it.
   * :code:`int64_t UTIL_TIME_BASE_getTime()` (declared in ``u_time_base.h``) must return the current time, in microseconds. You can call ``microej_time_get_time_nanos``, which should already be defined in your BSP project, as it is required for the platform to run.
   * :code:`void UTIL_TIME_BASE_initialize()` (declared in ``u_time_base.h``) should contain any necessary initialization step required for ``UTIL_TIME_BASE_getTime`` to perform its task.

#. Locate the call to ``microej_main`` in the BSP project. Include the ``t_core_main.h`` header file in this file, and add a call to the function ``T_CORE_main`` just before the call to ``microej_main``.
#. In the MicroEJ SDK, import the MicroEJ project ``java-testsuite-runner-core`` from the folder ``tests/core``.
#. Follow `MicroEJ Core Validation Readme <java-testsuite-runner-core/README.rst>`_ and build this MicroEJ Application against the MicroEJ Platform to qualify.
#. Build the BSP and link it with the MicroEJ Platform runtime library and MicroEJ Application.

Expected Results
----------------

::

   start
   .
   ****************************************************************************
   **                      Platform Qualification Core                       **
   **                              version 1.0                               **
   ****************************************************************************
   *           Copyright 2013-2020 MicroEJ Corp. All rights reserved.         *
   * Use of this source code is governed by a BSD-style license               *
   * that can be found with this software.                                    *
   ****************************************************************************

   Print test:
    if this message is displayed, the test is passed!

   Time base check:
   .
   RAM tests:
   .....................
   RAM speed benchmark:
   .RAM speed average read access (according to your configuration file 8/16/32 bits) : 51.180522MBytes/s
   .RAM speed average write access (according to your configuration file 8/16/32 bits) : 131.289164 MBytes/s
   .RAM speed average transfert access (according to your configuration file 8/16/32 bits) : 86.466471MBytes/s

   Core/Flash benchmark:
   .2K performance run parameters for coremark.
   CoreMark Size    : 666
   Total ticks      : 12052657
   Total time (secs): 12.052657
   Iterations/Sec   : 497.815544
   Iterations       : 6000
   Compiler version : ARMCC V5.06 update 4 (build 422)
   Compiler flags   : -c --cpu Cortex-M4.fp -D__MICROLIB -g -O3 -Otime --apcs=interwork --split_sections -D__UVISION_VERSION="523" -D_RTE_ -DSTM32L496xx -DUSE_HAL_DRIVER -DSTM32L496xx
   Memory location  : STATIC
   seedcrc          : 0xe9f5
   [0]crclist       : 0xe714
   [0]crcmatrix     : 0x1fd7
   [0]crcstate      : 0x8e3a
   [0]crcfinal      : 0xa14c
   Correct operation validated. See readme.txt for run and reporting rules.
   CoreMark 1.0 : 497.815544 / ARMCC V5.06 update 4 (build 422) -c --cpu Cortex-M4.fp -D__MICROLIB -g -O3 -Otime --apcs=interwork --split_sections -D__UVISION_VERSION="523" -D_RTE_ -DSTM32L496xx -DUSE_HAL_DRIVER -DSTM32L496xx / STATIC

   OK (27 tests)
   MicroEJ START
   *****************************************************************************************************
   *                                  MicroEJ Core Validation - 3.2.0                                  *
   *****************************************************************************************************
   * Copyright 2013-2023 MicroEJ Corp. All rights reserved.                                            *
   * Use of this source code is governed by a BSD-style license that can be found with this software.  *
   *****************************************************************************************************
   
   -> Check visible clock (LLMJVM_IMPL_getCurrentTime validation)...
   Property 'com.microej.core.tests.max.allowed.clock.tick.duration.milliseconds' is not set (default to '20' millisecondss)
   Property 'com.microej.core.tests.clock.seconds' is not set (default to '10' seconds)
   1
   2
   3
   4
   5
   6
   7
   8
   9
   10
   OK: testVisibleClock
   -> Check schedule request and wakeup (LLMJVM_IMPL_scheduleRequest and LLMJVM_IMPL_wakeupVM validation)...
   Property 'com.microej.core.tests.max.allowed.clock.tick.duration.milliseconds' is not set (default to '20' millisecondss)
   Waiting for 5s...
   ...done
   OK: testTime
   -> Check monotonic time (LLMJVM_IMPL_getCurrentTime, LLMJVM_IMPL_setApplicationTime validation)...
   Waiting for 5s...
   ...done
   OK: testMonotonicTime
   -> Check Java round robin (LLMJVM_IMPL_scheduleRequest validation)...
   For a best result, please disable all the C native tasks except the MicroEJ task.
   Task 3 is waiting for start...
   Task 2 is waiting for start...
   Task 1 is waiting for start...
   Task 0 is waiting for start...
   Starting tasks and wait for 10 seconds...
   Task 2 ends.
   Task 3 ends.
   Task 0 ends.
   Task 1 ends.
   ...done.
   OK: testJavaRoundRobin
   Main thread starts sleeping for 1s..
   WaitMaxTimeThread starts sleeping for `Long.MAX_VALUE` milliseconds
   Main thread woke up!
   OK: testScheduleMaxTime
   -> Check isInReadOnlyMemory (LLBSP_IMPL_isInReadOnlyMemory validation)...
   Test synchronize on literal string
   Test synchronize on class
   Test multiple synchronize
   OK: testIsInReadOnlyMemory
   -> Check FPU (soft/hard FP option)...
   OK: testFPU
   -> Check floating-point arithmetic with NaN...
   -> Check floating-point arithmetic with 0.0 and -0.0...
   -> Check floating-point arithmetic with infinity...
   -> Check floating-point arithmetic with min values...
   -> Check floating-point division by 0.0...
   -> Check floating-point Math functions...
   -> Check integer arithmetic...
   OK: testFloatingPointArithmetic
   -> Check floating-point parser...
   OK: testParseFloatingPoint
   -> Check floating-point formatter...
   OK: testFormatFloatingPoint
   -> Check parsing a string as a double ; in some systems such operations may allocate memory in the C heap (strtod, strtof, malloc implementation)...
   OK: testParseDoubleStringHeap
   Property 'com.microej.core.tests.monotonic.time.check.seconds' is not set (default to '60' seconds)
   -> Check monotonic time consistency for 60 seconds (LLMJVM_IMPL_getCurrentTime)...
   .............................
   OK: testMonotonicTimeIncreases
   -> Check current time clock tick duration (LLMJVM_IMPL_getCurrentTime, LLMJVM_IMPL_getTimeNanos)...
   Property 'com.microej.core.tests.max.allowed.clock.tick.duration.milliseconds' is not set (default to '20' millisecondss)
   Estimated LLMJVM_IMPL_getCurrentTime clock tick is 1 ms.
   Estimated LLMJVM_IMPL_getTimeNanos clock tick is lower than 4000 ns.
   OK: testSystemCurrentTimeClockTick
   -> Check schedule request clock tick duration (LLMJVM_IMPL_scheduleRequest)...
   Property 'com.microej.core.tests.max.allowed.clock.tick.duration.milliseconds' is not set (default to '20' millisecondss)
   Estimated LLMJVM_IMPL_scheduleRequest clock tick is 1 ms.
   OK: testScheduleRequestClockTick
   -> Check SNI native calling convention (ABI)...
   OK: testSniAbi
   PASSED: 15
   MicroEJ END (exit code = 0)

--------------

Tests Description
=================

Print: t_core_print.c
---------------------

An implementation of ``print`` is required by MicroEJ Platform to debug
the Java exceptions. Furthermore this implementation is also required to
check this qualification bundle.

**Configuration**

The default implementation (the one implemented in the ``weak``
functions, see ``u_print.c``) calls ``stdio``\ ’s ``printf`` functions.
Write your own functions if necessary.

**Expected results**

A message is just printed:

::

   ****************************************************************************
   **                      Platform Qualification Core                       **
   **                              version 1.0                               **
   ****************************************************************************
   *           Copyright 2013-2020 MicroEJ Corp. All rights reserved.         *
   * Use of this source code is governed by a BSD-style license               *
   * that can be found with this software.                                    *
   ****************************************************************************

   Print test:
    if this message is displayed, the test is passed!

Timer: t_core_time_base.c
-------------------------

A time counter is required by MicroEJ Platform. This timer must respect
the following rules:

* during MicroEJ Application, this counter must not return to zero
  (return in the past),
* its precision must be around one or ten microseconds (often running
  at 1MHz).

This timer can be the OS timer but most of time the OS timer does not
respect the expected conditions. A hardware timer is often used instead.
Its interrupt should be programmed to occur when the timer exceeds the
half of the counter. Under interrupt, a software counter is updated.
When application asks the time, an addition between this software
counter and the current hardware timer is performed.

This timer is used by the next qualification tests and by the LLMJVM
implementation (see ``LLMJVM_impl.h``, functions
``LLMJVM_IMPL_getCurrentTime`` and ``LLMJVM_IMPL_getTimeNanos``).

This test ensures a timer is implemented but it does not check its
accuracy (tested later).

**Configuration**

The default implementation (the one implemented in the ``weak``
functions, see ``u_time_base.c``) returns always ``0``. Write your own
functions to implement the timer counter.

**Expected results**

No error must be thrown when executing this test:

::

   Time base check:
   .

**Code Review**

In addition to this automatic test, a code review must be done to spot potential 
race conditions that are diffcult to check automatically.

In some implementations, the current time is calculated by adding 2 values:

* a high-precision time with a quick overflow: ``hp_time``
* a low-precision time without any overflow risk: ``lp_time``

Low-precision time is incremented when high-precision time overflows. 
It is done usually in an interrupt or directly by the hardware.
Computing time with an expression similar to ``time = lp_time + hp_time`` can lead 
to a wrong result because this operation is not done atomically.
Moreover, the compiler may reorder the accesses to ``hp_time`` and ``lp_time``.

The right pattern to use is the following one, where ``hp_time`` and ``lp_time``
are both declared **volatile**:

::

   // An interrupt may occur between read of lp_time and hp_time,
   // this interrupt may modify lp_time,
   // so, after accessing hp_time, we must check if lp_time has not been modified.
   do {
       lp_time_local = lp_time;        
       hp_time_local = hp_time;
   } while (lp_time_local != lp_time);
   
   time = lp_time_local + hp_time_local;

The code review consists in verifying the implementations of ``LLMJVM_IMPL_getCurrentTime`` 
and ``LLMJVM_IMPL_getTimeNanos`` to see if they follow the above recommendation.

RAM Tests: t_core_ram.c
-----------------------

This test is useful to check external RAM when it is available on the
hardware. The test performs several read and write actions, with
different patterns. All accesses are aligned on value to write: 8, 16 or
32 bits, like the MicroEJ Platform will use the RAM.

To run, several functions must be implemented. See ``x_ram_checks.h``:

* ``X_RAM_CHECKS_zone_t* X_RAM_CHECKS_get32bitZones(void)``
* ``X_RAM_CHECKS_zone_t* X_RAM_CHECKS_get16bitZones(void)``
* ``X_RAM_CHECKS_zone_t* X_RAM_CHECKS_get8bitZones(void)``
* ``uint8_t X_RAM_CHECKS_get32bitZoneNumber(void)``
* ``uint8_t X_RAM_CHECKS_get16bitZoneNumber(void)``
* ``uint8_t X_RAM_CHECKS_get8bitZoneNumber(void)``

**Configuration**

Some default weak functions are already implemented and return ``NULL``
or ``0``; that means the test will not been performed.

**Expected results**

No error must be thrown when executing this test:

::

   RAM tests:
   .....................

RAM Benchs: t_core_ram.c
------------------------

This test is useful to bench external RAM accesses when it is available
on the hardware. This test only performs some benches. In addition with
previous test, the external RAM timings can be adjusted to obtain the
faster RAM accesses (and without any error!).

**Configuration**

To run, several functions must be implemented. See ``x_ram_checks.h``:

* ``X_RAM_CHECKS_zone_t* X_RAM_CHECKS_get32bitSourceZone(void)``
* ``X_RAM_CHECKS_zone_t* X_RAM_CHECKS_get16bitSourceZone(void)``
* ``X_RAM_CHECKS_zone_t* X_RAM_CHECKS_get8bitSourceZone(void)``

These *sources* can target a region in internal flash, internal RAM or
any other regions.

**Expected results**

::

   RAM speed benchmark:
   .RAM speed average read access (according to your configuration file 8/16/32 bits) : 51.180522MBytes/s
   .RAM speed average write access (according to your configuration file 8/16/32 bits) : 131.289164 MBytes/s
   .RAM speed average transfert access (according to your configuration file 8/16/32 bits) : 86.466471MBytes/s

**Notes**

These results can be sent to MicroEJ in order to compare the BSP
implementation with all others MicroEJ Platforms.

Coremark: t_core_core_benchmark.c
---------------------------------

EEMBC Coremark allows to compare CPU and BSP configurations. Refer to
EEMBC Coremark website (http://www.eembc.org/coremark/index.php) to have
more information about results. The Github repository containing the sources of Coremark (https://github.com/eembc/coremark.git) is linked as a submodule of this repository.



**Configuration**

To run this test:

* Create ``core_portme.h`` and ``core_portme.h`` files to port EEMBC CoreMark.
* Insert the directive line :code:`#define main core_main` into the ``core_portme.h``.
* Implement ``X_CORE_BENCHMARK_run(void)`` from ``x_core_benchmark.h``.

**Expected results**

::

   Core/Flash benchmark:
   .2K performance run parameters for coremark.
   CoreMark Size    : 666
   Total ticks      : 12052657
   Total time (secs): 12.052657
   Iterations/Sec   : 497.815544
   Iterations       : 6000
   Compiler version : ARMCC V5.06 update 4 (build 422)
   Compiler flags   : -c --cpu Cortex-M4.fp -D__MICROLIB -g -O3 -Otime --apcs=interwork --split_sections -D__UVISION_VERSION="523" -D_RTE_ -DSTM32L496xx -DUSE_HAL_DRIVER -DSTM32L496xx
   Memory location  : STATIC
   seedcrc          : 0xe9f5
   [0]crclist       : 0xe714
   [0]crcmatrix     : 0x1fd7
   [0]crcstate      : 0x8e3a
   [0]crcfinal      : 0xa14c
   Correct operation validated. See readme.txt for run and reporting rules.
   CoreMark 1.0 : 497.815544 / ARMCC V5.06 update 4 (build 422) -c --cpu Cortex-M4.fp -D__MICROLIB -g -O3 -Otime --apcs=interwork --split_sections -D__UVISION_VERSION="523" -D_RTE_ -DSTM32L496xx -DUSE_HAL_DRIVER -DSTM32L496xx / STATIC

MicroEJ Core Validation
-----------------------

This MicroEJ Application validates the LLAPI ``LLMJVM_impl.h``
implementation executing several tests. Two first tests check the time,
and require an human check to be sure the time is correct.

**Configuration**

In the MicroEJ SDK, import the MicroEJ project `java-testsuite-runner-core <./java-testsuite-runner-core/>`_ from the folder ``tests/core``.
Follow the MicroEJ Core Validation `README <./java-testsuite-runner-core/README.rst>`_ to build and link this MicroEJ Application against the MicroEJ Platform to qualify.

**Expected results**

No error must be thrown when executing this test. A typical execution trace is described in the MicroEJ Core Validation `README <./java-testsuite-runner-core/README.rst>`_
(the visible clock accuracy must be compared manually with an external clock).


