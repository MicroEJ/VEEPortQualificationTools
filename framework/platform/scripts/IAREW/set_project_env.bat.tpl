@echo off

REM Copyright 2019-2024 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'set_project_env.bat' implementation for IAR Embedded Workbench.

REM 'set_project_env' is responsible for
REM - checking the availability of required environment variables 
REM - setting project local variables for 'build.bat' and 'run.bat' 

REM Required Environment Variable
REM IAR Embedded Workbench installation directory (e.g.: C:\Program Files (x86)\IAR Systems\Embedded Workbench VERSION)
REM IAREW_CHANGEIT_INSTALLATION_DIR

IF "%IAREW_CHANGEIT_INSTALLATION_DIR%" == "" (
    ECHO Please set the environment variable 'IAREW_CHANGEIT_INSTALLATION_DIR'
    exit /B -1
)

SET IAREW_INSTALLATION_DIR=%IAREW_CHANGEIT_INSTALLATION_DIR%

REM Set the project variables required by the build script for IAR Embedded Workbench
REM IAREW project directory that contains the project file .ewp (e.g.: %~dp0\..\)
SET IAREW_PROJECT_DIR=CHANGEIT
REM IAREW project file name without the extension .ewp (e.g.: Project)
SET IAREW_PROJECT_NAME=CHANGEIT
REM IAREW project output folder configuration (can be the project configuration or a combination with the project name)
SET IAREW_PROJECT_OUTPUT_FOLDER=CHANGEIT
REM IAREW project configuration (e.g.: Debug or Release)
SET IAREW_PROJECT_CONFIGURATION=CHANGEIT

REM Device macro file relative to IAREW_INSTALLATION_DIR (e.g.: arm\config\debugger\NXP\LPC5460x.dmac)
SET IAREW_PROJECT_DEVICE_MACRO=CHANGEIT

REM Device flash loader file relative to IAREW_INSTALLATION_DIR (e.g.: arm\config\flashloader\NXP\FlashNXPLPC5460xM4F512K.board)
SET IAREW_PROJECT_FLASH_LOADER=CHANGEIT

REM Path of the binary file to flash into the board
SET IAREW_PROJECT_EXECUTABLE_FILE="%IAREW_PROJECT_DIR%\%IAREW_PROJECT_OUTPUT_FOLDER%\Exe\%IAREW_OUT_FILENAME%.out"

ECHO IAREW_INSTALLATION_DIR=%IAREW_INSTALLATION_DIR%
ECHO IAREW_PROJECT_DIR=%IAREW_PROJECT_DIR%
ECHO IAREW_PROJECT_NAME=%IAREW_PROJECT_NAME%
ECHO IAREW_PROJECT_CONFIGURATION=%IAREW_PROJECT_CONFIGURATION%

exit /B 0
