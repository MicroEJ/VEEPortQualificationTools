/*
 * C
 * 
 * Copyright 2019-2021 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "x_ui_framerate.h"
#include "LLDISPLAY.h"
#include "../../../../../framework/c/utils/inc/u_print.h"
#include "../../../../../framework/c/utils/inc/u_time_base.h"

/*
 * Defines the number of loops to get an average of bench time.
 */
#define NB_LOOPS 20

/*
 * Defines the time tolerance in us we consider both times are equal
 */
#define TIME_TOLERANCE_US 1000

/* Debug macro */
#ifndef TEST_DBG
#ifdef CONFIG_TEST_PRINTF_ON
#define TEST_DBG      printf
#else
#define TEST_DBG(...) (void)0
#endif
#endif

/*
 * Prints a time like it: 8.51 ms (in debug mode only)
 */
#define PRINT_TIME(time_us) (TEST_DBG("%.2f ms", ((float)(time_us)/1000)))

/** private function definitions */

static void flush_and_sync(uint32_t* buffer_address)
{
	*buffer_address = LLDISPLAY_flush(*buffer_address, 0, 0, LLDISPLAY_getWidth() - 1, LLDISPLAY_getHeight() - 1);
	LLDISPLAY_synchronize();
}

/*
 * Retrieves the LCD framerate simulating some drawings during given time.
 * @return a time in us
 */
static uint32_t get_framerate_time(uint32_t* buffer_address, uint32_t drawing_time_us)
{
	// We don't know when the first flush is performed when tearing signal is used.
	// -> perform a flush/sync action on test startup to start the bench just after
	// the end of first flush/sync
	flush_and_sync(buffer_address);

	uint32_t time_counter = 0;

	for(int i = 0; i < NB_LOOPS; i++)
	{
		uint64_t t0 = UTIL_TIME_BASE_getTime();
		{
			// simulate the time to perform some drawings
			while(UTIL_TIME_BASE_getTime() - t0 < drawing_time_us);

			// ask a flush and wait its end
			flush_and_sync(buffer_address);
		}
		uint64_t t1 = UTIL_TIME_BASE_getTime();

		time_counter += (uint32_t)(t1 - t0);
	}

	return time_counter / NB_LOOPS;
}

/*
 * Adjusts the time to perform some drawings. This time must not change the expected LCD framerate.
 */
static uint32_t adjust_drawing_time(uint32_t drawing_time_us, uint32_t drawing_time_step_us, uint32_t framerate_time_us_ref, uint32_t* buffer_address)
{
	uint32_t framerate_with_drawing = framerate_time_us_ref;

	while(framerate_with_drawing < framerate_time_us_ref + TIME_TOLERANCE_US)
	{
		drawing_time_us += drawing_time_step_us;
		framerate_with_drawing = get_framerate_time(buffer_address, drawing_time_us);

		TEST_DBG("With a drawing time of ");
		PRINT_TIME(drawing_time_us);
		TEST_DBG(", the LCD framerate time is ");
		PRINT_TIME(framerate_with_drawing);
		TEST_DBG("\n");
	}

	return drawing_time_us - drawing_time_step_us;
}

/* public function definitions */

void X_UI_FRAMERATE_get(uint32_t buffer_address, uint32_t* framerate_time_us, uint32_t* flush_copy_time_us)
{
	// retrieve the LCD minimal framerate time
	UTIL_print_string("Retrieve the LCD framerate...\n");
	*framerate_time_us = get_framerate_time(&buffer_address, 0);
	TEST_DBG("Minimal LCD framerate time is ");
	PRINT_TIME(*framerate_time_us);
	TEST_DBG("\n");

	// retrieve maximum time to perform some drawings without changing LCD minimal framerate time
	UTIL_print_string("Retrieve the maximal drawing time (this will take several seconds)...\n");
	uint32_t drawing_time_us = 0;
	for(uint32_t drawing_time_step_us = 1000; drawing_time_step_us >= 10; drawing_time_step_us /= 10)
	{
		drawing_time_us = adjust_drawing_time(drawing_time_us, drawing_time_step_us, *framerate_time_us, &buffer_address);
	}

	*flush_copy_time_us = *framerate_time_us - drawing_time_us;

	TEST_DBG("Maximum drawing time is ");
	PRINT_TIME(drawing_time_us);
	TEST_DBG("(and so flush copy time is ");
	PRINT_TIME(*flush_copy_time_us);
	TEST_DBG(")\n");
}
