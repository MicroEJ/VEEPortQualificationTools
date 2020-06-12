/*
 * C
 *
 * Copyright 2019-2020 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */
#include <stdio.h>
#include <stdarg.h>
#include "../../../../framework/c/embunit/embUnit/embUnit.h"
#include "../../../../framework/c/utils/inc/u_print.h"
#include "x_version.h"
#include "t_ui_api.h"
#include "x_ui_config.h"
#include "LLDISPLAY.h"
#include "t_ui_main.h"

/*
 * LCD size (width or height) cannot be higher than this value.
 */
#define MAX_LCD_SIZE 2048
#define CONFIG_TEST_PRINTF_ON 1
/* Debug macro */
#ifndef TEST_DBG
#ifdef CONFIG_TEST_PRINTF_ON
#define TEST_DBG      printf
#else
#define TEST_DBG(...) (void)0
#endif
#endif

static void T_UI_API_setUp(void)
{
	UTIL_print_initialize();
}

static void T_UI_API_tearDown(void)
{

}

/*
 * Ensures <code>initialize</code> function is implemented (no returned value).
 */
static void T_UI_API_initialize(void)
{
	T_UI_LCD_initialize();

	// actually nothing to test, just ensure compilation is working
	TEST_ASSERT(1);
}

/**
 * Ensures LCD size is valid.
 */
static void T_UI_API_checkSize(void)
{
	int32_t w = LLDISPLAY_getWidth();
	int32_t h = LLDISPLAY_getHeight();

	TEST_DBG("LCD width = %d\n", w);
	TEST_DBG("LCD height = %d\n", h);

	TEST_ASSERT_MESSAGE( w > 0,  "LCD width is invalid. Check value returned by LLDISPLAY_IMPL_getWidth().\n" );
	TEST_ASSERT_MESSAGE( h > 0,  "LCD height is invalid. Check value returned by LLDISPLAY_IMPL_getHeight().\n" );
	TEST_ASSERT_MESSAGE( w <= MAX_LCD_SIZE,  "LCD width is too high. Max value is MAX_LCD_SIZE. Check value returned by LLDISPLAY_IMPL_getWidth().\n");
	TEST_ASSERT_MESSAGE( h <= MAX_LCD_SIZE,  "LCD height is too high. Max value is MAX_LCD_SIZE. Check value returned by LLDISPLAY_IMPL_getHeight().\n");
}

/*
 * Check LCD BPP (bit-per-pixel). This API is not mandatory in BSP project and required in MicroEJ Platform configuration project.
 * This value is useful to perform some additional checks.
 */
static void T_UI_API_checkBPP(void)
{
	uint32_t bpp = UI_CONFIG_getBPP();

	switch(bpp)
	{
	case 0:
		TEST_DBG("Function UI_CONFIG_getBPP() is not implemented, cannot check LCD BPP.\n");
		break;
	case 1:
	case 2:
	case 4:
	case 8:
	case 16:
	case 24:
	case 32:
		// valid BPP
		TEST_DBG("LCD BPP = %d\n", bpp);
		TEST_ASSERT(1);
		break;
	default:
		TEST_FAIL("Invalid BPP. UI_CONFIG_getBPP() must return a value among this list: 1, 2, 4, 8, 16, 24, 32 and UI_LCD_BPP_*");
		break;
	}
}

static void T_UI_API_checkBufferAddr(uint32_t buffer_addr)
{
	volatile uint8_t* start_address_8 =  (uint8_t*)buffer_addr;
	volatile uint16_t* start_address_16 = (uint16_t*)buffer_addr;
	volatile uint32_t* start_address_32 = (uint32_t*)buffer_addr;

	uint32_t bpp = UI_CONFIG_getBPP();
	if (bpp == 0)
	{
		TEST_DBG("LCD BPP is recommended to test back buffer size. Please implement UI_CONFIG_getBPP() function.\n");
		TEST_DBG("LCD back buffer starts at 0x%p\n", start_address_8);
	}
	else
	{
		volatile uint8_t* end_address_8 =  start_address_8 + LLDISPLAY_getWidth() * LLDISPLAY_getHeight() * bpp / 8;
		TEST_DBG("LCD back buffer is [0x%p, 0x%p[\n", start_address_8, end_address_8);
	}

	TEST_DBG("Try to write and verify something in this buffer...\n");

	// write at the beggining of LCD buffer
	*start_address_8 = 12;
	TEST_ASSERT_MESSAGE( *start_address_8 == 12,  "Cannot write or read an u8 at the beggining of LCD back buffer.");
	*start_address_16 = 1234;
	TEST_ASSERT_MESSAGE( *start_address_16 == 1234,  "Cannot write or read an u16 at the beggining of LCD back buffer.");
	*start_address_32 = 12345678;
	TEST_ASSERT_MESSAGE( *start_address_32 == 12345678,  "Cannot write or read an u32 at the beggining of LCD back buffer.");

	if (bpp > 0)
	{
		// write at the end of LCD buffer
		volatile uint8_t* end_address_8 =  start_address_8 + LLDISPLAY_getWidth() * LLDISPLAY_getHeight() * bpp / 8;
		volatile uint16_t* end_address_16 = (uint16_t*)end_address_8;
		volatile uint32_t* end_address_32 = (uint32_t*)end_address_8;

		*(end_address_8 - 1) = 12;
		TEST_ASSERT_MESSAGE( *(end_address_8 - 1) == 12,  "Cannot write or read an u8 at the end of LCD back buffer.");
		*(end_address_16 - 2) = 1234;
		TEST_ASSERT_MESSAGE( *(end_address_16 - 2) == 1234,  "Cannot write or read an u16 at the end of LCD back buffer.");
		*(end_address_32 - 4) = 12345678;
		TEST_ASSERT_MESSAGE( *(end_address_32 - 4) == 12345678,  "Cannot write or read an u32 at the end of LCD back buffer.");
	}
}

static void T_UI_API_checkBuffer(void)
{
	T_UI_API_checkBufferAddr(LLDISPLAY_getGraphicsBufferAddress());
}

static void T_UI_API_checkFlush(void)
{
	uint32_t buffer_address = LLDISPLAY_getGraphicsBufferAddress();

	// ask a flush and wait end of flush
	uint32_t buffer_address_2 = LLDISPLAY_flush(buffer_address, 0, 0, LLDISPLAY_getWidth() - 1, LLDISPLAY_getHeight() - 1);
	LLDISPLAY_synchronize();

	if (buffer_address_2 != buffer_address)
	{
		// it is a "LCD buffer switch implementation"; test this new buffer
		T_UI_API_checkBufferAddr(buffer_address_2);
	}

	// actually nothing (else) to test, just ensure compilation is working
	TEST_ASSERT(1);
}

TestRef T_UI_API_tests(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures)
	{
		new_TestFixture("LCD_Init", T_UI_API_initialize),
		new_TestFixture("LCD_Size", T_UI_API_checkSize),
		new_TestFixture("LCD_BPP", T_UI_API_checkBPP),
		new_TestFixture("LCD_Buffer", T_UI_API_checkBuffer),
		new_TestFixture("LCD_Flush", T_UI_API_checkFlush),
	};

	EMB_UNIT_TESTCALLER(apiTest, "UI_API_tests", T_UI_API_setUp, T_UI_API_tearDown, fixtures);

	return (TestRef)&apiTest;
}
