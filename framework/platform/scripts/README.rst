Build and Run Scripts Examples
==============================

This directory contains examples of build and run scripts for several toolchains and programming tools.

Overview
--------

Within each directory, the following scripts are available:

- ``build.XXX`` compiles and links the BSP to produce a MicroEJ
  Firmware.
- ``run.XXX`` flash the MicroEJ Firmware onto the device and reset the
  device.
- ``set_project_env.XXX`` checks the environment settings and set
  required environment variables.

Both ``build.XXX`` and ``run.XXX`` load the ``set_project_env.XXX``
script to ensure the environment is properly set up.

The behavior of ``build.XXX`` MUST follow the
specification described in `BSP Build Script File
<https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformCreation.html#build-script-file>`_.

The behavior of ``run.XXX`` MUST follow the
specification described in `BSP Run Script File
<https://docs.microej.com/en/latest/PlatformDeveloperGuide/platformCreation.html#run-script-file>`_.

Usage
-----

Add the build and run scripts to the BSP.

General recommendations for build and run scripts
------------------------------------------------

In addition to the specification of the build and run scripts, here
are some general recommendations for the scripts:

- When applicable, use the following naming convention for the
  toolchain installation directory:

  ``<TOOLCHAIN>_<TOOLCHAIN VERSION>_INSTALLATION_DIR``

  For example:  ``IAREW_83x_INSTALLATION_DIR`` for IAR Embedded
  Workbench version 8.3.x.

- Document the required variables, provide examples when applicable.

Stub implementations of build and run script are provided as example
for both Windows (``WINDOWS_STUB/``) and Unix (``UNIX_STUB/``).

Test Scripts
------------

After developing a new script or modifying existing scripts for you needs, check the script works using the following tests sequence:

#. Initialization
   
   - Create a temporary directory which contains spaces and accented characters (e.g. ``c:\tmp\my rép``)
   - Create the following directories:

      - ``c:\tmp\my rép\bsp``
      - ``c:\tmp\my rép\test``
      - ``c:\tmp\my rép\test2``

   - Copy the BSP (including build and run scripts) into ``c:\tmp\my rép\bsp`` directory 
   - Open a terminal
   - Change current directory to ``c:\tmp\my rép\test``

#. Test Build
   
   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\build.bat``
   - After successful build, check the ``c:\tmp\my rép\test\application.out`` exists
   
#. Test Build Overwrite
   
   - Touch the ``c:\tmp\my rép\test\application.out``
   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\build.bat``
   - After successful build, check the ``c:\tmp\my rép\test\application.out`` date has been modified

#. Test Run

   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\run.bat``
   - Check the executable has been programmed and started on device (e.g. it prints ``Hello World!``)

#. Test Run Overwrite

   - Change current directory to ``c:tmp\my rép\test2``
   - Update the application in the bsp to change it's behavior (e.g. it prints ``Hello World #2!`` instead of ``Hello World!``)
   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\build.bat``
   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\run.bat``
   - Check the executable has been programmed and started on device (e.g. it prints ``Hello World #2!``)
   - Change current directory to ``c:tmp\my rép\test``
   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\run.bat``
   - Check the executable has been programmed and started on device (e.g. it prints ``Hello World!``)

#. Test Run From Parameter

   The current directory is ``c:tmp\my rép\test`` and contains ``application.out`` file that prints ``Hello World!``.
   This last test verifies that the executable passed as parameter is taken prior to the ``application.out`` file.
 
   - Launch ``c:\tmp\my rép\bsp\[path_to_build_script]\run.bat c:tmp\my rép\test2\application.out``
   - Check the executable has been programmed and started on device (e.g. it prints ``Hello World #2!``)

Troubleshooting
---------------

Permissions on BSP script files
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The file permissions are not preserved during the build of a Platform.
If the third-party toolchain requires specific permissions (such as
the executable permission) during the execution of the build or the
run scripts, they must be enforced in the scripts.  For example, in
the build script file:

.. code-block:: sh

   # Add exec permission on a file
   chmod +x ../toolchain/a_script.sh

   # Add exec permission on all .sh files in a directory hierarchy
   find ../a_module/ -type f -name \*.sh -exec chmod +x {} \;

Issues with path length on Windows
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When copying in a bat script you can have an issue if the source path
is too long.  For example, when copying like this:

.. code-block:: bat

   copy /B "%ELF_FILE%" "%output.file%"

Use instead this:

.. code-block:: bat

   copy /B "%ELF_FILE%" "\\?\%output.file%"

See https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file#maximum-path-length-limitation for more information.


.. ReStructuredText
.. Copyright 2020-2021 MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.
