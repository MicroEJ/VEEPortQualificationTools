@echo off

REM Copyright 2020-2021 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'set_project_env.bat' implementation for Keil µVision5.

REM 'set_project_env' is responsible for
REM - checking the availability of required environment variables 
REM - setting project local variables for 'build.bat' and 'run.bat' 

REM Required Environment Variable
REM Keil installation directory (e.g.: C:\Keil_v5)
REM KEIL_CHANGEIT_INSTALLATION_DIR

IF "%KEIL_CHANGEIT_INSTALLATION_DIR%" == "" (
    ECHO Please set the environment variable 'KEIL_CHANGEIT_INSTALLATION_DIR'
    exit /B -1
)

SET KEIL_INSTALLATION_DIR=%KEIL_CHANGEIT_INSTALLATION_DIR%

REM Set the project variables required by the build and scripts for Keil µVision5.
REM Keil project directory that contains the project files .uvprojx (e.g.: %~dp0\..\MDK-ARM)
SET KEIL_PROJECT_DIR=CHANGEIT
REM Keil project file name without the extension .uvprojx (e.g.: Project)
SET KEIL_PROJECT_NAME=CHANGEIT
REM Keil target name (e.g.: standalone)
SET KEIL_TARGETNAME=CHANGEIT

SET KEIL_PROJECT_EXECUTABLE_FILE="%KEIL_PROJECT_DIR%\%KEIL_TARGETNAME%\%KEIL_TARGETNAME%.axf"

ECHO KEIL_INSTALLATION_DIR=%KEIL_INSTALLATION_DIR%
ECHO KEIL_PROJECT_DIR=%KEIL_PROJECT_DIR%
ECHO KEIL_PROJECT_NAME=%KEIL_PROJECT_NAME%
ECHO KEIL_TARGETNAME=%KEIL_TARGETNAME%
exit /B 0
