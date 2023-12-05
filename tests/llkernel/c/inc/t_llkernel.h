/*
 * C
 *
 * Copyright 2023 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#ifndef T_LLKERNEL_H
#define T_LLKERNEL_H
#include "../../../../framework/c/embunit/embUnit/embUnit.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @brief this function is the entry point for the LLKERNEL Test Suite.
 */
void T_LLKERNEL_main(void);

TestRef	T_LLKERNEL_tests(void);

#ifdef __cplusplus
}
#endif

#endif
