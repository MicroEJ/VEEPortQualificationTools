/*
 * C
 *
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/* Prevent recursive inclusion */

#ifndef __T_UI_MAIN_H
#define __T_UI_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "LLUI_DISPLAY_impl.h"

/**
 * @brief The LLAPI "LLUI_DISPLAY_IMPL_flush" cannot be called from a C example: it requires an image of
 * a MicroUI GraphicsContext (MICROUI_GraphicsContext*) and the LCD driver has to call the MicroEJ Graphics
 * Engine callback "LLUI_DISPLAY_flushDone" to notify the end of flush.
 *
 * By consequence, the tests have been extracted in a MicroEJ application that produces the same results.
 *
 * However it is possible to enable the C tests in order to test the LLAPI LLUI_DISPLAY_IMPL portage in C.
 * The portage has to respect the following rules:
 *
 * - The parameter "MICROUI_GraphicsContext*" of "LLUI_DISPLAY_IMPL_flush" function is useless by the
 *   implementation (C tests give NULL).
 * - The LCD driver has to call the function "T_UI_LCD_flush_done" instead of "LLUI_DISPLAY_flushDone".
 *   When the C UI tests are running, this callback is used to be notified of the end of flush. When the
 *   MicroEJ VEE is running (MicroEJ application), a call to "LLUI_DISPLAY_flushDone" is performed.
 *   However this indirection takes some time.
 * - A linker error is thrown when this define is enabled for the first time: it forces to remaind that
 *   the LCD driver has not to call directly "LLUI_DISPLAY_flushDone" function.
 *
 * @see LLUI_DISPLAY_flushDone in x_impl_config.c
 */
//#define ENABLE_FLUSH_TESTS

/* public field declaration */

extern LLUI_DISPLAY_SInitData LLUI_DISPLAY_InitData;

/* public function declaration */

/*
 * @brief This function is the entry point for the UI test suite. By default, the executed test sequence is :
 *		-# Check LLUI_DISPLAY_IMPL implementation
 *		-# Retrieve the LCD framerate
 */
void T_UI_main(void);

/*
 * @brief The LLUI_DISPLAY_IMPL initialize function should be only called once. This function ensures to not call
 * several time initialize function in case of all UI tests are not executed as originally planned.
 */
void T_UI_LCD_initialize(void);

#ifdef ENABLE_FLUSH_TESTS

/*
 * @brief The C UI tests can wait the end of flush by calling this function.
 */
void T_UI_LCD_wait_flush(void);

/*
 * @brief The LCD driver has to call this function instead of calling "LLUI_DISPLAY_flushDone".
 */
void T_UI_LCD_flush_done(bool from_isr);

#endif // ENABLE_FLUSH_TESTS

#ifdef __cplusplus
}
#endif

#endif
