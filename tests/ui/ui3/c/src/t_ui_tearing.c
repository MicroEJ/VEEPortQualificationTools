/*
 * C
 *
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */
#include "t_ui_main.h"

#ifdef ENABLE_FLUSH_TESTS

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "../../../../../framework/c/embunit/embUnit/embUnit.h"
#include "../../../../../framework/c/utils/inc/u_time_base.h"
#include "../../../../../framework/c/utils/inc/u_print.h"
#include "t_ui_tearing.h"
#include "x_ui_config.h"

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

	uint8_t* buffer_address = LLUI_DISPLAY_InitData.back_buffer_address;
	uint32_t size = LLUI_DISPLAY_InitData.memory_width * LLUI_DISPLAY_InitData.memory_height * bpp / 8;
	uint64_t t0 = UTIL_TIME_BASE_getTime();

	UTIL_print_string("Refresh the LCD content with black and white data. Ensure about the tearing effect.");

	while(UTIL_TIME_BASE_getTime() - t0 < TEARING_TIME_SECOND * 1000000)
	{
		// fill buffer with '0' (often means black) and flush it
		memset((void*)buffer_address, 0, size);
		buffer_address = LLUI_DISPLAY_IMPL_flush(NULL, buffer_address, 0, 0, LLUI_DISPLAY_InitData.lcd_width - 1, LLUI_DISPLAY_InitData.lcd_height - 1);
		T_UI_LCD_wait_flush();

		// fill buffer with '1' (often means white) and flush it
		memset((void*)buffer_address, 0xff, size);
		buffer_address = LLUI_DISPLAY_IMPL_flush(NULL, buffer_address, 0, 0, LLUI_DISPLAY_InitData.lcd_width - 1, LLUI_DISPLAY_InitData.lcd_height - 1);
		T_UI_LCD_wait_flush();
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

#endif // ENABLE_FLUSH_TESTS
