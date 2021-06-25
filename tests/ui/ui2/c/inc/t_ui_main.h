/*
 * C
 *
 * Copyright 2019-2020 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/* Prevent recursive inclusion */

#ifndef __T_UI_MAIN_H
#define __T_UI_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* public function declaration */

/**
 * @brief This function is the entry point for the UI test suite. By default, the executed test sequence is :
 *		-# Check LLDisplay implementation
 *		-# Retrieve the LCD framerate
 */
void T_UI_main(void);

/**
 * @brief The LLDisplay initialize function should be only called once. This function ensures to not call
 * several time initialize function in case of all UI tests are not executed as originally planned.
 */
void T_UI_LCD_initialize(void);

#ifdef __cplusplus
}
#endif

#endif
