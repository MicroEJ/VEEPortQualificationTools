..
	Copyright 2019-2023 MicroEJ Corp. All rights reserved.
	Use of this source code is governed by a BSD-style license that can be found with this software.

=========
Changelog
=========

All notable changes to this project will be documented in this file.

The format is based on `Keep a Changelog <https://keepachangelog.com/en/1.0.0/>`_, and this project adheres to `Semantic Versioning <https://semver.org/spec/v2.0.0.html>`_.

------------------
2.9.0 - 2023-06-29
------------------

Changed
=======

- Platform Configuration Additions 2.0.0 (see `CHANGELOG <framework/platform/content-sdk-5/build/CHANGELOG.md>`_).


Added 
=====

- MicroEJ External Resource Loader Validation (Java) 1.0.0 (see `CHANGELOG <tests/ext-res-loader/java-testsuite-runner-ext-res-loader/CHANGELOG.rst>`_).
- MicroEJ MicroVG Validation (Java) 1.0.0 (see `CHANGELOG <tests/microvg/java-testsuite-runner-microvg/CHANGELOG.rst>`_).

Changed
=======

- MicroEJ UI Validation (Java) 1.2.0 (see `CHANGELOG <tests/ui/ui3/java-testsuite-runner-ui3/CHANGELOG.rst>`_).
- MicroEJ Core Validation (Java) 3.2.0 (see `CHANGELOG <tests/core/java-testsuite-runner-core/CHANGELOG.rst>`_).
- MicroEJ ECOM-WIFI Validation (Java) 1.0.1 (see `CHANGELOG <tests/ecom-wifi/java-testsuite-runner-ecom-wifi/CHANGELOG.rst>`_).
- MicroEJ FS Validation (Java) 1.0.1 (see `CHANGELOG <tests/fs/java-testsuite-runner-fs/CHANGELOG.rst>`_).
- MicroEJ NET Validation (Java) 1.0.1 (see `CHANGELOG <tests/net/java-testsuite-runner-net/CHANGELOG.rst>`_).
- MicroEJ SECURITY Validation (Java) 1.0.1 (see `CHANGELOG <tests/security/java-testsuite-runner-security/CHANGELOG.rst>`_).
- MicroEJ SSL Validation (Java) 1.0.1 (see `CHANGELOG <tests/ssl/java-testsuite-runner-ssl/CHANGELOG.rst>`_).
- MicroEJ WATCHDOG-TIMER Validation (Java) 1.0.1 (see `CHANGELOG <tests/watchdog-timer/java-testsuite-runner-watchdog-timer/CHANGELOG.rst>`_).

Fixed
=====

- Fix broken links. 
- Fix option name in ``config.properties.tpl`` files (No BSP Connection: use ``deploy.dir.microejscript`` instead of ``deploy.bsp.microejscript``). 

------------------
2.8.0 - 2022-07-23
------------------

Added
=====

- MicroEJ NET Validation (Java) 1.0.0 for MicroEJ NET Packs 10.0.0 and higher (see `README <tests/net/README.rst>`_).
- MicroEJ SSL Validation (Java) 1.0.0 for MicroEJ NET Packs 10.0.0 and higher (see `README <tests/ssl/README.rst>`_).
- MicroEJ SECURITY Validation (Java) 1.0.0 for MicroEJ NET Packs 10.0.0 and higher (see `README <tests/security/README.rst>`_).
- MicroEJ WATCHDOG-TIMER Validation (Java) 1.0.0 for MicroEJ WATCHDOG-TIMER Packs 2.0.1 and higher (see `README <tests/watchdog-timer/README.rst>`_).
- MicroEJ ECOM-WIFI Validation (Java) 1.0.0 for MicroEJ ECOM-WIFI 2.1 and higher (see `README <tests/ecom-wifi/README.rst>`_).

Changed
=======

- MicroEJ Core Validation (Java) 3.1.0 (see `CHANGELOG <tests/core/java-testsuite-runner-core/CHANGELOG.rst>`_).
- MicroEJ UI Validation (Java) 1.1.0 (see `CHANGELOG <tests/ui/ui3/java-testsuite-runner-ui3/CHANGELOG.rst>`_).
- Reformat MicroEJ Core Validation and MicroEJ UI Validation to use standard MicroEJ Test Suite flow.

Remove
======

- MicroEJ UI Validation: remove the C project.

------------------
2.7.0 - 2021-07-16
------------------

Changed
=======

- Platform Configuration Additions 1.4.0 (see `CHANGELOG <framework/platform/content/build/CHANGELOG.md>`_).

Fixed
=====

- Fixed links and paths in Graphical User Interface Test Suite README files and Core Engine Test Suite README file.

------------------
2.6.0 - 2021-06-25
------------------

Added
=====

- Add Graphical User Interface Test Suite for MicroEJ UI Packs 13.0.0 and higher (see `README <tests/ui/ui3/README.rst>`_).

Changed
=======

- Graphical User Interface Test Suite for MicroEJ UI Packs [6.0.0-13.0.0[ (13.0.0 excluded) has moved from ``tests/ui/`` to ``tests/ui/ui2/`` (see `README <tests/ui/ui2/README.rst>`_).

------------------
2.5.0 - 2021-05-11
------------------

Changed
=======

- Platform Configuration Additions 1.3.0 (see `CHANGELOG <framework/platform/content/build/CHANGELOG.md>`_).
- IAREW run script compliance with latest specification (the executable file can be provided as first argument).
- CDT_GCC run script compliance with latest specification (the executable file can be provided as first argument).

Fixed
=====

- URLs in the documentation.

------------------
2.4.0 - 2021-04-16
------------------

Added
=====

- Documentation for testing build and run scripts.

Changed
=======

- Platform Configuration Additions 1.2.0 (see `CHANGELOG <framework/platform/content/build/CHANGELOG.md>`_).
- ``cd`` into the script's directory in CDT scripts because CDT needs to be called from the directory in which the project is.
- Use CDT variable ``CUBE_PROGRAMMER_DIR`` absolute path instead of relative so the user can choose another Cube Programmer installation than the one installed in CDT.
- Replace CDT ``cleanBuild`` by ``build`` as the clean is not needed and it forces to rebuild the whole project.
- Improve comments on how to use ``set_project_env.bat.tpl`` for Keil uVision.

Fixed
=====

- IAREW run script compliance (copy of the local ``application.out``).
- Keil uVision run script compliance (copy of the local ``application.out``).
- Documentation of ``target.platform.dir`` to setup the Test Suite FS.
- CORE Test Suite updated to 3.0.2 (see `CHANGELOG <tests/core/java-testsuite-runner-core/CHANGELOG.rst`_).

------------------
2.3.0 - 2021-01-13
------------------

The main changes of this release are the addition of the Java Test
Suite Filesystem for FS API and the Platform Configuration Additions
1.1.0.

Added
=====

- Add Filesystem Test Suite.
- Add Build Script example for CDT.
- README for the Build Scripts Examples.

Fixed
=====

- Use ``svn export`` instead of ``svn checkout`` to retrieve Platform Configuration Addition without creating a ``.svn`` directory.
- Ensure MicroEJ Platform Configuration Additions scripts are properly copied into the MicroEJ Platform.
- Use ``xxx.platform`` as default name of the Platform Configuration file.
- Fix platform build when launching for the first time MicroEJ SDK.

Changed
=======

- Platform Configuration Additions 1.1.0 with Platform module build using MMM.

------------------
2.2.0 - 2020-06-24
------------------

Added
=====

- MicroEJ Platform Configuration Additions (see `README <framework/platform/README.rst>`_).

Fixed
=====

- Add missing symbol ``core_main`` and improve the documentation on how to run CoreMark benchmark..
- Fix speed computation when less than 3 zones are defined.

------------------
2.1.0 - 2020-06-10
------------------

Added
=====

- Add UI test ``t_ui_api.c``: test LLDisplay implementation.
- Add UI test ``t_ui_tearing.c``: test LCD tearing synchronization.
- Add UI test ``t_ui_framerate.c``: retrieve LCD framerate.

Fixed
=====

- Fix ``X_RAM_CHECKS_checkAddress16()``: test checked memory accesses outside memory range.
- Fix ``UTIL_TIME_BASE_getTime()``: fix type of returned value.

Changed
=======

- Improved documentation.
- Provide CoreMark as git-submodule instead of a local copy.
- Provide Core Engine Test Suite as source instead of a jar.

------------------
1.0.1 - 2019-04-25
------------------

Fixed
=====

- Delete ``t_core_lljvm.c`` (workaround before fixing).

------------------
1.0.0 - 2019-03-07
------------------

Added
=====

- Initial revision with CORE tests only.
  
