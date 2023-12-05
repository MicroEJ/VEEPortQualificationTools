.. image:: https://shields.microej.com/endpoint?url=https://repository.microej.com/packages/badges/sdk_5.4.json
   :alt: sdk_5.4 badge
   :align: left

.. image:: https://shields.microej.com/endpoint?url=https://repository.microej.com/packages/badges/arch_7.14.json
   :alt: arch_7.14 badge
   :align: left

.. image:: https://shields.microej.com/endpoint?url=https://repository.microej.com/packages/badges/arch_8.0.json
   :alt: arch_8.0 badge
   :align: left
..
   Copyright 2019-2023 MicroEJ Corp. All rights reserved.
   Use of this source code is governed by a BSD-style license that can be found with this software.


Description
===========

The Platform Qualification Tools (PQT) project provides the tools required to validate each component of a MicroEJ Platform.
After porting or adding a feature to a MicroEJ Platform, it is necessary to validate its integration.

Clone this repository with ``git clone --recursive https://github.com/MicroEJ/PlatformQualificationTools``.

Test Suites Available
=====================

Core Engine Test Suite
----------------------

The CORE Test Suite contains a C Test Suite and a Java Test Suite. It is the most basic Test Suite to run.
It ensures MicroEJ Application will run correctly.

All other Test Suites assume the CORE Test Suite is validated.

See `CORE Readme <tests/core/README.rst>`_

Multi-Sandbox Test Suite
------------------------

The Multi-Sandbox Test Suite contains a C Test Suite. It ensures MicroEJ Multi-Sandbox features install/uninstall flow will run correctly.

See `Multi-Sandbox Readme <tests/llkernel/README.rst>`_

Graphical User Interface Test Suite
-----------------------------------

The UI Test Suite is a Java Test Suite. It tests the implementation of the ``LLUI*`` API and the tearing signal usage.
It also provides indication about the minimum draw time allowed to display animations at a given framerate.

See `UI Readme <tests/ui/README.rst>`_

Vector Graphics Test Suite
--------------------------

The VG Test Suite is a Java Test Suite. It checks the implementation of the ``LLVG*`` API over a vector GPU.

See `VG Readme <tests/vg/README.rst>`_

Filesystem Test Suite
---------------------

The FS Test Suite is a Java Test Suite. It checks the implementation of the ``LLFS*`` APIs over a C File System library.

See `FS Readme <tests/fs/README.rst>`_

Network Core Engine Test Suite
------------------------------

The NET Test Suite is a Java Test Suite. It checks the implementation of the ``LLNET`` APIs.

See `Network Core Engine Readme <tests/net/README.rst>`_

SSL Test Suite
--------------

The SSL Test Suite is a Java Test Suite. It checks the implementation of the ``LLNET_SSL`` APIs.

See `SSL Readme <tests/ssl/README.rst>`_

SECURITY Test Suite
--------------

The SECURITY Test Suite is a Java Test Suite.

See `SECURITY Readme <tests/security/README.rst>`_

WatchdogTimer Test Suite
-------------------------

The WatchdogTimer Test Suite is a Java Test Suite. It checks the implementation of the ``LLWATCHDOG_TIMER`` APIs.

See `WatchdogTimer Readme <tests/watchdog-timer/README.rst>`_

ECOM-WIFI Test Suite
--------------------

The ECOM-WIFI Test Suite is a Java Test Suite.

See `ECOM-WIFI Readme <tests/ecom-wifi/README.rst>`_

Event Queue Test Suite
--------------------

The Event Queue Test Suite is a Java Test Suite.

See `Event Queue Readme <tests/event-queue/README.rst>`_

External Resource Loader Test Suite
-----------------------------------

The External Resource Loader Test Suite is a Java Test Suite.

See `External Resource Loader Readme <tests/ext-res-loader/README.rst>`_

Platform Qualification Tools Overview
=====================================

The Platform Qualification Tools (PQT) contains:

- a ``framework/`` folder with scripts and frameworks used by the tests
- a ``tests/`` folder with one sub-folder per Test Suite (e.g. ``tests/core/`` for the CORE Test Suite, etc.)

Each Test Suite sub-folder contains a ``README.rst`` that explain how to use the Test Suite in details.

The following sections give an overview of the Platform Qualification Tools (PQT).

Framework
---------

The ``framework/`` folder contains the infrastructure required to build and run the tests.

C infrastructure
----------------

The ``framework/c/`` folders contains the following:

- Embedded Unit (embUnit) is a unit testing framework used for C tests.
- CoreMark is a processor benchmark used by the CORE Test Suite.
- utils provides several utilities used by various C tests

Platform Configuration Additions
--------------------------------

The ``framework/platform/content`` folder contains the MicroEJ Platform Configuration Additions.
See the `Platform Configuration Additions README <framework/platform/README.rst>`_ for more information.
For licenses management, please refer to `License <https://docs.microej.com/en/latest/overview/licenses.html>`_ .

Build and Run Scripts Examples
------------------------------

The ``framework/platform/scripts`` folder contains Build and Run Scripts examples for several third-party toolchains.

See the `Build and Run Scripts Examples <framework/platform/scripts/README.rst>`_ for more information.

Test Suites
-----------

The Platform Qualification Tools (PQT) provides two kinds of Test Suite:

- C Test Suite that must be added to the BSP
- Java Test Suite that are launched as standard MicroEJ Application

A Test Suite validates a particular component of a MicroEJ Platform.
The CORE Test Suite is applicable to every MicroEJ Platform.
The other Test Suites depends on the capabilities provided by the MicroEJ Platform to validate.

A detailed explanation how to use each Test Suite is provided in the ``README.rst`` present in each sub-folder.
For example, for the CORE Test Suite, refer to the `CORE Readme <tests/core/README.rst>`_.

C Test Suites
-------------

The C Test Suites validate that the hardware and RTOS (if applicable) are properly integrated in the BSP.

The C Test Suites uses Embunit framework. They have to be launched just
before MicroEJ Application (just before the call to ``microjvm_main()``).
At this moment, the BSP is fully initialized and the OS is started.

The C Test Suites perform some basic checks which ensures MicroEJ Application
will run. Unless specified otherwise, C Test Suites are linked with a MicroEJ Application
(``microejapp.o``) and a MicroEJ runtime library (``microejruntime.a``).

The C Test Suites often require some additional data (some specific functions have to
be implemented in addition of LLAPI implementation functions).

Java Test Suites
----------------

The Java Test Suites validate the Foundation Libraries integration.

The Java Test Suites verify the integration of the MicroEJ Platform over the
BSP. No specific unit test framework is used, each test describes how it
works.
