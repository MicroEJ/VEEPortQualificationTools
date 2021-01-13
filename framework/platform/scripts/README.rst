Build Scripts Examples
======================

This directory contains build scripts examples for several toolchains.

Overview
--------

For each toolchain, the following scripts are available:

- ``build.XXX`` compiles and links the BSP to produce a MicroEJ
  Firmware.
- ``run.XXX`` flash the MicroEJ Firmware onto the device and reset the
  device.
- ``set_project_env.XXX`` checks the environment settings and set
  required environment variables.

Both ``build.XXX`` and ``run.XXX`` load the ``set_project_env.XXX``
script to ensure the environment is properly set up.

The behavior of ``build.XXX`` and ``run.XXX`` MUST follow the
specification described in `BSP Script File
<https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformCreation.html#bsp-connection-build-script>`__.

Usage
-----

Add the build scripts to the BSP.

General recommendation for build scripts
----------------------------------------

In addition to the specification of the build scripts, here some
general recommendation for the build scripts:

- Provide sensible default (e.g. default path for the toolchain).
- Allow the user to override the default settings with global
  environment variables and with a local script (see
  ``set_local_env.XXX.tpl``).


.. ReStructuredText
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.
