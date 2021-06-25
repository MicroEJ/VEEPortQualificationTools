/*
 * C
 *
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */
#include <stdio.h>
#include <stdarg.h>
#include "../../../../../framework/c/embunit/embUnit/embUnit.h"
#include "../../../../../framework/c/utils/inc/u_print.h"
#include "../../../../../framework/c/utils/inc/u_time_base.h"
#include "x_version.h"
#include "t_ui_framerate.h"
#include "x_ui_framerate.h"
#include "LLDISPLAY.h"
#include "t_ui_main.h"

static void T_UI_FRAMERATE_setUp(void)
{
	UTIL_print_initialize();
	UTIL_TIME_BASE_initialize();
	T_UI_LCD_initialize();
}

static void T_UI_FRAMERATE_tearDown(void)
{

}

static void print_drawing_time_report(float frequency, uint32_t div, uint32_t framerate_time_us, uint32_t flush_copy_time_us)
{
	UTIL_print_string("To have an animation at ");
	UTIL_print_float(frequency / div);
	UTIL_print_string(" Hz, the drawing time cannot be higher than ");
	UTIL_print_float(((float)(framerate_time_us * div - flush_copy_time_us))/1000);
	UTIL_print_string(" ms.\n");
}

static void T_UI_FRAMERATE_getFramerate(void)
{
	uint32_t buffer_address = LLDISPLAY_getGraphicsBufferAddress();
	uint32_t framerate_time_us;
	uint32_t flush_copy_time_us;

	X_UI_FRAMERATE_get(LLDISPLAY_getGraphicsBufferAddress(), &framerate_time_us, &flush_copy_time_us);

	float frequency = 1/(((float)framerate_time_us)/1000000);

	UTIL_print_string("\n");
	UTIL_print_string("LCD framerate time is ");
	UTIL_print_float(((float)framerate_time_us)/1000);
	UTIL_print_string(" ms (");
	UTIL_print_float(frequency);

	UTIL_print_string(" Hz)\n");
	UTIL_print_string("The copy time is ");
	UTIL_print_float(((float)flush_copy_time_us)/1000);
	UTIL_print_string(" ms\n");

	print_drawing_time_report(frequency, 1, framerate_time_us, flush_copy_time_us);
	print_drawing_time_report(frequency, 2, framerate_time_us, flush_copy_time_us);
	print_drawing_time_report(frequency, 3, framerate_time_us, flush_copy_time_us);
}

TestRef T_UI_FRAMERATE_tests(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures)
			{
		new_TestFixture("Framerate", T_UI_FRAMERATE_getFramerate),
			};

	EMB_UNIT_TESTCALLER(framerateTest, "Framerate_tests", T_UI_FRAMERATE_setUp, T_UI_FRAMERATE_tearDown, fixtures);

	return (TestRef)&framerateTest;
}
