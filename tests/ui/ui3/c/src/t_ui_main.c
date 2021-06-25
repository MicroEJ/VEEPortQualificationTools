/*
 * C
 *
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include "../../../../../framework/c/embunit/embUnit/embUnit.h"
#include "t_ui_main.h"
#include "t_ui_api.h"
#include "t_ui_framerate.h"
#include "t_ui_tearing.h"

LLUI_DISPLAY_SInitData LLUI_DISPLAY_InitData;

#ifdef ENABLE_FLUSH_TESTS
static bool _tests_running = false;
#endif // ENABLE_FLUSH_TESTS

void T_UI_main(void)
{

#ifdef ENABLE_FLUSH_TESTS
	_tests_running = true;
#endif // ENABLE_FLUSH_TESTS

	memset((void*)&LLUI_DISPLAY_InitData, 0, sizeof(LLUI_DISPLAY_SInitData));
	
	TestRunner_start();
	TestRunner_runTest(T_UI_API_tests());

#ifdef ENABLE_FLUSH_TESTS
	TestRunner_runTest(T_UI_TEARING_tests());
	TestRunner_runTest(T_UI_FRAMERATE_tests());
#endif // ENABLE_FLUSH_TESTS

	TestRunner_end();

#ifdef ENABLE_FLUSH_TESTS
	_tests_running = false;
#endif // ENABLE_FLUSH_TESTS
}

void T_UI_LCD_initialize()
{
	if (0 == LLUI_DISPLAY_InitData.lcd_width)
	{		
		// this call should be executed only once
		LLUI_DISPLAY_IMPL_initialize(&LLUI_DISPLAY_InitData);
		
		// LCD buffer size is optional, by default its size is equal to LCD size.
		
		if (0 == LLUI_DISPLAY_InitData.memory_width)
		{
			LLUI_DISPLAY_InitData.memory_width = LLUI_DISPLAY_InitData.lcd_width;
		}
		
		if (0 == LLUI_DISPLAY_InitData.memory_height)
		{
			LLUI_DISPLAY_InitData.memory_height = LLUI_DISPLAY_InitData.lcd_height;
		}
	}
}

#ifdef ENABLE_FLUSH_TESTS

void T_UI_LCD_wait_flush(void)
{
	if (_tests_running)
	{
		// use a Graphics Engine's semaphore to wait the end of flush
		LLUI_DISPLAY_IMPL_binarySemaphoreTake(LLUI_DISPLAY_InitData.binary_semaphore_0);
	}
	// else: tests are not running (MicroEJ VEE is running), cannot use the Graphics Engine's semaphore
}

void T_UI_LCD_flush_done(bool from_isr)
{
	if (_tests_running)
	{
		// use a Graphics Engine's semaphore to notify the end of flush
		LLUI_DISPLAY_IMPL_binarySemaphoreGive(LLUI_DISPLAY_InitData.binary_semaphore_0, from_isr);
	}
	else
	{
		// tests are not running (MicroEJ VEE is running), cannot use the Graphics Engine's semaphore
		// -> redirect the end of flush to Graphics Engine's function
		LLUI_DISPLAY_flushDone(from_isr);
	}
}

#endif // ENABLE_FLUSH_TESTS

