..
    Copyright 2021-2024 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.

MicroEJ UI Validation
=====================

Overview
--------

This project contains test cases aimed at validating the correct runtime execution 
of UI Pack on a VEE Port connected to a Board Support Package (BSP).
 
Tests are written as JUnit test cases, thus the main entry point is automatically generated by MicroEJ SDK.

Tests can be launched:

-  as a standard Application by using a local launcher, see `Launcher Mode`_.
-  as a VEE Port Test Suite by building the module, see `VEE Port Test Suite Mode`_.

Requirements
------------

-  MicroEJ SDK version ``5.1.0`` (included in MicroEJ SDK dist. ``19.05``).
-  VEE Port built from a MicroEJ UI Pack version ``14.0.0`` or higher.
-  See VEE Port Test Suites `documentation <../../../README.rst>`_.

Relationship
------------

The test suite evolves as the UI Pack evolves: bug fixes, new features, etc. 
A test suite is, therefore, compatible with a given range of UI Packs (cf UI Pack changelog: https://docs.microej.com/en/latest/VEEPortingGuide/uiChangeLog.html). 
The following table shows the relationship between the different versions of the test suite and the associated UI Packs. 
(note: Each UI Pack implements a version of MicroUI; cf UI Pack release notes: https://docs.microej.com/en/latest/VEEPortingGuide/uiReleaseNotes.html). 

The table indicates:

* the version of the project ``java-testsuite-runner-ui3``,
* the version of the test suite library fetched by the project ``java-testsuite-runner-ui3``,
* the compatible UI Packs to run the tests of the test suite,
* the minimum version of the MicroUI API required by the test suite. 

+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+
| Project version | TestSuite version | UI Pack Range   | MicroUI API Range | Testsuite changes                                                      |
+=================+===================+=================+===================+========================================================================+
| 1.7.0           | 1.7.0             | [14.0.0-15.0.0[ | [3.5.0-4.0.0[     | Add Buffer Refresh Strategies tests 									 |
+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+
| 1.4.0           | 1.4.0             | [13.7.0-14.0.0[ | [3.0.3-4.0.0[     | Add image formats with premultiplied alpha values                      |
+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+
| [1.3.0-1.3.1]   | 1.3.0             | [13.4.1-14.0.0[ | [3.0.3-4.0.0[     | Allow setting the image heap size according to the display buffer size |
+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+
| 1.2.0           | 1.2.0             | [13.4.1-14.0.0[ | [3.0.3-4.0.0[     | Add tests for circles and ellipses                                     |
+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+
| 1.1.0           | 1.1.0             | [13.0.0-14.0.0[ | [3.0.3-4.0.0[     | Add tests for GPU ports                                                |
+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+
| 1.0.0           | 1.0.0             | [13.0.0-14.0.0[ | [3.0.3-4.0.0[     | Initial version                                                        |
+-----------------+-------------------+-----------------+-------------------+------------------------------------------------------------------------+

Usage
-----

Launcher Mode
~~~~~~~~~~~~~

In MicroEJ SDK,

-  Select ``Run > Run Configurations...``. A launcher named
   ``java-testsuite-runner-ui3`` should be available under
   ``MicroEJ Application``.
   
-  In ``Execution`` tab, select the target VEE Port.

-  Click on ``Run`` button to compile the MicroEJ Application.

-  Link the BSP project with the MicroEJ Application (``microejapp.o``), 
   the VEE Port runtime (``microejruntime.a``) and the VEE Port header files (``*.h``).

-  See below for an output example

::

    *****************************************************************************************************
    *                                  MicroEJ UI Validation - 1.7.0                                    *
    *****************************************************************************************************
    * Copyright 2021-2024 MicroEJ Corp. All rights reserved.                                            *
    * Use of this source code is governed by a BSD-style license that can be found with this software.  *
    *****************************************************************************************************
    
    -> Check LCD tearing: full screen (LLUI_DISPLAY_IMPL_flush validation)...
    Property 'com.microej.ui.tests.clock.seconds' is not set (default to '10' second(s))
    OK: testTearingFullScreen
    -> Check LCD tearing: black band (LLUI_DISPLAY_IMPL_flush validation)...
    Property 'com.microej.ui.tests.clock.seconds' is not set (default to '10' second(s))
    OK: testTearingVerticalBand
    Property 'com.microej.ui.tests.flush.tolerance.us' is not set (default to '200' us)
    LCD framerate time is 17528 us (57.051579 Hz)
    Retrieve the maximal drawing time (this will take several seconds)...
    The flush time is 7.708000 us
    To have an animation at 57.051579 Hz, the drawing time cannot be higher than 9.820000 ms.
    To have an animation at 28.525789 Hz, the drawing time cannot be higher than 27.348000 ms.
    To have an animation at 19.017193 Hz, the drawing time cannot be higher than 44.875999 ms.
    OK: testDrawingTime
    OK: testBackBufferRestore
    flush time (several iterations): 0
    wait flush time (several iterations): 295
    OK: testFlushTime
    PASSED: 5

VEE Port Test Suite Mode
~~~~~~~~~~~~~~~~~~~~~~~~

-  In MicroEJ SDK, import the ``java-testsuite-runner-ui3`` project in your workspace.

-  Follow the configuration and execution steps described in VEE Port Test Suites `documentation <../../../README.rst>`_.

Tests Suite Description
-----------------------

All tests can be run in one step: all tests will be executed one by one
and are run in a specific order, *next one* expects *previous one* is
passed.

Tearing
~~~~~~~

A tearing effect (flickering) visible on LCD indicates a synchronization issue with
the LCD tearing signal (TE).

* "Full screen" test toggles black and white screens. If the flush job is properly synchronized and quite fast, the LCD is gray. The LCD being cut in multiple parts indicates a synchronization issue of the flush job.

* "Black band" test moves a black band on a white background. The band being cut in multiple parts indicates a synchronization issue of the flush job.

Drawing Time
~~~~~~~~~~~~

This test is useful when the implementation of ``LLUI_DISPLAY_IMPL_flush`` uses the  `SWITCH mode <https://docs.microej.com/en/latest/PlatformDeveloperGuide/uiDisplay.html#switch>`_.
"Drawing time" test determinates the maximum drawing time (in milliseconds) for a given
framerate. The possible framerates depend on the LCD and on the post-flush copy step. When the
drawing time exceeds the maximum drawing time, the framerate is divided by two when the flush
job is synchronized on LCD tearing signal.

Flush Time
~~~~~~~~~~

The implementation of the function ``LLUI_DISPLAY_IMPL_flush`` must be as fast as possible: it is not a blocking function (see function specification).
The implementation has to launch a third-party process (software task or hardware process) to perform the operation and returns.
Once the third-party process has finished, the callback has to call the function ``LLUI_DISPLAY_flushDone``.

This test checks that the implementation of ``LLUI_DISPLAY_IMPL_flush`` is not a blocking function.

Dependencies
------------

*All dependencies are retrieved transitively by MicroEJ Module Manager*.

Source
------

N/A

Restrictions
------------

None.
