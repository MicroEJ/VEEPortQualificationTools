/*
 * C
 *
 * Copyright 2019-2024 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

/* Prevent recursive inclusion */

#ifndef __T_UI_CONFIG_H
#define __T_UI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdint.h>

#define UI_LCD_BPP_ARGB8888 32
#define UI_LCD_BPP_RGB888 24
#define UI_LCD_BPP_RGB565 16
#define UI_LCD_BPP_RGB1555 16
#define UI_LCD_BPP_RGB4444 16

/* Public function declarations */

/**
 * @brief Gets the LCD number of bits-per-pixel. This information is not required by the LLDisplay
 * implementation (already available in the VEE Port) but it is highly recommended to perform
 * some tests.
 */
uint32_t UI_CONFIG_getBPP(void);

#ifdef __cplusplus
}
#endif

#endif
