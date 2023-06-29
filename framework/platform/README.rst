Platform Configuration Additions
================================

This directory contains all required files to properly configure an empty Platform project 
connected to a third party C BSP (Board Support Package) project.

- The ``content-sdk-5`` directory contains files for building the Platform using a SDK version ``5.x``.
  These files must be copied into the Platform configuration directory.
  Configuration directory is the one that holds "[PLATFORM_NAME]-configuration" project that contains the ``.platform`` file.
  This directory can be downloaded by cloning or downloading the repository through web interface.
  
  Optionally, if you have Subversion (svn command) installed, it can be automatically downloaded using the 
  following command line:

  .. code-block:: console
   
     svn export --force https://github.com/MicroEJ/PlatformQualificationTools/trunk/framework/platform/content-sdk-5 [path_to_platform_configuration_directory]

- The ``content-architecture-7`` directory extends the ``content-sdk-5`` directory with files for building the Executable.
  These files must be copied into the Platform configuration directory only if you are using an Architecture version ``7.x``. 
  If you are using Architecture ``8.x``, the files are already included and must not be copied. 

  If you have Subversion (svn command) installed, it can be automatically downloaded using the 
  following command line:

  .. code-block:: console
   
     svn export --force https://github.com/MicroEJ/PlatformQualificationTools/trunk/framework/platform/content-architecture-7 [path_to_platform_configuration_directory]



- The ``scripts`` directory contains ready to use console scripts templates to invoke the build and the run of 
  an Executable using a third party C toolchain or IDE (IAR Embedded Workbench, Keil MDK-ARM, Espressif ESP-IDF toolchain, ...)

Please refer to `Platform creation documentation <https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformCreation.html>`_ for usage and options.

.. ReStructuredText
.. Copyright 2020-2022 MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.