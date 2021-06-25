/*
 * C
 * 
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "t_ui_main.h"
#include "x_ui_config.h"
#include "bsp_util.h"
#include "LLUI_DISPLAY.h"
#include "../../../../../framework/c/embunit/embUnit/embUnit.h"

/**
 * 
 * @brief This function provides an invalid value of LCD BPP (bit-per-pixel).
 *
 * @return 0
 */

BSP_DECLARE_WEAK_FCNT uint32_t UI_CONFIG_getBPP(void)
{
	return 0;
}

#ifdef ENABLE_FLUSH_TESTS

/**
 *
 * @brief Comment, rename or remove this function when ENABLE_FLUSH_TESTS is enabled.
 *
 * - To run the PQT UI flush tests:
 *   1. Define ENABLE_FLUSH_TESTS
 *   2. Change the caller of LLUI_DISPLAY_flushDone() to use T_UI_LCD_flush_done() function instead of LLUI_DISPLAY_flushDone().
 *   3. Comment, rename or remove this function.
 * - To run the MicroEJ VEE application, restore the use of LLUI_DISPLAY_flushDone() in the caller.
 *
 * Note: the function T_UI_LCD_flush_done() is calling Graphics Engine's LLUI_DISPLAY_flushDone() function
 * when PQT UI tests are not running (MicroEJ VEE is running). However this call performs an indirection.
 *
 * @see ENABLE_FLUSH_TESTS in t_ui_main.h
 */
void LLUI_DISPLAY_flushDone(bool from_isr)
{
	TEST_FAIL("Call T_UI_LCD_flush_done() instead of LLUI_DISPLAY_flushDone() and remove this function to run the PQT UI tests. (see function comment)");
}

#endif // ENABLE_FLUSH_TESTS
