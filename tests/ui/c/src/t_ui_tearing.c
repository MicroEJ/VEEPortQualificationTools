/*
 * C
 *
 * Copyright 2019-2020 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "../../../../framework/c/embunit/embUnit/embUnit.h"
#include "../../../../framework/c/utils/inc/u_time_base.h"
#include "../../../../framework/c/utils/inc/u_print.h"
#include "x_version.h"
#include "t_ui_tearing.h"
#include "LLDISPLAY.h"
#include "x_ui_config.h"
#include "t_ui_main.h"

/*
 * Time in second the test is running
 */
#define TEARING_TIME_SECOND 10

static void T_UI_FRAMERATE_setUp(void)
{
	UTIL_print_initialize();
	UTIL_TIME_BASE_initialize();
	T_UI_LCD_initialize();
}

static void T_UI_FRAMERATE_tearDown(void)
{

}

static void T_UI_TEARING_showTearing(void)
{
	uint32_t bpp = UI_CONFIG_getBPP();
	if (bpp == 0)
	{
		UTIL_print_string("Tearing test requires an implementation of UI_CONFIG_getBPP() function. Test cannot run.");
		return;
	}

	uint32_t buffer_address = LLDISPLAY_getGraphicsBufferAddress();
	uint32_t size = LLDISPLAY_getWidth() * LLDISPLAY_getHeight() * bpp / 8;
	uint64_t t0 = UTIL_TIME_BASE_getTime();

	UTIL_print_string("Refresh LCD content with black and screen data. Ensures about tearing effect.");

	while(UTIL_TIME_BASE_getTime() - t0 < TEARING_TIME_SECOND * 1000000)
	{
		// fill buffer with '0' (often means black) and flush it
		memset((void*)buffer_address, 0, size);
		buffer_address = LLDISPLAY_flush(buffer_address, 0, 0, LLDISPLAY_getWidth() - 1, LLDISPLAY_getHeight() - 1);
		LLDISPLAY_synchronize();

		// fill buffer with '1' (often means white) and flush it
		memset((void*)buffer_address, 0xff, size);
		buffer_address = LLDISPLAY_flush(buffer_address, 0, 0, LLDISPLAY_getWidth() - 1, LLDISPLAY_getHeight() - 1);
		LLDISPLAY_synchronize();
	}
}

TestRef T_UI_TEARING_tests(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures)
	{
		new_TestFixture("Tearing", T_UI_TEARING_showTearing),
	};

	EMB_UNIT_TESTCALLER(framerateTest, "Framerate_tests", T_UI_FRAMERATE_setUp, T_UI_FRAMERATE_tearDown, fixtures);

	return (TestRef)&framerateTest;
}
