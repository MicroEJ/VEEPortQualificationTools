@echo off

REM Copyright 2020 MicroEJ Corp. All rights reserved.
REM Use of this source code is governed by a BSD-style license that can be found with this software.

REM 'build.bat' implementation for Eclipse CDT.

REM 'build.bat' is responsible for producing the executable file 
REM then copying this executable file to the current directory where it has been executed to a file named 'application.out'

CALL "%~dp0\set_project_env.bat"
IF %ERRORLEVEL% NEQ 0 (
	exit /B %ERRORLEVEL%
)
ECHO OK

@echo on

%ECLIPSE_CDT_INSTALLATION_DIR%\%ECLIPSE_CDT_EXECUTABLE% --launcher.suppressErrors -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data %ECLIPSE_CDT_WORKSPACE_DIR% -import "."

%ECLIPSE_CDT_INSTALLATION_DIR%\%ECLIPSE_CDT_EXECUTABLE% --launcher.suppressErrors -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data %ECLIPSE_CDT_WORKSPACE_DIR% -cleanBuild "%ECLPISE_CDT_PROJECT_NAME%/%ECLIPSE_CDT_PROJECT_CONFIGURATION%"

REM copy the generated .elf file
COPY %ECLIPSE_CDT_PROJECT_DIR%\%ECLIPSE_CDT_PROJECT_CONFIGURATION%\%ECLIPSE_CDT_PROJECT_NAME%.elf application.out