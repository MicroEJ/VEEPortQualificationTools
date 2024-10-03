..
    Copyright 2020-2024 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.
..

*********************
Filesystem Test Suite
*********************

This folder contains a ready-to-use project for testing `File System <https://docs.microej.com/en/latest/VEEPortingGuide/fs.html>`_ implementations on a device.
This Test Suite will typically test file and directory creation, access permissions, and file content read/write...

Specifications
--------------

- Tested Foundation Library: `FS <https://repository.microej.com/modules/ej/api/fs/>`_
- Test Suite Module: `com.microej.pack.fs#fs-testsuite <https://repository.microej.com/modules/com/microej/pack/fs/fs-testsuite/>`_

Set the FS Test Suite module version in the `module.ivy
<java-testsuite-runner-fs/module.ivy>`_ to match the pack version of the tested VEE Port.

Please refer to `VEE Port Qualification Test Suite Versioning
<https://docs.microej.com/en/latest/VEEPortingGuide/veePortQualification.html#test-suite-versioning>`_
to determine the FS Test Suite module version.

Requirements
-------------

- See VEE Port Test Suites `documentation <../README.rst>`_.

Usage
-----

- In the SDK, import the ``java-testsuite-runner-fs`` project in your workspace.
- Follow the configuration and execution steps described in VEE Port Test Suites `documentation <../README.rst>`_.

Test Suite Source Code Navigation
---------------------------------

- See VEE Port Test Suites `documentation <../README.rst>`_.

Troubleshooting
---------------

See VEE Port Test Suites `documentation <../README.rst>`_.
