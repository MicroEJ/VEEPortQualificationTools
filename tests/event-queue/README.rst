..
    Copyright 2023-2024 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.
..

**********************
Event Queue Test Suite
**********************

This folder contains a ready-to-use project for testing `Event Queue <https://docs.microej.com/en/latest/VEEPortingGuide/packEventQueue.html>`_ implementations on a device.
This Test Suite will create some listeners and send basic/extended events with different primitive types of data.

Specifications
==============

- Tested Foundation Library: `Event Queue <https://forge.microej.com/artifactory/microej-developer-repository-release/ej/api/event/>`_
- Test Suite Module: `ej.api.event#event-testsuite <https://forge.microej.com/artifactory/microej-developer-repository-release/com/microej/pack/event/event-testsuite//>`_

Set the Event Queue Test Suite module version in the `module.ivy
<java-testsuite-runner-event-queue/module.ivy>`_.

Please refer to `VEE Port Qualification Test Suite Versioning
<https://docs.microej.com/en/latest/VEEPortingGuide/veePortQualification.html#test-suite-versioning>`_
to determine the Event Queue Test Suite module version.

Requirements
============

- Read VEE Port Test Suites `documentation <../README.rst>`_.
- Read External resource loader Test Suites `documentation <../ext-res-loader/README.rst>`_.

Usage
=====

- In your BSP project, add all files of ``c/src`` folder as source files:
- In your BSP project, add ``c/inc`` folder as include paths.
- In the SDK, import the ``java-testsuite-runner-event-queue`` project in your workspace.
- Follow the configuration and execution steps described in VEE Port Test Suites `documentation <../README.rst>`_.

Test Suite Source Code Navigation
=================================

- See VEE Port Test Suites `documentation <../README.rst>`_.

Troubleshooting
===============

- This testsuite does not work automatically in Simulation. You have to manually stop the Application by closing the Front panel.
- See Vee Port Test Suites `documentation <../README.rst>`_.
