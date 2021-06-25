/*
 * C
 *
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include "../../../../../framework/c/embunit/embUnit/embUnit.h"
#include "t_ui_api.h"
#include "t_ui_framerate.h"
#include "t_ui_tearing.h"
#include "LLDISPLAY.h"

static bool lcd_initialized = false;

void T_UI_main(void)
{
	TestRunner_start();
	TestRunner_runTest(T_UI_API_tests());
	TestRunner_runTest(T_UI_TEARING_tests());
	TestRunner_runTest(T_UI_FRAMERATE_tests());
	TestRunner_end();
	return;
}

void T_UI_LCD_initialize()
{
	if (!lcd_initialized)
	{
		// this call should be executed only once
		LLDISPLAY_initialize();
		lcd_initialized = true;
	}
}
