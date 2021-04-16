@echo off

REM Copyright 2020-2021 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'set_project_env.bat' implementation for ECLIPSE_CDT.

REM 'set_project_env' is responsible for
REM - checking the availability of required environment variables 
REM - setting project local variables for 'build.bat' and 'run.bat' 

REM Required Environment Variable
REM ECLIPSE_CDT_CHANGEIT_INSTALLATION_DIR

IF "%ECLIPSE_CDT_CHANGEIT_INSTALLATION_DIR%" == "" (
    ECHO Please set the environment variable 'ECLIPSE_CDT_CHANGEIT_INSTALLATION_DIR'
    exit /B -1
)

REM Set the project variables required by the external build script for Eclipse CDT.
SET ECLIPSE_CDT_INSTALLATION_DIR=%ECLIPSE_CDT_CHANGEIT_INSTALLATION_DIR%
SET ECLIPSE_CDT_EXECUTABLE=CHANGEIT
SET ECLIPSE_CDT_PROJECT_DIR=CHANGEIT
SET ECLIPSE_CDT_PROJECT_NAME=CHANGEIT
SET ECLIPSE_CDT_PROJECT_CONFIGURATION=CHANGEIT
SET ECLIPSE_CDT_WORKSPACE_DIR=CHANGEIT
REM The Cube Programmer utility directory absolute path
SET CUBE_PROGRAMMER_DIR=CHANGEIT

ECHO ECLIPSE_CDT_INSTALLATION_DIR=%ECLIPSE_CDT_INSTALLATION_DIR%
ECHO ECLIPSE_CDT_PROJECT_DIR=%ECLIPSE_CDT_PROJECT_DIR%
ECHO ECLIPSE_CDT_PROJECT_NAME=%ECLIPSE_CDT_PROJECT_NAME%
ECHO ECLIPSE_CDT_PROJECT_CONFIGURATION=%ECLIPSE_CDT_PROJECT_CONFIGURATION%
ECHO CUBE_PROGRAMMER_DIR=%CUBE_PROGRAMMER_DIR%
exit /B 0