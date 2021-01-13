..
	Copyright 2019-2021 MicroEJ Corp. All rights reserved.
	Use of this source code is governed by a BSD-style license that can be found with this software.

=========
Changelog
=========

All notable changes to this project will be documented in this file.

The format is based on `Keep a Changelog <https://keepachangelog.com/en/1.0.0/>`_, and this project adheres to `Semantic Versioning <https://semver.org/spec/v2.0.0.html>`_.

-------------------
2.3.0 -- 2021-01-13
-------------------

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
  
