@echo off

REM Copyright 2020 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'set_project_env.bat' implementation for Keil µVision5.

REM 'set_project_env' is responsible for
REM - checking the availability of required environment variables 
REM - setting project local variables for 'build.bat' and 'run.bat' 

REM Required Environment Variable
REM KEIL_CHANGEIT_INSTALLATION_DIR

IF "%KEIL_CHANGEIT_INSTALLATION_DIR%" == "" (
    ECHO Please set the environment variable 'KEIL_CHANGEIT_INSTALLATION_DIR'
    exit /B -1
)

REM Set the project variables required by the external build script for Keil µVision5
SET KEIL_INSTALLATION_DIR=%KEIL_CHANGEIT_INSTALLATION_DIR%
SET KEIL_PROJECT_DIR=CHANGEIT
SET KEIL_PROJECT_NAME=CHANGEIT
SET KEIL_PROJECT_CONFIGURATION=CHANGEIT

ECHO KEIL_INSTALLATION_DIR=%KEIL_INSTALLATION_DIR%
ECHO KEIL_PROJECT_DIR=%KEIL_PROJECT_DIR%
ECHO KEIL_PROJECT_NAME=%KEIL_PROJECT_NAME%
ECHO KEIL_PROJECT_CONFIGURATION=%KEIL_PROJECT_CONFIGURATION%
exit /B 0
