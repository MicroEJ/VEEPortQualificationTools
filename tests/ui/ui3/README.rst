.. ReStructuredText
.. Copyright 2021 MicroEJ Corp.  MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.

***********************************
Graphical User Interface Test Suite
***********************************

Overview
========

This folder is a part of a project which gathers the Platform Qualification Tools.
It contains sources and projects to check drivers and implementation of LLAPI ``LLUI_DISPLAY_IMPL``.

.. note:: 

   These tests only concern the MicroEJ Platforms made against the MicroEJ UI Packs 13.0.0 and higher.
   For the older MicroEJ UI packs, see `UI2 Readme <../ui2/README.rst>`_.

All tests can be run in one step: all tests will be executed one by one
and are run in a specific order, *next one* expects *previous one* is
passed.

For each test, its configuration and its results are described in a
dedicated section. See `Quick Start`_ section which resume how to configure the
tests, how to launch them and the expected results.

Additionally, the `Tool-Java-Touch <https://github.com/MicroEJ/Tool-Java-Touch>`_ project
allows to test the correct behavior of MicroUI in a Java application. 

Dependencies
============

- Follow the `main Readme <../../../README.rst>`_.
- Follow the `CORE Readme <../../core/README.rst>`_.

Quick Start
===========

Configuration
-------------

#. Follow the configuration of the `CORE Test Suite <../../core/README.rst>`_.

#. Add all files of these folders as source files:

   -  ``tests/ui/ui3/c/src``

#. Add these folders as include folders:

   -  ``tests/ui/ui3/c/inc``

#. Implement all functions defined in these files:

   -  ``x_impl_config.c``: see `Tests Description`_

#. Add a call to the function ``T_UI_main()`` just before the call to
   ``microej_main()``.
#. In the MicroEJ SDK, import the MicroEJ project ``microej-ui-validation`` from the folder ``tests/ui/ui3/java``.
#. Build this MicroEJ Application against the MicroEJ Platform to qualify.
#. Build the BSP and link it with the MicroEJ Platform runtime library and MicroEJ Application.

Flush Tests
-----------

There are some limitations on tests that are using ``LLUI_DISPLAY_IMPL_flush`` API. By default these tests are
disabled. 

See comment of define ``ENABLE_FLUSH_TESTS`` in ``t_ui_main.h``.

Expected Results
----------------

Without Flush tests:

::

   ..LCD width = 480
   LCD height = 272
   .LCD memory width = 480
   LCD memory height = 272
   .LCD BPP = 16
   .LCD back buffer is [0xc003fc00, 0xc007f800[
   Try to write and verify something in this buffer...
   ..
   OK (7 tests)


With Flush tests:

::

   ..LCD width = 480
   LCD height = 272
   .LCD memory width = 480
   LCD memory height = 272
   .LCD BPP = 16
   .LCD back buffer is [0xc003fc00, 0xc007f800[
   Try to write and verify something in this buffer...
   ...Refresh the LCD content with black and white data. Ensure about the tearing effect..Retrieve the LCD framerate...
   Retrieve the maximal drawing time (this will take several seconds)...
   
   LCD framerate time is 17.528000 ms (57.051579 Hz)
   The copy time is 7.708000 ms
   To have an animation at 57.051579 Hz, the drawing time cannot be higher than 9.820000 ms.
   To have an animation at 28.525789 Hz, the drawing time cannot be higher than 27.348000 ms.
   To have an animation at 19.017193 Hz, the drawing time cannot be higher than 44.875999 ms.
   
   OK (9 tests)
   

Tests Description
=================

API: t_ui_api.c
---------------

This test checks the ``LLUI_DISPLAY_IMPL`` implementation API. It ensures
invalid values are not returned and the coherence between them.

A sum-up of LCD is printed (width, height, bpp, back buffer address).
Then the test tries to write and read some values in back buffer. In
case of back buffer changes after each ``flush``, another write and read
sequence is performed in new back buffer.

**Configuration**

``LLUI_DISPLAY_IMPL`` implementation is written to target a LCD with a specific
BPP (bits-per-pixel). This value is also available in MicroEJ Platform
Configuration project in order to build a MicroEJ Platform with the corresponded
graphical engine (see ``display/display.properties``). The UI
qualification bunble tests require this value. So a function must be
implemented to run UI tests.

The default implementation (the one implemented in the ``weak``
function, see ``x_impl_config.c``) returns the invalid value ``0``. If
the weak function is not overridden, the tests which require this value
throw an assert. See ``x_ui_config.h`` for a mapping between the graphical
engine and the value used by the BSP. 

**Expected results**

No error must be thrown when executing this test:

::

   Board init finished.
   ..LCD width = 480
   LCD height = 272
   .LCD BPP = 16
   .LCD back buffer is [0xa0000000, 0xa003fc00[
   Try to write and verify something in this buffer...
   .LCD back buffer is [0xa003fc00, 0xa007f800[
   Try to write and verify something in this buffer...
   .

Tearing: t_ui_tearing.c
-----------------------

When possible, the LLUI_DISPLAY_IMPL implementation should synchronize the
``flush`` with the LCD tearing signal. This signal tells to the BSP the
LCD has finished to refresh itself with last available frame buffer
data. At this moment, the frame buffer data can be updated (a copy from
back buffer to frame buffer can be performed) or the frame buffer
address can be updated (back buffer becomes frame buffer and vice-versa;
a copy from new frame buffer to back buffer is required, see developer
guide).

This test performs several ``flush`` with black and white screens during
10 sec. When the tearing signal is not used, you can see on display
several rectangles: the frame buffer is updated during the LCD refresh
period. So the LCD starts refreshing itself with old data and then with
new data.

When the tearing signal is used correctly, full screen is updated at
same time.

**Configuration**

Just run the test.

**Expected results**

Check display content: no rectangle must appear when tearing signal is
used.

::

   Refresh LCD content with black and screen data. Ensures about tearing effect..

**Notes**

When the time to update frame buffer data is higher than the LCD refresh
rate, you can see rectangles even if LCD driver is using the LCD tearing
signal.

Framerate: t_ui_framerate.c
---------------------------

This test determinates the maximum time a drawing can take to respect a
given LCD framerate. The LCD framerate is cadenced to the time to
perform a ``flush`` and to wait the end of this flush. The flush consits
in several steps:

1. The LLUI_DISPLAY_IMPL implementation of ``LLUI_DISPLAY_IMPL_flush`` prepare the
   copy of data from back buffer to display buffer (setup a DMA for
   instance).
2. It program the LCD tearing interrupt.
3. During the LCD tearing interrupt, it starts the copy (start the DMA
   or unlock a copy task).
4. To notify the end of flush, the LCD driver has to call ``T_UI_LCD_flush_done``.

When the tearing signal is used, the call to
``T_UI_LCD_flush_done`` means the tearing signal and the end of copy have 
been reached. To determinate only the copy time, the test simulates a
drawing time just before calling ``LLUI_DISPLAY_IMPL_flush`` function. This
time is increased until the time to wait the tearing signal is null: the
drawing time + the copy time fit the LCD refresh rate.

**Configuration**

Just run the test.

**Expected results**

The test will take several seconds to determinate the drawing time.

::

   Retrieve the LCD framerate...
   Retrieve the maximal drawing time (this will take several seconds)...

   LCD framerate time is 17.528000 ms (57.051579 Hz)
   The copy time is 7.708000 ms
   To have an animation at 57.051579 Hz, the drawing time cannot be higher than 9.820000 ms.
   To have an animation at 28.525789 Hz, the drawing time cannot be higher than 27.348000 ms.
   To have an animation at 19.017193 Hz, the drawing time cannot be higher than 44.875999 ms.

This report shows the LCD framerate (in ms and Hz), the time to perform
the copy from back buffer to frame buffer and three drawing times: one
for LCD nominal refresh rate, one for this refresh rate divided by two
and one this refresh rate divided by three.

**Notes**

These results can be sent to MicroEJ in order to compare the BSP
implementation with all others MicroEJ Platforms.
