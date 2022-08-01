REM BAT
REM Copyright 2020-2021 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM Set Espressif toolchain installation directory default value recommanded by Espressif (see https://docs.espressif.com/projects/esp-idf/en/v3.3.4/get-started/windows-setup.html#toolchain-setup)
SET MSYS_PATH=C:\msys32\

REM Set the COM port used by your board
SET ESPPORT=COM0

REM Set the default value for 'ENV_BASH_CMD' environment variable (default is to build a full features firmware)
SET ENV_BASH_CMD="export IDF_PATH=$(pwd)/../../Drivers/esp-idf && make -j4 all"

REM Set the default value for 'ENV_FLASH_CMD' environment variable (default is to flash full features firmware without erasing it)
REM You can add erase_flash instead of flash to fully erase the flash at each run (e.g: "IDF_PATH=$(pwd)/../../Drivers/esp-idf && make -j4 erase_flash ESPPORT=%ESPPORT%")
SET ENV_FLASH_CMD="export IDF_PATH=$(pwd)/../../Drivers/esp-idf && make -j4 flash ESPPORT=$ESPPORT"
