..
	Copyright 2019-2020 MicroEJ Corp. All rights reserved.
	Use of this source code is governed by a BSD-style license that can be found with this software.

=========
Changelog
=========

All notable changes to this project will be documented in this file.

The format is based on `Keep a Changelog <https://keepachangelog.com/en/1.0.0/>`_, and this project adheres to `Semantic Versioning <https://semver.org/spec/v2.0.0.html>`_.

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

- Fix ``X_RAM_CHECKS_checkAddress16()``: test checked memory accesses outside memory range
- Fix ``UTIL_TIME_BASE_getTime()``: fix type of returned value

Changed
=======

- Improved documentation
- Provide CoreMark as git-submodule instead of a local copy
- Provide JVM Portage Validation as source instead of a jar

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
  
