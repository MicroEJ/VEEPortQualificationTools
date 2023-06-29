..
    Copyright 2023 MicroEJ Corp. All rights reserved.
    Use of this source code is governed by a BSD-style license that can be found with this software.
..

************************************
External resource loader Test Suite
************************************

This folder contains a ready-to-use project for testing `External resource loader <https://docs.microej.com/en/latest/VEEPortingGuide/externalResourceLoader.html>`_ implementations on a device.
This Test Suite will typically test the ``InputStream`` used with an external resource.

Specifications
--------------

- Tested Foundation Library with external resource: `InputStream <https://repository.microej.com/javadoc/microej_5.x/foundation/index.html?ej/sni/NativeException.html>`_
- Test Suite Module: `com.microej.pack.external-resource#external-resource-testsuite <https://repository.microej.com/modules/com/microej/pack/external-resource/external-resource-testsuite/>`_

Set the External resource loader Test Suite module version in the `module.ivy
<java-testsuite-runner-ext-res-loader/module.ivy>`_ to match the pack version of the VEE Port
tested.

Please refer to `Platform Qualification Test Suite Versioning
<https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformQualification.html#test-suite-versioning>`_
to determine the External resource loader Test Suite module version.

Requirements
-------------

- Read VEE Port Test Suites `documentation <../README.rst>`_.
- Read External resource loader Test Suites `documentation <./java-testsuite-runner-ext-res-loader/README.md>`_.

Usage
-----

- In MicroEJ SDK, import the ``java-testsuite-runner-ext-res-loader`` project in your workspace.
- Follow the configuration and execution steps described in VEE Port Test Suites `documentation <../README.rst>`_.

Test Suite Source Code Navigation
---------------------------------

- See VEE Port Test Suites `documentation <../README.rst>`_.

Troubleshooting
---------------

See Vee Port Test Suites `documentation <../README.rst>`_.
