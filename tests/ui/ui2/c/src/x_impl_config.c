/*
 * C
 * 
 * Copyright 2019-2020 MicroEJ Corp. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be found with this software.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "x_ram_checks.h"
#include "x_ui_config.h"
#include "bsp_util.h"


/* public weak function default definitions */


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

