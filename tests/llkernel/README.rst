.. ReStructuredText
.. Copyright 2023 MicroEJ Corp.  MicroEJ Corp. All rights reserved.
.. Use of this source code is governed by a BSD-style license that can be found with this software.

************************
Multi-Sandbox Test Suite
************************

Overview
========

This folder contains sources to test implementation of MicroEJ Multi-Sandbox.

The MicroEJ Multi-Sandbox Test Suite validates the LLAPI ``LLKERNEL_impl.h``
implementation executing several tests.

All tests can be run in one step: all tests will be executed one by one
and are run in a specific order, *next one* expects *previous one* is
passed.

Requirements
============

- Follow the `main Readme <../../README.rst>`_.

Configuration
=============

#. In your BSP project, add all files of these folders as source files:

   * ``tests/llkernel/c/src/``
   * ``framework/c/utils/src/``
   * ``framework/c/embunit/embUnit/``

#. In your BSP project, add these folders as include paths:

   * ``tests/llkernel/c/inc/``
   * ``framework/c/utils/inc/``
   * ``framework/c/embunit/embUnit/``

#. Locate the call to ``microej_main`` in the BSP project. Include the ``t_llkernel_main.h`` header file in this file, and add a call to the function ``T_LLKERNEL_main`` just before the call to ``microej_main``.
#. Build the BSP and link it with the MicroEJ Platform runtime library and MicroEJ Application.

Expected Results
================

::

    T_LLKERNEL v1.1.0
	.
	T_LLKERNEL_setUp
	LLKERNEL resource allocate
	T_LLKERNEL_tearDown
	.
	T_LLKERNEL_setUp
	LLKERNEL resource allocate and free
	T_LLKERNEL_tearDown
	.
	T_LLKERNEL_setUp
	LLKERNEL resource allocate overflow
	T_LLKERNEL_tearDown
	.
	T_LLKERNEL_setUp
	LLKERNEL resource install overflow
	T_LLKERNEL_tearDown
	.
	T_LLKERNEL_setUp
	LLKERNEL resource install out of bounds
	T_LLKERNEL_tearDown
	
	OK (5 tests)


No error must be thrown when executing this test.
