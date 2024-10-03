..
    Copyright 2023-2024 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.
..

*************
VG Test Suite
*************

This folder contains a ready-to-use project for testing `MicroVG <https://docs.microej.com/en/latest/VEEPortingGuide/vg.html>`__ implementations on a device.
This Test Suite will test vector drawing capabilites.

Specifications
--------------

- Tested Foundation Library: `MicroVG <https://repository.microej.com/modules/ej/api/microvg/>`__
- Test Suite Module: `com.microej.pack.vg#vg-testsuite <https://repository.microej.com/modules/com/microej/pack/vg/vg-testsuite/>`__

Set the VG Test Suite module version in the `module.ivy
<java-testsuite-runner-vg/module.ivy>`__ to match the pack version of the VEE Port
tested.

Please refer to `VEE Port Qualification Test Suite Versioning
<https://docs.microej.com/en/latest/VEEPortingGuide/veePortQualification.html#test-suite-versioning>`__
to determine the MicroVG Test Suite module version.

Requirements
-------------

See VEE Port Test Suites `documentation <../README.rst>`__.

Relationship
------------

The test suite evolves as the VG Pack evolves: bug fixes, new features, etc.
A test suite is, therefore, compatible with a given range of VG Packs (cf VG Pack changelog: https://docs.microej.com/en/latest/VEEPortingGuide/vgChangeLog.html).
The following table shows the relationship between the different versions of the test suite and the associated VG Packs.
(note: Each VG Pack implements a version of MicroVG; cf VG Pack release notes: https://docs.microej.com/en/latest/VEEPortingGuide/vgReleaseNotes.html).

The table indicates:

* the version of the project ``java-testsuite-runner-vg``,
* the version of the test suite library fetched by the project ``java-testsuite-runner-vg``,
* the compatible VG Packs to run the tests of the test suite,
* the minimum version of the MicroVG API required by the test suite.

+-----------------+-------------------+---------------+-------------------+
| Project version | TestSuite version | VG Pack Range | MicroVG API Range |
+=================+===================+===============+===================+
| 1.3.0           | 3.0.0             | [1.6.0-2.0.0[ | [1.4.0-2.0.0[     |
+-----------------+-------------------+---------------+-------------------+
|                 | 2.7.0             | [1.5.1-2.0.0[ | [1.4.0-2.0.0[     |
+-----------------+-------------------+---------------+-------------------+
| 1.2.0           | 2.6.0             | [1.5.0-2.0.0[ | [1.4.0-2.0.0[     |
+-----------------+-------------------+---------------+-------------------+
| 1.1.0           | 2.5.0             | [1.4.2-2.0.0[ | [1.4.0-2.0.0[     |
+-----------------+-------------------+---------------+-------------------+
| 1.0.0           | 2.2.0             | [1.3.0-2.0.0[ | [1.3.0-2.0.0[     |
+-----------------+-------------------+---------------+-------------------+

Skip Tests
----------

Some tests might be skipped according to:

* The VEE Port: Some features are tested (like external resources: images and fonts stored outside the CPU address range). If the VEE Port does not provide an external resource loader, some tests must be skipped.
* The target, embedded or simulator. The simulator can skip some tests (approximation issues, useless feature like external resources management, known issues).
* The GPU: The MicroVG testsuite checks all the MicroVG specification. A GPU may not support some drawings, for instance the usage of some blending modes. By consequence, the associated tests must be skipped.

The MicroVG testsuite provides dedicated settings files for:

* the Vivante VGLite GPU
* the Think Silicon NemaVG GPU
* the MicroEJ Simulator

These files allow to skip the irrelevant tests according to the target.
The content of a file must be copied into the ``config.properties`` file.
These files are available in the MicroVG testsuite JAR file, in the folder ``settings``.

This is an example of property to skip the test ``TestPath.testVeryLongDynamicPath()``:

.. code-block:: jproperties

	microej.testsuite.properties.microej.java.property.tests.TestPath.testVeryLongDynamicPath.skip=true

Usage
-----

- In the SDK, import the ``java-testsuite-runner-vg`` project in your workspace.
- Follow the configuration and execution steps described in VEE Port Test Suites `documentation <../README.rst>`__.

Test Suite Source Code Navigation
---------------------------------

See VEE Port Test Suites `documentation <../README.rst>`__.

Troubleshooting
---------------

See VEE Port Test Suites `documentation <../README.rst>`__.
