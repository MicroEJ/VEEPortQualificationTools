..
    Copyright 2024 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.
..

****************
Audio Test Suite
****************

This folder contains a ready-to-use project for testing `Audio <https://docs.microej.com/en/latest/VEEPortingGuide/audio.html>`_ implementations on a device.
This Test Suite will test audio recording and audio playing.

Specifications
--------------

- Tested Foundation Library: `Audio <https://repository.microej.com/modules/ej/api/audio/>`_
- Test Suite Module: `com.microej.pack.audio#audio-testsuite <https://repository.microej.com/modules/com/microej/pack/audio/audio-testsuite/>`_

Set the Audio Test Suite module version in the `module.ivy
<java-testsuite-runner-audio/module.ivy>`_ to match the pack version of the tested VEE Port.

Please refer to `VEE Port Qualification Test Suite Versioning
<https://docs.microej.com/en/latest/VEEPortingGuide/veePortQualification.html#test-suite-versioning>`_
to determine the Audio Test Suite module version.

Requirements
-------------

See VEE Port Test Suites `documentation <../README.rst>`_.

Usage
-----

- In the SDK, import the ``java-testsuite-runner-audio`` project in your workspace.
- Follow the configuration and execution steps described in VEE Port Test Suites `documentation <../README.rst>`_.
- If the VEE Port does not support both audio recording and audio playback, change  the ``test.run.includes.pattern`` property in the ``config.properties`` file.

Test Suite Source Code Navigation
---------------------------------

See VEE Port Test Suites `documentation <../README.rst>`_.

Troubleshooting
---------------

See VEE Port Test Suites `documentation <../README.rst>`_.
