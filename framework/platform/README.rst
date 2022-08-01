MicroEJ Platform Configuration Additions
========================================

This directory contains all required files to properly configure an empty MicroEJ Platform project 
connected to a third party C BSP (Board Support Package) project.

- The ``content`` directory contains files that must be copied into MicroEJ Platform configuration directory.
  Configuration directory is the one that holds "[PLATFORM_NAME]-configuration" project that contains the ``.platform`` file.
  This directory can be downloaded by cloning or downloading the repository through web interface.
  
  Optionally, if you have Subversion (svn command) installed, it also can be automatically downloaded using the 
  following command line:

  .. code-block:: console
   
     svn export --force https://github.com/MicroEJ/PlatformQualificationTools/trunk/framework/platform/content [path_to_platform_configuration_directory]

- The ``scripts`` directory contains ready to use console scripts templates to invoke the build and the run of 
  a MicroEJ Firmware using a third party C toolchain or IDE (IAR Embedded Workbench, Keil MDK-ARM, Espressif ESP-IDF toolchain, ...)

Please refer to `MicroEJ Platform creation documentation <https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformCreation.html>`_ for usage and options.

.. ReStructuredText
.. Copyright 2020 MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.