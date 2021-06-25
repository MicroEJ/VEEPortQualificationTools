/*
 * C
 *
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/* Prevent recursive inclusion */

#ifndef __T_UI_API_H
#define __T_UI_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../../../framework/c/embunit/embunit/embUnit.h"

/* Public function declarations */

/**
 * @brief Performs several tests on LLDisplay API to validate LLDisplay implementation.
 */
TestRef T_UI_API_tests(void);

#ifdef __cplusplus
}
#endif

#endif
