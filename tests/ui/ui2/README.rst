.. ReStructuredText
.. Copyright 2019-2021 MicroEJ Corp.  MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.

***********************************
Graphical User Interface Test Suite
***********************************

Overview
========

This folder is a part of a project which gathers the Platform Qualification Tools.
It contains sources and projects to check drivers and implementation of LLAPI ``LLDisplay``.

.. note:: 

   These tests only concern the MicroEJ Platforms made against the MicroEJ UI Packs [6.0.0-13.0.0[ (13.0.0 excluded).
   For the newer MicroEJ UI packs, see `UI3 Readme <../ui3/README.rst>`_ .

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

-  Follow the main readme file
-  Follow the *CORE* readme file

Quick Start
===========

Configuration
-------------

1. Add all files of these folders as source files:

   -  ``tests/ui/c/src``

2. Add these folders as include folders:

   -  ``tests/ui/c/inc``

3. Implement all functions defined in these files:

   -  ``x_impl_config.c``: see `Tests Description`_

4. Add a call to the function ``T_UI_main()`` just before the call to
   ``microej_main()``.
5. In the MicroEJ SDK, import the MicroEJ project ``microej-core-validation`` from the folder ``tests/core/java``.
6. Build this MicroEJ Application against the MicroEJ Platform to qualify.
7. Build the BSP and link it with the MicroEJ Platform runtime library and MicroEJ Application.

Expected Results
----------------

::

   Board init finished.
   ..LCD width = 480
   LCD height = 272
   .LCD BPP = 16
   .LCD back buffer is [0xa0000000, 0xa003fc00[
   Try to write and verify something in this buffer...
   .LCD back buffer is [0xa003fc00, 0xa007f800[
   Try to write and verify something in this buffer...
   .Refresh LCD content with black and screen data. Ensures about tearing effect..Retrieve the LCD framerate...
   Retrieve the maximal drawing time (this will take several seconds)...

   LCD framerate time is 17.528000 ms (57.051579 Hz)
   The copy time is 7.708000 ms
   To have an animation at 57.051579 Hz, the drawing time cannot be higher than 9.820000 ms.
   To have an animation at 28.525789 Hz, the drawing time cannot be higher than 27.348000 ms.
   To have an animation at 19.017193 Hz, the drawing time cannot be higher than 44.875999 ms.

   OK (7 tests)

--------------

Tests Description
=================

API: t_ui_api.c
---------------

This test checks the ``LLDisplay`` implementation API. It ensures
invalid values are not returned and the coherence between them.

A sum-up of LCD is printed (width, height, bpp, back buffer address).
Then the test tries to write and read some values in back buffer. In
case of back buffer changes after each ``flush``, another write and read
sequence is performed in new back buffer.

**Configuration**

``LLDisplay`` implementation is written to target a LCD with a specific
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

When possible, the LLDisplay implementation should synchronize the
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

1. The LLDisplay implementation of ``LLDISPLAY_IMPL_flush`` prepare the
   copy of data from back buffer to display buffer (setup a DMA for
   instance).
2. It program the LCD tearing interrupt.
3. During the LCD tearing interrupt, it starts the copy (start the DMA
   or unlock a copy task).
4. During this time, a call to ``LLDISPLAY_IMPL_synchronize`` is
   performed. The implementation has to lock the caller until the copy
   is done.

When the tearing signal is used, the aim of
``LLDISPLAY_IMPL_synchronize`` consists to wait the tearing signal plus
the end of copy. To determinate only the copy time, the test simulates a
drawing time just before calling ``LLDISPLAY_IMPL_flush`` function. This
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
